add_executable(client "${CMAKE_CURRENT_SOURCE_DIR}/client.cpp")
add_executable(server "${CMAKE_CURRENT_SOURCE_DIR}/server.cpp")

set(LINK_LIBRARIES "-lssl -lcrypto")

if(WIN32)

    set(LINK_LIBRARIES "${LINK_LIBRARIES} -lws2_32")

endif()

target_link_libraries(client torfs ${LINK_LIBRARIES})
target_link_libraries(server torfs ${LINK_LIBRARIES})