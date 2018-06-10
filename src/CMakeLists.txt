# Main source directory

# Add config include
include_directories("${PROJECT_BINARY_DIR}/config")

# Add project include
include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(simwar-lib
	battle.cpp
	entity.cpp
	client.cpp
	hero.cpp
	test.cpp
)

add_executable(simwar main.cpp)
target_link_libraries(simwar simwar-lib lua5.3-lib)

add_executable(devtest test.cpp)
target_link_libraries(devtest simwar-lib lua5.3-lib)
