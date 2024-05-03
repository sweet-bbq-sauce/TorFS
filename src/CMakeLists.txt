set(SOURCES

    "${CMAKE_CURRENT_SOURCE_DIR}/address/address.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/address/connect.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/address/listen.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/address/resolve.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/client/user/files.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/client/user/filesystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/client/user/user.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/client/client.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/command/procedures/files.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/command/procedures/filesystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/command/procedures/user.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/command/command.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/firewall/firewall.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/iosocket/iosocket.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/iosocket/read.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/iosocket/write.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/listener/listener.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/server/default.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/server/server.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/session/session.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/utils/misc.cpp"

)

add_library(torfs ${SOURCES})