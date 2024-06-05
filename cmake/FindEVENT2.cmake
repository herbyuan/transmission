if(EVENT2_PREFER_STATIC_LIB)
    set(EVENT2_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
    if(WIN32)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib ${CMAKE_FIND_LIBRARY_SUFFIXES})
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    endif()
endif()

if(UNIX)
    find_package(PkgConfig QUIET)
    pkg_check_modules(_EVENT2 QUIET libevent)
endif()

find_path(EVENT2_INCLUDE_DIR
    NAMES event2/event.h
    HINTS ${_EVENT2_INCLUDEDIR})
find_library(EVENT2_LIBRARY
    NAMES
        event-2.1
        event
    HINTS ${_EVENT2_LIBDIR})
find_library(LIBEVENT_OPENSSL_LIBRARY
    NAMES event_openssl
    HINTS ${_EVENT2_LIBDIR})

if(EVENT2_INCLUDE_DIR)
    if(_EVENT2_VERSION)
        set(EVENT2_VERSION ${_EVENT2_VERSION})
    else()
        file(STRINGS "${EVENT2_INCLUDE_DIR}/event2/event-config.h" EVENT2_VERSION_STR
            REGEX "^#define[\t ]+_EVENT_VERSION[\t ]+\"[^\"]+\"")
        if(EVENT2_VERSION_STR MATCHES "\"([^\"]+)\"")
            set(EVENT2_VERSION "${CMAKE_MATCH_1}")
        endif()
    endif()
endif()

# 判断是否找到 libevent_openssl 库
if(LIBEVENT_OPENSSL_LIBRARY)
    message("==========libevent_openssl library found at: ${LIBEVENT_OPENSSL_LIBRARY}")
    # 在这里可以添加您的逻辑，比如设置编译定义或链接库
else()
    message("==========libevent_openssl library not found")
    # 在这里可以添加处理库未找到的逻辑
endif()

message("==========${EVENT2_LIBRARY}")
if(LIBEVENT_OPENSSL_LIBRARY)
    # 添加新的路径到现有列表中
    list(APPEND EVENT2_LIBRARY LIBEVENT_OPENSSL_LIBRARY)

    # 打印更新后的列表
    message("Updated EVENT2_LIBRARY: ${EVENT2_LIBRARY}")

    # 遍历更新后的列表
    foreach(LIB ${EVENT2_LIBRARY})
        message("Library path: ${LIB}")
        # 在这里执行您的逻辑
    endforeach()
endif()
message("==========${EVENT2_LIBRARY}")

set(EVENT2_INCLUDE_DIRS ${EVENT2_INCLUDE_DIR})
set(EVENT2_LIBRARIES ${EVENT2_LIBRARY})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(EVENT2
    REQUIRED_VARS
        EVENT2_LIBRARY
        EVENT2_INCLUDE_DIR
    VERSION_VAR EVENT2_VERSION)

mark_as_advanced(EVENT2_INCLUDE_DIR EVENT2_LIBRARY)

if(EVENT2_PREFER_STATIC_LIB)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${EVENT2_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})
    unset(EVENT2_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES)
endif()
