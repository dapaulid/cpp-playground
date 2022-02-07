set(CMAKE_CXX_STANDARD 17)

add_library(mylibrary mylibrary.cpp)
set_target_properties(mylibrary PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/mylibrary.h
)

if(PLATFORM STREQUAL "web")
	set_target_properties(mylibrary PROPERTIES COMPILE_FLAGS "-s USE_PTHREADS")
	set_target_properties(mylibrary PROPERTIES LINK_FLAGS "--emrun -s NO_EXIT_RUNTIME -s USE_PTHREADS -s PROXY_TO_PTHREAD")
	target_link_libraries(mylibrary -lwebsocket)
endif()
