cmake_minimum_required(VERSION 3.16)
project(vader_sentiment_cpython)

set(CMAKE_CXX_STANDARD 14)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.71.0 COMPONENTS filesystem system REQUIRED)
add_executable(vader_sentiment_cpython main.cpp)

target_link_libraries(vader_sentiment_cpython PUBLIC ${PYTHON_LIBRARIES})
target_link_libraries(vader_sentiment_cpython LINK_PUBLIC ${Boost_LIBRARIES} )
target_link_libraries(vader_sentiment_cpython PUBLIC ${CMAKE_DL_LIBS})
