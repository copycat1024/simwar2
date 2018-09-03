# Main source directory

# Add config include
include_directories("${PROJECT_BINARY_DIR}/config")

# Add project include
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add project include
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_subdirectory("server") # server source
add_subdirectory("client") # client source
add_subdirectory("combi")  # combinatorics source

add_library(simwar-core
	program.cpp
)
target_link_libraries(simwar-core
	simwar-server
	simwar-client
	simwar-combi
)

add_executable(simwar simwar.cpp)
target_link_libraries(simwar
	simwar-core
)

add_executable(test_server test_server.cpp)
target_link_libraries(test_server
	simwar-core
)

add_executable(test_client test_client.cpp)
target_link_libraries(test_client
	simwar-core
)

add_executable(test_combi test_combi.cpp)
target_link_libraries(test_combi
	simwar-core
)

add_executable(formation_rating formation_rating.cpp)
target_link_libraries(formation_rating
	simwar-core
)
