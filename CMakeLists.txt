cmake_minimum_required(VERSION 3.28)
project(cryptography_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(cryptography_1 main.cpp
          simple_substitution_cipher.cpp
          simple_substitution_cipher.h
          affine_cipher.cpp
          affine_cipher.h
          affine_recurrent_cipher.cpp
          affine_recurrent_cipher.h
)
