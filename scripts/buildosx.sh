# $repos is an environment variable which is 
# an absolute path to the directory your github 
# repo for the ezira node software resides in

# cd $repos/eznode/dev ;
rm -r build/ ;
mkdir build && cd build ;
cmake \
	-DCMAKE_BUILD_TYPE=Release \
	-DLOW_MEMORY_NODE=OFF \
	-DCLEAR_VOTES=OFF \
	-DSKIP_BY_TX_ID=ON \
	..

# -DCMAKE_INSTALL_PREFIX=$repos/eznode/dev/made \
# make -j$(sysctl -n hw.logicalcpu)

