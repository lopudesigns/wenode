args=""
# EITHER ADD YOUR PRIVATE KEYS AS A LIST IN ./scripts/private-keys
# eg. no whitespaces start and finish of the file
# either
# "privatekey1 privatekey2 privatek3"
# or
# "privatekey1 \
# privatekey2 \
# privatekey3"

# and use the following PRIVATE_KEYS definition
PRIVATE_KEYS=$(cat ./scripts/private-keys)
# OR
# PRIVATE_KEYS="privatekey1 privatekey2 privatekey3"

if [[ ! -z "$PRIVATE_KEYS" ]]; then
    for PRIVATE_KEY in $PRIVATE_KEYS ; do
        args+=" --private-key=$PRIVATE_KEY"
    done
fi

# The node software will automatically match the private keys with
# all the corresponding witness account names you input or generate

# either generate with the following code
# will make webuilder1 - webuilder99 if start=0 and end=100
start=1
end=50
witness_base_name="webuilder"
args+=" --witness=\"$witness_base_name\""
for ((n=$start;n<$end;n++)); do
	args+=" --witness=\"$witness_base_name$((n))\""
done

# add argument
# args+=' --replay-blockchain'
# add argument
args+=' --rpc-endpoint=127.0.0.1:8090'

# add argument
args+=' --p2p-endpoint=0.0.0.0:2001'

# add argument
args+=' --data-dir="/Users/lopu/Sync/git/weyoume/wenode/dev-wenode/osx_data-dir/"'

# or set witness names manually as a list
# witness_names="witnessname1 witnessname2 witnessname3"
# or use a file
# witness_names=$(cat ./scripts/private-witness-names)
# witness names don't need to be private but the repo ignores
# files beginning with scripts/private* when commiting and publishing

# output witness names
echo [$witness_names]

# $repos is an environment variable which is 
# an absolute path to the directory your github 
# repo for the WeYouMe node software resides in

./osx_build/programs/node/node $args