cmake_minimum_required(VERSION 3.18)

project(safe_cast)

set(CMAKE_INSTALL_PREFIX /usr/include)

install(FILES safe_cast.h DESTINATION ${CMAKE_INSTALL_PREFIX}/safe_cast)
