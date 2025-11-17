cmake_minimum_required(VERSION 3.16)
project(DigitalWalletDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wallet
    src/main.cpp
    src/DigitalWallet.cpp
)

target_include_directories(wallet PRIVATE include)

set_target_properties(wallet PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(wallet PRIVATE -Wall -Wextra -Wpedantic)
  #if(CMAKE_BUILD_TYPE STREQUAL "Debug") #ptdebug sa mearga cu sanatize
  #  target_compile_options(wallet PRIVATE -fsanitize=address,undefined)
  #  target_link_options(wallet PRIVATE -fsanitize=address,undefined)
  #endif()
endif()

add_custom_target(run
  COMMAND wallet
  DEPENDS wallet
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
