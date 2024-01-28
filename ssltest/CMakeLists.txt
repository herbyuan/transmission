add_executable(${TR_NAME}-ssltest)

target_sources(${TR_NAME}-ssltest
    PRIVATE
        ssltest.cc)

target_link_libraries(${TR_NAME}-ssltest
    PRIVATE
        transmission::crypto_impl
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

