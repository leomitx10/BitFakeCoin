cmake_minimum_required(VERSION 3.10)
project(CryptoProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Download and include Crow
include(FetchContent)
FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow
    GIT_TAG v1.0+5
)
FetchContent_MakeAvailable(Crow)

# Download and include jwt-cpp
FetchContent_Declare(
    jwt-cpp
    GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(jwt-cpp)

# Add source files
set(SOURCES
    src/main.cpp
    src/blockchain/Block.cpp
    src/blockchain/Blockchain.cpp
)

# Add executable
add_executable(crypto_app ${SOURCES})

# Include directories
target_include_directories(crypto_app PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${OPENSSL_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(crypto_app PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    Crow::Crow
    jwt-cpp
)
