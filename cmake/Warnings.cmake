# Set warning flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    add_compile_options(-Wall -Wextra -Wpedantic) # -Wconversion
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    add_compile_options(-Wall -Wextra -Wpedantic) # -Wconversion
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
endif()

# add_compile_options(-Weffc++)