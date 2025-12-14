set(
    SRC
    mpi_interposition.cpp
    mpi_impl.cpp
    util.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_library(mmc SHARED ${SRC})

# target_compile_features(mmc PUBLIC cxx_std_20)

target_include_directories(mmc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(mmc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/queue)
target_include_directories(mmc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mpi)

target_link_libraries(mmc PRIVATE MPI::MPI_CXX)
