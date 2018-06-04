# Config directory

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/config/config.h.in"
  "${PROJECT_BINARY_DIR}/config/config.h"
)
