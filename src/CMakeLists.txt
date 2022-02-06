set(CMAKE_CXX_STANDARD 17)

add_library(mylibrary mylibrary.cpp)
set_target_properties(mylibrary PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/mylibrary.h
)
