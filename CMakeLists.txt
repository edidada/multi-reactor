cmake_minimum_required(VERSION 3.12)
project(cpp_reactor)
add_executable(cpp_multi-reactor src/main.cc
        src/TcpConn.cc
        src/TcpServer.cc
)