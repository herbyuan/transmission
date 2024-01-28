add_executable(${TR_NAME}-ssltest)

target_sources(${TR_NAME}-ssltest
    PRIVATE
        ssltest.cc)

target_link_libraries(${TR_NAME}-ssltest
    PRIVATE
        Threads::Threads
        deflate::deflate
        transmission::crypto_impl
        CURL::libcurl
        FastFloat::fast_float
        psl::psl
        natpmp::natpmp
        miniupnpc::libminiupnpc
        dht::dht
        libutp::libutp
        libb64::libb64
        ${LIBINTL_LIBRARY}
        ${LIBM_LIBRARY}
        ${LIBQUOTA_LIBRARY}
        ${TR_NETWORK_LIBRARIES}
        jsonsl
        utf8::cpp
        wildmat
        WideInteger::WideInteger
        $<$<BOOL:${WIN32}>:crypt32>
        $<$<BOOL:${WIN32}>:shlwapi>
        "$<$<BOOL:${APPLE}>:-framework Foundation>"
    PUBLIC
        fmt::fmt-header-only
        libevent::event)

tr_win32_app_info(${TR_NAME}-ssltest
    "Transmission Utility ('ssltest', obsolete)"
    "${TR_NAME}-ssltest"
    "${TR_NAME}-ssltest.exe")

install(
    TARGETS ${TR_NAME}-ssltest
    DESTINATION ${CMAKE_INSTALL_BINDIR})

