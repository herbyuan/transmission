foreach(P create edit remote show)
    add_executable(${TR_NAME}-${P})

    target_sources(${TR_NAME}-${P}
        PRIVATE
            ${P}.cc)

    if(CRYPTO_PKG STREQUAL "openssl")
        target_link_libraries(${TR_NAME}-${P}
            PRIVATE
                ${TR_NAME}
                CURL::libcurl
                fmt::fmt-header-only
                Libevent::core
                Libevent::extra
                Libevent::openssl)
    else()
        target_link_libraries(${TR_NAME}-${P}
            PRIVATE
                ${TR_NAME}
                CURL::libcurl
                fmt::fmt-header-only
                Libevent::core
                Libevent::extra)
    endif()

    tr_win32_app_info(${TR_NAME}-${P}
        "Transmission Utility ('${P}')"
        "${TR_NAME}-${P}"
        "${TR_NAME}-${P}.exe")

    install(
        TARGETS ${TR_NAME}-${P}
        DESTINATION ${CMAKE_INSTALL_BINDIR})

    if(INSTALL_DOC)
        install(
            FILES ${TR_NAME}-${P}.1
            DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
    endif()
endforeach()
