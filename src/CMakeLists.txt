# Main source directory

# Add config include
include_directories("${PROJECT_BINARY_DIR}/config")

# Add project include
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add library include
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_library(simwar-lib
#	battle.cpp
	entity.cpp
#	client.cpp
#	hero.cpp
	director.cpp
	role.cpp
	team.cpp
	program.cpp
)

#add_executable(simwar main.cpp)
#target_link_libraries(simwar simwar-lib lua5.3-lib)

add_executable(simwar-test test.cpp)
target_link_libraries(simwar-test simwar-lib lua5.3-lib)
