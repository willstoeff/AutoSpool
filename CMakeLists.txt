set(BOARD nucleo_l152re)

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(AutoSpool)

target_include_directories(app PUBLIC inc)

target_sources(app PRIVATE src/main.cpp src/drv8838.cpp)