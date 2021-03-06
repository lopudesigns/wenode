#include <boost/test/unit_test.hpp>
#include <boost/program_options.hpp>

#include <graphene/utilities/tempdir.hpp>

#include <node/chain/node_objects.hpp>
#include <node/chain/history_object.hpp>
#include <node/account_history/account_history_plugin.hpp>
#include <node/witness/witness_plugin.hpp>

#include <fc/crypto/digest.hpp>
#include <fc/smart_ref_impl.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "database_fixture.hpp"

#include <node/protocol/config.hpp>

//using namespace node::chain::test;

uint32_t TESTING_GENESIS_TIMESTAMP = 1431700000;

namespace node { namespace chain {

using std::cout;
using std::cerr;

clean_database_fixture::clean_database_fixture()
{
   try {
   int argc = boost::unit_test::framework::master_test_suite().argc;
   char** argv = boost::unit_test::framework::master_test_suite().argv;
   for( int i=1; i<argc; i++ )
   {
      const std::string arg = argv[i];
      if( arg == "--record-assert-trip" )
         fc::enable_record_assert_trip = true;
      if( arg == "--show-test-names" )
         std::cout << "running test " << boost::unit_test::framework::current_test_case().p_name << std::endl;
   }
   auto ahplugin = app.register_plugin< node::account_history::account_history_plugin >();
   db_plugin = app.register_plugin< node::plugin::debug_node::debug_node_plugin >();
   auto wit_plugin = app.register_plugin< node::witness::witness_plugin >();
   init_account_pub_key = init_account_priv_key.get_public_key();

   boost::program_options::variables_map options;

   db_plugin->logging = false;
   ahplugin->plugin_initialize( options );
   db_plugin->plugin_initialize( options );
   wit_plugin->plugin_initialize( options );

   open_database();

   generate_block();
   db.set_hardfork( NUM_HARDFORKS );
   generate_block();

   //ahplugin->plugin_startup();
   db_plugin->plugin_startup();
   score( genesisAccountBasename, 10000 );

   // Fill up the rest of the required miners
   for( int i = numberOfGenesisWitnessAccounts; i < MAX_WITNESSES; i++ )
   {
      accountCreate( genesisAccountBasename + fc::to_string( i ), init_account_pub_key );
      fund( genesisAccountBasename + fc::to_string( i ), MIN_PRODUCER_REWARD.amount.value );
      witness_create( genesisAccountBasename + fc::to_string( i ), init_account_priv_key, "foo.bar", init_account_pub_key, MIN_PRODUCER_REWARD.amount );
   }

   validate_database();
   } catch ( const fc::exception& e )
   {
      edump( (e.to_detail_string()) );
      throw;
   }

   return;
}

clean_database_fixture::~clean_database_fixture()
{ try {
   // If we're unwinding due to an exception, don't do any more checks.
   // This way, boost test's last checkpoint tells us approximately where the error was.
   if( !std::uncaught_exception() )
   {
      BOOST_CHECK( db.get_node_properties().skip_flags == database::skip_nothing );
   }

   if( data_dir )
      db.close();
   return;
} FC_CAPTURE_AND_RETHROW() }

void clean_database_fixture::resize_shared_mem( uint64_t size )
{
   db.wipe( data_dir->path(), data_dir->path(), true );
   int argc = boost::unit_test::framework::master_test_suite().argc;
   char** argv = boost::unit_test::framework::master_test_suite().argv;
   for( int i=1; i<argc; i++ )
   {
      const std::string arg = argv[i];
      if( arg == "--record-assert-trip" )
         fc::enable_record_assert_trip = true;
      if( arg == "--show-test-names" )
         std::cout << "running test " << boost::unit_test::framework::current_test_case().p_name << std::endl;
   }
   init_account_pub_key = init_account_priv_key.get_public_key();

   db.open( data_dir->path(), data_dir->path(), INITIAL_TEST_SUPPLY, size, chainbase::database::read_write );

   boost::program_options::variables_map options;


   generate_block();
   db.set_hardfork( NUM_HARDFORKS );
   generate_block();

   score( genesisAccountBasename, 10000 );

   // Fill up the rest of the required miners
   for( int i = numberOfGenesisWitnessAccounts; i < MAX_WITNESSES; i++ )
   {
      accountCreate( genesisAccountBasename + fc::to_string( i ), init_account_pub_key );
      fund( genesisAccountBasename + fc::to_string( i ), MIN_PRODUCER_REWARD.amount.value );
      witness_create( genesisAccountBasename + fc::to_string( i ), init_account_priv_key, "foo.bar", init_account_pub_key, MIN_PRODUCER_REWARD.amount );
   }

   validate_database();
}

live_database_fixture::live_database_fixture()
{
   try
   {
      ilog( "Loading saved chain" );
      _chain_dir = fc::current_path() / "test_blockchain";
      FC_ASSERT( fc::exists( _chain_dir ), "Requires blockchain to test on in ./test_blockchain" );

      auto ahplugin = app.register_plugin< node::account_history::account_history_plugin >();
      ahplugin->plugin_initialize( boost::program_options::variables_map() );

      db.open( _chain_dir, _chain_dir );

      validate_database();
      generate_block();

      ilog( "Done loading saved chain" );
   }
   FC_LOG_AND_RETHROW()
}

live_database_fixture::~live_database_fixture()
{
   try
   {
      // If we're unwinding due to an exception, don't do any more checks.
      // This way, boost test's last checkpoint tells us approximately where the error was.
      if( !std::uncaught_exception() )
      {
         BOOST_CHECK( db.get_node_properties().skip_flags == database::skip_nothing );
      }

      db.pop_block();
      db.close();
      return;
   }
   FC_LOG_AND_RETHROW()
}

fc::ecc::private_key database_fixture::generate_private_key(string seed)
{
   static const fc::ecc::private_key committee = fc::ecc::private_key::regenerate( fc::sha256::hash( string( "init_key" ) ) );
   if( seed == "init_key" )
      return committee;
   return fc::ecc::private_key::regenerate( fc::sha256::hash( seed ) );
}

string database_fixture::generate_anon_acct_name()
{
   // names of the form "anon-acct-x123" ; the "x" is necessary
   //    to workaround issue #46
   return "anon-acct-x" + std::to_string( anon_acct_count++ );
}

void database_fixture::open_database()
{
   if( !data_dir ) {
      data_dir = fc::temp_directory( graphene::utilities::temp_directory_path() );
      db._log_hardforks = false;
      db.open( data_dir->path(), data_dir->path(), INITIAL_TEST_SUPPLY, 1024 * 1024 * 8, chainbase::database::read_write ); // 8 MB file for testing
   }
}

void database_fixture::generate_block(uint32_t skip, const fc::ecc::private_key& key, int miss_blocks)
{
   skip |= default_skip;
   db_plugin->debug_generate_blocks( graphene::utilities::key_to_wif( key ), 1, skip, miss_blocks );
}

void database_fixture::generate_blocks( uint32_t block_count )
{
   auto produced = db_plugin->debug_generate_blocks( debug_key, block_count, default_skip, 0 );
   BOOST_REQUIRE( produced == block_count );
}

void database_fixture::generate_blocks(fc::time_point_sec timestamp, bool miss_intermediate_blocks)
{
   db_plugin->debug_generate_blocks_until( debug_key, timestamp, miss_intermediate_blocks, default_skip );
   BOOST_REQUIRE( ( db.head_block_time() - timestamp ).to_seconds() < BLOCK_INTERVAL );
}

const account_object& database_fixture::accountCreate(
   const string& name,
   const string& creator,
   const private_key_type& creator_key,
   const share_type& fee,
   const public_key_type& key,
   const public_key_type& post_key,
   const string& json
   )
{
   try
   {
      if( db.has_hardfork( HARDFORK_0_17 ) )
      {
         accountCreateWithDelegation_operation op;
         op.newAccountName = name;
         op.creator = creator;
         op.fee = asset( fee, SYMBOL_COIN );
         op.delegation = asset( 0, SYMBOL_SCORE );
         op.owner = authority( 1, key, 1 );
         op.active = authority( 1, key, 1 );
         op.posting = authority( 1, post_key, 1 );
         op.memoKey = key;
         op.json = json;

         trx.operations.push_back( op );
      }
      else
      {
         accountCreate_operation op;
         op.newAccountName = name;
         op.creator = creator;
         op.fee = asset( fee, SYMBOL_COIN );
         op.owner = authority( 1, key, 1 );
         op.active = authority( 1, key, 1 );
         op.posting = authority( 1, post_key, 1 );
         op.memoKey = key;
         op.json = json;

         trx.operations.push_back( op );
      }

      trx.set_expiration( db.head_block_time() + MAX_TIME_UNTIL_EXPIRATION );
      trx.sign( creator_key, db.get_chain_id() );
      trx.validate();
      db.push_transaction( trx, 0 );
      trx.operations.clear();
      trx.signatures.clear();

      const account_object& acct = db.get_account( name );

      return acct;
   }
   FC_CAPTURE_AND_RETHROW( (name)(creator) )
}

const account_object& database_fixture::accountCreate(
   const string& name,
   const public_key_type& key,
   const public_key_type& post_key
)
{
   try
   {
      return accountCreate(
         name,
         genesisAccountBasename,
         init_account_priv_key,
         std::max( db.get_witness_schedule_object().median_props.account_creation_fee.amount, share_type( 100 ) ),
         key,
         post_key,
         "" );
   }
   FC_CAPTURE_AND_RETHROW( (name) );
}

const account_object& database_fixture::accountCreate(
   const string& name,
   const public_key_type& key
)
{
   return accountCreate( name, key, key );
}

const witness_object& database_fixture::witness_create(
   const string& owner,
   const private_key_type& owner_key,
   const string& url,
   const public_key_type& signing_key,
   const share_type& fee )
{
   try
   {
      witness_update_operation op;
      op.owner = owner;
      op.url = url;
      op.block_signing_key = signing_key;
      op.fee = asset( fee, SYMBOL_COIN );

      trx.operations.push_back( op );
      trx.set_expiration( db.head_block_time() + MAX_TIME_UNTIL_EXPIRATION );
      trx.sign( owner_key, db.get_chain_id() );
      trx.validate();
      db.push_transaction( trx, 0 );
      trx.operations.clear();
      trx.signatures.clear();

      return db.get_witness( owner );
   }
   FC_CAPTURE_AND_RETHROW( (owner)(url) )
}

void database_fixture::fund(
   const string& account_name,
   const share_type& amount
   )
{
   try
   {
      transfer( genesisAccountBasename, account_name, amount );

   } FC_CAPTURE_AND_RETHROW( (account_name)(amount) )
}

void database_fixture::fund(
   const string& account_name,
   const asset& amount
   )
{
   try
   {
      db_plugin->debug_update( [=]( database& db)
      {
         db.modify( db.get_account( account_name ), [&]( account_object& a )
         {
            if( amount.symbol == SYMBOL_COIN )
               a.balance += amount;
            else if( amount.symbol == SYMBOL_USD )
            {
               a.TSDbalance += amount;
               a.TSD_seconds_last_update = db.head_block_time();
            }
         });

         db.modify( db.get_dynamic_global_properties(), [&]( dynamic_global_property_object& gpo )
         {
            if( amount.symbol == SYMBOL_COIN )
               gpo.current_supply += amount;
            else if( amount.symbol == SYMBOL_USD )
               gpo.current_TSD_supply += amount;
         });

         if( amount.symbol == SYMBOL_USD )
         {
            const auto& median_feed = db.get_feed_history();
            if( median_feed.current_median_history.is_null() )
               db.modify( median_feed, [&]( feed_history_object& f )
               {
                  f.current_median_history = price( asset( 1, SYMBOL_USD ), asset( 1, SYMBOL_COIN ) );
               });
         }

         db.update_virtual_supply();
      }, default_skip );
   }
   FC_CAPTURE_AND_RETHROW( (account_name)(amount) )
}

void database_fixture::convert(
   const string& account_name,
   const asset& amount )
{
   try
   {
      const account_object& account = db.get_account( account_name );


      if ( amount.symbol == SYMBOL_COIN )
      {
         db.adjust_balance( account, -amount );
         db.adjust_balance( account, db.to_TSD( amount ) );
         db.adjust_supply( -amount );
         db.adjust_supply( db.to_TSD( amount ) );
      }
      else if ( amount.symbol == SYMBOL_USD )
      {
         db.adjust_balance( account, -amount );
         db.adjust_balance( account, db.to_TME( amount ) );
         db.adjust_supply( -amount );
         db.adjust_supply( db.to_TME( amount ) );
      }
   } FC_CAPTURE_AND_RETHROW( (account_name)(amount) )
}

void database_fixture::transfer(
   const string& from,
   const string& to,
   const share_type& amount )
{
   try
   {
      transfer_operation op;
      op.from = from;
      op.to = to;
      op.amount = amount;

      trx.operations.push_back( op );
      trx.set_expiration( db.head_block_time() + MAX_TIME_UNTIL_EXPIRATION );
      trx.validate();
      db.push_transaction( trx, ~0 );
      trx.operations.clear();
   } FC_CAPTURE_AND_RETHROW( (from)(to)(amount) )
}

void database_fixture::score( const string& from, const share_type& amount )
{
   try
   {
      transferTMEtoSCOREfund_operation op;
      op.from = from;
      op.to = "";
      op.amount = asset( amount, SYMBOL_COIN );

      trx.operations.push_back( op );
      trx.set_expiration( db.head_block_time() + MAX_TIME_UNTIL_EXPIRATION );
      trx.validate();
      db.push_transaction( trx, ~0 );
      trx.operations.clear();
   } FC_CAPTURE_AND_RETHROW( (from)(amount) )
}

void database_fixture::score( const string& account, const asset& amount )
{
   if( amount.symbol != SYMBOL_COIN )
      return;

   db_plugin->debug_update( [=]( database& db )
   {
      db.modify( db.get_dynamic_global_properties(), [&]( dynamic_global_property_object& gpo )
      {
         gpo.current_supply += amount;
      });

      db.createTMEfundForSCORE( db.get_account( account ), amount );

      db.update_virtual_supply();
   }, default_skip );
}

void database_fixture::proxy( const string& account, const string& proxy )
{
   try
   {
      account_witness_proxy_operation op;
      op.account = account;
      op.proxy = proxy;
      trx.operations.push_back( op );
      db.push_transaction( trx, ~0 );
      trx.operations.clear();
   } FC_CAPTURE_AND_RETHROW( (account)(proxy) )
}

void database_fixture::set_price_feed( const price& new_price )
{
   try
   {
      for ( int i = 1; i < 8; i++ )
      {
         feed_publish_operation op;
         op.publisher = genesisAccountBasename + fc::to_string( i );
         op.exchange_rate = new_price;
         trx.operations.push_back( op );
         trx.set_expiration( db.head_block_time() + MAX_TIME_UNTIL_EXPIRATION );
         db.push_transaction( trx, ~0 );
         trx.operations.clear();
      }
   } FC_CAPTURE_AND_RETHROW( (new_price) )

   generate_blocks( BLOCKS_PER_HOUR );
   BOOST_REQUIRE(
#ifdef IS_TEST_NET
      !db.skip_price_feed_limit_check ||
#endif
      db.get(feed_history_id_type()).current_median_history == new_price
   );
}

const asset& database_fixture::get_balance( const string& account_name )const
{
  return db.get_account( account_name ).balance;
}

void database_fixture::sign(signed_transaction& trx, const fc::ecc::private_key& key)
{
   trx.sign( key, db.get_chain_id() );
}

vector< operation > database_fixture::get_last_operations( uint32_t num_ops )
{
   vector< operation > ops;
   const auto& acc_hist_idx = db.get_index< account_history_index >().indices().get< by_id >();
   auto itr = acc_hist_idx.end();

   while( itr != acc_hist_idx.begin() && ops.size() < num_ops )
   {
      itr--;
      ops.push_back( fc::raw::unpack< node::chain::operation >( db.get(itr->op).serialized_op ) );
   }

   return ops;
}

void database_fixture::validate_database( void )
{
   try
   {
      db.validate_invariants();
   }
   FC_LOG_AND_RETHROW();
}

namespace test {

bool _push_block( database& db, const signed_block& b, uint32_t skip_flags /* = 0 */ )
{
   return db.push_block( b, skip_flags);
}

void _push_transaction( database& db, const signed_transaction& tx, uint32_t skip_flags /* = 0 */ )
{ try {
   db.push_transaction( tx, skip_flags );
} FC_CAPTURE_AND_RETHROW((tx)) }

} // node::chain::test

} } // node::chain
