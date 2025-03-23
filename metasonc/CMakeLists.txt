find_package(peff REQUIRED)

add_executable(metasonc)

file(GLOB HEADERS *.h)
file(GLOB SRC *.cc)

target_sources(metasonc PRIVATE ${HEADERS} ${SRC})
target_link_libraries(metasonc PRIVATE peff_containers_static)
