git submodule update --init --recursive
mkdir -p buildubu1604
cd buildubu1604
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)