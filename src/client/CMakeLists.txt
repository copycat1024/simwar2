# Client source directory

# Add project include
include_directories("${PROJECT_SOURCE_DIR}/include/client")

add_library(simwar-client
	driver.cpp
	label.cpp
	progress_bar.cpp
	board.cpp
	client_model.cpp
	client_control.cpp
	client_view.cpp

	client.cpp
)
target_link_libraries(simwar-client
	lua5.3-lib
)
