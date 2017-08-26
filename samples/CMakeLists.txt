
include_directories("../include")

add_executable(simple "simple.cc")
target_link_libraries(simple libcursed "ncursesw")
set_target_properties(simple PROPERTIES
	OUTPUT_NAME "simple"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")


add_executable(components "components.cc")
target_link_libraries(components libcursed "ncursesw")
set_target_properties(components PROPERTIES
	OUTPUT_NAME "components"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
