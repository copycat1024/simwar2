# Server source directory

# Add project include
include_directories("${PROJECT_SOURCE_DIR}/include/server")

add_library(simwar-server
	battle.cpp
	director.cpp
	role.cpp
	team.cpp
	proxy.cpp
	logger.cpp

	api.cpp
	api_attack.cpp

	server.cpp
)
target_link_libraries(simwar-server
	lua5.3-lib
)
