#include <eznode/protocol/get_config.hpp>
#include <eznode/protocol/config.hpp>
#include <eznode/protocol/asset.hpp>
#include <eznode/protocol/types.hpp>
#include <eznode/protocol/version.hpp>

namespace eznode { namespace protocol {

fc::variant_object get_config()
{
   fc::mutable_variant_object result;

#ifdef IS_TEST_NET
   result[ "IS_TEST_NET" ] = true;
#else
   result[ "IS_TEST_NET" ] = false;
#endif

   result["SYMBOL_EZD"] = SYMBOL_EZD;
   result["PERCENT_100"] = PERCENT_100;
   result["PERCENT_1"] = PERCENT_1;
   result["PERCENT_10_OF_PERCENT_1"] = PERCENT_10_OF_PERCENT_1;
   result["ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD"] = ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD;
   result["ACTIVE_CHALLENGE_COOLDOWN"] = ACTIVE_CHALLENGE_COOLDOWN;
   result["ACTIVE_CHALLENGE_FEE"] = ACTIVE_CHALLENGE_FEE;
   result["ADDRESS_PREFIX"] = ADDRESS_PREFIX;
   result["APR_PERCENT_MULTIPLY_PER_BLOCK"] = APR_PERCENT_MULTIPLY_PER_BLOCK;
   result["APR_PERCENT_MULTIPLY_PER_HOUR"] = APR_PERCENT_MULTIPLY_PER_HOUR;
   result["APR_PERCENT_MULTIPLY_PER_ROUND"] = APR_PERCENT_MULTIPLY_PER_ROUND;
   result["APR_PERCENT_SHIFT_PER_BLOCK"] = APR_PERCENT_SHIFT_PER_BLOCK;
   result["APR_PERCENT_SHIFT_PER_HOUR"] = APR_PERCENT_SHIFT_PER_HOUR;
   result["APR_PERCENT_SHIFT_PER_ROUND"] = APR_PERCENT_SHIFT_PER_ROUND;
   result["BANDWIDTH_AVERAGE_WINDOW_SECONDS"] = BANDWIDTH_AVERAGE_WINDOW_SECONDS;
   result["BANDWIDTH_PRECISION"] = BANDWIDTH_PRECISION;
   result["BLOCKCHAIN_PRECISION"] = BLOCKCHAIN_PRECISION;
   result["BLOCKCHAIN_PRECISION_DIGITS"] = BLOCKCHAIN_PRECISION_DIGITS;
   result["BLOCKCHAIN_HARDFORK_VERSION"] = BLOCKCHAIN_HARDFORK_VERSION;
   result["BLOCKCHAIN_VERSION"] = BLOCKCHAIN_VERSION;
   result["BLOCK_INTERVAL"] = BLOCK_INTERVAL;
   result["BLOCKS_PER_DAY"] = BLOCKS_PER_DAY;
   result["BLOCKS_PER_HOUR"] = BLOCKS_PER_HOUR;
   result["BLOCKS_PER_YEAR"] = BLOCKS_PER_YEAR;
   result["CASHOUT_WINDOW_SECONDS"] = CASHOUT_WINDOW_SECONDS;
   result["CASHOUT_WINDOW_SECONDS_PRE_HF12"] = CASHOUT_WINDOW_SECONDS_PRE_HF12;
   result["CASHOUT_WINDOW_SECONDS_PRE_HF17"] = CASHOUT_WINDOW_SECONDS_PRE_HF17;
   result["CHAIN_ID"] = CHAIN_ID;
   result["COMMENT_REWARD_FUND_NAME"] = COMMENT_REWARD_FUND_NAME;
   result["CONTENT_APR_PERCENT"] = CONTENT_APR_PERCENT;
   result["CONTENT_CONSTANT_HF0"] = CONTENT_CONSTANT_HF0;
   result["CONTENT_REWARD_PERCENT"] = CONTENT_REWARD_PERCENT;
   result["CONVERSION_DELAY"] = CONVERSION_DELAY;
   result["CONVERSION_DELAY_PRE_HF_16"] = CONVERSION_DELAY_PRE_HF_16;
   result["CREATE_ACCOUNT_DELEGATION_RATIO"] = CREATE_ACCOUNT_DELEGATION_RATIO;
   result["CREATE_ACCOUNT_DELEGATION_TIME"] = CREATE_ACCOUNT_DELEGATION_TIME;
   result["CREATE_ACCOUNT_WITH_MODIFIER"] = CREATE_ACCOUNT_WITH_MODIFIER;
   result["CURATE_APR_PERCENT"] = CURATE_APR_PERCENT;
   result["DEFAULT_EZD_INTEREST_RATE"] = DEFAULT_EZD_INTEREST_RATE;
   result["EQUIHASH_K"] = EQUIHASH_K;
   result["EQUIHASH_N"] = EQUIHASH_N;
   result["FEED_HISTORY_WINDOW"] = FEED_HISTORY_WINDOW;
   result["FEED_HISTORY_WINDOW_PRE_HF_16"] = FEED_HISTORY_WINDOW_PRE_HF_16;
   result["FEED_INTERVAL_BLOCKS"] = FEED_INTERVAL_BLOCKS;
   result["FREE_TRANSACTIONS_WITH_NEW_ACCOUNT"] = FREE_TRANSACTIONS_WITH_NEW_ACCOUNT;
   result["GENESIS_TIME"] = GENESIS_TIME;
   result["HARDFORK_REQUIRED_WITNESSES"] = HARDFORK_REQUIRED_WITNESSES;
   result["INFLATION_NARROWING_PERIOD"] = INFLATION_NARROWING_PERIOD;
   result["INFLATION_RATE_START_PERCENT"] = INFLATION_RATE_START_PERCENT;
   result["INFLATION_RATE_STOP_PERCENT"] = INFLATION_RATE_STOP_PERCENT;
   result["INIT_MINER_NAME"] = INIT_MINER_NAME;
   result["INIT_PUBLIC_KEY_STR"] = INIT_PUBLIC_KEY_STR;
#if 0
   // do not expose private key, period.
   // we need this line present but inactivated so CI check for all constants in config.hpp doesn't complain.
   result["INIT_PRIVATE_KEY"] = INIT_PRIVATE_KEY;
#endif
   result["INIT_SUPPLY"] = INIT_SUPPLY;
   result["INIT_TIME"] = INIT_TIME;
   result["IRREVERSIBLE_THRESHOLD"] = IRREVERSIBLE_THRESHOLD;
   result["LIQUIDITY_APR_PERCENT"] = LIQUIDITY_APR_PERCENT;
   result["LIQUIDITY_REWARD_BLOCKS"] = LIQUIDITY_REWARD_BLOCKS;
   result["LIQUIDITY_REWARD_PERIOD_SEC"] = LIQUIDITY_REWARD_PERIOD_SEC;
   result["LIQUIDITY_TIMEOUT_SEC"] = LIQUIDITY_TIMEOUT_SEC;
   result["MAX_ACCOUNT_NAME_LENGTH"] = MAX_ACCOUNT_NAME_LENGTH;
   result["MAX_ACCOUNT_WITNESS_VOTES"] = MAX_ACCOUNT_WITNESS_VOTES;
   result["MAX_ASSET_WHITELIST_AUTHORITIES"] = MAX_ASSET_WHITELIST_AUTHORITIES;
   result["MAX_AUTHORITY_MEMBERSHIP"] = MAX_AUTHORITY_MEMBERSHIP;
   result["MAX_BLOCK_SIZE"] = MAX_BLOCK_SIZE;
   result["MAX_CASHOUT_WINDOW_SECONDS"] = MAX_CASHOUT_WINDOW_SECONDS;
   result["MAX_COMMENT_DEPTH"] = MAX_COMMENT_DEPTH;
   result["MAX_COMMENT_DEPTH_PRE_HF17"] = MAX_COMMENT_DEPTH_PRE_HF17;
   result["MAX_FEED_AGE_SECONDS"] = MAX_FEED_AGE_SECONDS;
   result["MAX_INSTANCE_ID"] = MAX_INSTANCE_ID;
   result["MAX_MEMO_SIZE"] = MAX_MEMO_SIZE;
   result["MAX_WITNESSES"] = MAX_WITNESSES;
   result["MAX_MINER_WITNESSES_HF0"] = MAX_MINER_WITNESSES_HF0;
   result["MAX_MINER_WITNESSES_HF17"] = MAX_MINER_WITNESSES_HF17;
   result["MAX_PERMLINK_LENGTH"] = MAX_PERMLINK_LENGTH;
   result["MAX_PROXY_RECURSION_DEPTH"] = MAX_PROXY_RECURSION_DEPTH;
   result["MAX_RATION_DECAY_RATE"] = MAX_RATION_DECAY_RATE;
   result["MAX_RESERVE_RATIO"] = MAX_RESERVE_RATIO;
   result["MAX_RUNNER_WITNESSES_HF0"] = MAX_RUNNER_WITNESSES_HF0;
   result["MAX_RUNNER_WITNESSES_HF17"] = MAX_RUNNER_WITNESSES_HF17;
   result["MAX_SHARE_SUPPLY"] = MAX_SHARE_SUPPLY;
   result["MAX_SIG_CHECK_DEPTH"] = MAX_SIG_CHECK_DEPTH;
   result["MAX_TIME_UNTIL_EXPIRATION"] = MAX_TIME_UNTIL_EXPIRATION;
   result["MAX_TRANSACTION_SIZE"] = MAX_TRANSACTION_SIZE;
   result["MAX_UNDO_HISTORY"] = MAX_UNDO_HISTORY;
   result["MAX_URL_LENGTH"] = MAX_URL_LENGTH;
   result["MAX_VOTE_CHANGES"] = MAX_VOTE_CHANGES;
   result["MAX_VOTED_WITNESSES_HF0"] = MAX_VOTED_WITNESSES_HF0;
   result["MAX_VOTED_WITNESSES_HF17"] = MAX_VOTED_WITNESSES_HF17;
   result["MAX_WITHDRAW_ROUTES"] = MAX_WITHDRAW_ROUTES;
   result["MAX_WITNESS_URL_LENGTH"] = MAX_WITNESS_URL_LENGTH;
   result["MIN_ACCOUNT_CREATION_FEE"] = MIN_ACCOUNT_CREATION_FEE;
   result["MIN_ACCOUNT_NAME_LENGTH"] = MIN_ACCOUNT_NAME_LENGTH;
   result["MIN_BLOCK_SIZE"] = MIN_BLOCK_SIZE;
   result["MIN_BLOCK_SIZE_LIMIT"] = MIN_BLOCK_SIZE_LIMIT;
   result["MIN_CONTENT_REWARD"] = MIN_CONTENT_REWARD;
   result["MIN_CURATE_REWARD"] = MIN_CURATE_REWARD;
   result["MIN_PERMLINK_LENGTH"] = MIN_PERMLINK_LENGTH;
   result["MIN_REPLY_INTERVAL"] = MIN_REPLY_INTERVAL;
   result["MIN_ROOT_COMMENT_INTERVAL"] = MIN_ROOT_COMMENT_INTERVAL;
   result["MIN_VOTE_INTERVAL_SEC"] = MIN_VOTE_INTERVAL_SEC;
   result["MINER_ACCOUNT"] = MINER_ACCOUNT;
   result["MINER_PAY_PERCENT"] = MINER_PAY_PERCENT;
   result["MIN_FEEDS"] = MIN_FEEDS;
   result["MINING_REWARD"] = MINING_REWARD;
   result["MINING_TIME"] = MINING_TIME;
   result["MIN_LIQUIDITY_REWARD"] = MIN_LIQUIDITY_REWARD;
   result["MIN_LIQUIDITY_REWARD_PERIOD_SEC"] = MIN_LIQUIDITY_REWARD_PERIOD_SEC;
   result["MIN_PAYOUT_EZD"] = MIN_PAYOUT_EZD;
   result["MIN_POW_REWARD"] = MIN_POW_REWARD;
   result["MIN_PRODUCER_REWARD"] = MIN_PRODUCER_REWARD;
   result["MIN_RATION"] = MIN_RATION;
   result["MIN_TRANSACTION_EXPIRATION_LIMIT"] = MIN_TRANSACTION_EXPIRATION_LIMIT;
   result["MIN_TRANSACTION_SIZE_LIMIT"] = MIN_TRANSACTION_SIZE_LIMIT;
   result["MIN_UNDO_HISTORY"] = MIN_UNDO_HISTORY;
   result["NULL_ACCOUNT"] = NULL_ACCOUNT;
   result["NUM_INIT_MINERS"] = NUM_INIT_MINERS;
   result["NUM_INIT_EXTRAS"] = NUM_INIT_EXTRAS;
   result["ORIGINAL_MIN_ACCOUNT_CREATION_FEE"] = ORIGINAL_MIN_ACCOUNT_CREATION_FEE;
   result["OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM"] = OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM;
   result["OWNER_AUTH_RECOVERY_PERIOD"] = OWNER_AUTH_RECOVERY_PERIOD;
   result["OWNER_CHALLENGE_COOLDOWN"] = OWNER_CHALLENGE_COOLDOWN;
   result["OWNER_CHALLENGE_FEE"] = OWNER_CHALLENGE_FEE;
   result["OWNER_UPDATE_LIMIT"] = OWNER_UPDATE_LIMIT;
   result["POST_AVERAGE_WINDOW"] = POST_AVERAGE_WINDOW;
   result["POST_MAX_BANDWIDTH"] = POST_MAX_BANDWIDTH;
   result["POST_REWARD_FUND_NAME"] = POST_REWARD_FUND_NAME;
   result["POST_WEIGHT_CONSTANT"] = POST_WEIGHT_CONSTANT;
   result["POW_APR_PERCENT"] = POW_APR_PERCENT;
   result["PRODUCER_APR_PERCENT"] = PRODUCER_APR_PERCENT;
   result["PROXY_TO_SELF_ACCOUNT"] = PROXY_TO_SELF_ACCOUNT;
   result["EZD_INTEREST_COMPOUND_INTERVAL_SEC"] = EZD_INTEREST_COMPOUND_INTERVAL_SEC;
   result["SECONDS_PER_YEAR"] = SECONDS_PER_YEAR;
   result["RECENT_RSHARES_DECAY_RATE_HF19"] = RECENT_RSHARES_DECAY_RATE_HF19;
   result["RECENT_RSHARES_DECAY_RATE_HF17"] = RECENT_RSHARES_DECAY_RATE_HF17;
   result["REVERSE_AUCTION_WINDOW_SECONDS"] = REVERSE_AUCTION_WINDOW_SECONDS;
   result["ROOT_POST_PARENT"] = ROOT_POST_PARENT;
   result["SAVINGS_WITHDRAW_REQUEST_LIMIT"] = SAVINGS_WITHDRAW_REQUEST_LIMIT;
   result["SAVINGS_WITHDRAW_TIME"] = SAVINGS_WITHDRAW_TIME;
   result["EZD_START_PERCENT"] = EZD_START_PERCENT;
   result["EZD_STOP_PERCENT"] = EZD_STOP_PERCENT;
   result["SECOND_CASHOUT_WINDOW"] = SECOND_CASHOUT_WINDOW;
   result["SOFT_MAX_COMMENT_DEPTH"] = SOFT_MAX_COMMENT_DEPTH;
   result["START_MINER_VOTING_BLOCK"] = START_MINER_VOTING_BLOCK;
   result["START_VESTING_BLOCK"] = START_VESTING_BLOCK;
   result["TEMP_ACCOUNT"] = TEMP_ACCOUNT;
   result["UPVOTE_LOCKOUT_HF7"] = UPVOTE_LOCKOUT_HF7;
   result["UPVOTE_LOCKOUT_HF17"] = UPVOTE_LOCKOUT_HF17;
   result["VESTING_FUND_PERCENT"] = VESTING_FUND_PERCENT;
   result["VESTING_WITHDRAW_INTERVALS"] = VESTING_WITHDRAW_INTERVALS;
   result["VESTING_WITHDRAW_INTERVALS_PRE_HF_16"] = VESTING_WITHDRAW_INTERVALS_PRE_HF_16;
   result["VESTING_WITHDRAW_INTERVAL_SECONDS"] = VESTING_WITHDRAW_INTERVAL_SECONDS;
   result["VOTE_CHANGE_LOCKOUT_PERIOD"] = VOTE_CHANGE_LOCKOUT_PERIOD;
   result["VOTE_DUST_THRESHOLD"] = VOTE_DUST_THRESHOLD;
   result["VOTE_REGENERATION_SECONDS"] = VOTE_REGENERATION_SECONDS;
   result["SYMBOL_ECO"] = SYMBOL_ECO;
   result["SYMBOL_EZP"] = SYMBOL_EZP;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH"] = VIRTUAL_SCHEDULE_LAP_LENGTH;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH2"] = VIRTUAL_SCHEDULE_LAP_LENGTH2;

   return result;
}

} } // eznode::protocol
