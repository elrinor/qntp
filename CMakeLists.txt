cmake_minimum_required(VERSION 3.21)

project(
    qntp
    VERSION 1.0.0
    DESCRIPTION "C++ NTP client for Qt"
    HOMEPAGE_URL "https://github.com/elrinor/qntp/"
    LANGUAGES CXX
)

find_package(Qt6 COMPONENTS Core Network REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(qntp STATIC
    src/qntp/NtpClient.h
    src/qntp/NtpPacket.h
    src/qntp/NtpReply.h
    src/qntp/NtpTimestamp.h
    src/qntp/NtpEnums.h
)

set(qntp_warning_guard "")
if(PROJECT_IS_TOP_LEVEL)
    set(qntp_warning_guard SYSTEM)
endif()

target_include_directories(
    qntp
    ${qntp_warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

target_link_libraries(qntp PUBLIC Qt::Core Qt::Network)

target_compile_features(qntp PUBLIC cxx_std_11)

if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory(examples)
endif()