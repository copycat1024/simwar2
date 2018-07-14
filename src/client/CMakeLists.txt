# Client source directory

# Add project include
include_directories("${PROJECT_SOURCE_DIR}/include/client")

add_library(simwar-client
	driver.cpp
	element.cpp

	client.cpp
)
target_link_libraries(simwar-client
	lua5.3-lib
)
