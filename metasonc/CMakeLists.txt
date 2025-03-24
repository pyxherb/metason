find_package(peff REQUIRED)

add_executable(metasonc)

file(GLOB HEADERS *.h)
file(GLOB SRC *.cc)

target_sources(metasonc PRIVATE ${HEADERS} ${SRC})
target_link_libraries(metasonc PRIVATE peff_containers_static)
target_compile_definitions(metasonc PRIVATE METASONC_IS_BUILDING=1)
set_target_properties(metasonc PROPERTIES CXX_STANDARD 17)
