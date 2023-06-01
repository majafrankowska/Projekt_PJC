cmake_minimum_required(VERSION 3.24)
project(PasswordManagerPJC)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManagerPJC main.cpp Szyfrowanie.h Operations.cpp Operations.h Login.cpp Login.h Szyfrowanie.cpp)

