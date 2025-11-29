module unload intel-oneapi-compilers
module load cmake gcc intel-mpi/2019-gcc

#mkdir -p build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
#cd ..

