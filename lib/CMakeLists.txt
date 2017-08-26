
file(GLOB SOURCES "*.cc")

include_directories("../include")

add_library(libcursed STATIC ${SOURCES})
target_link_libraries(libcursed "ncursesw")
set_target_properties(libcursed PROPERTIES
	OUTPUT_NAME "cursed"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	PREFIX "lib" )

install(
	TARGETS libcursed
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib)

install(
	DIRECTORY "../include/cursed"
	DESTINATION "include")
