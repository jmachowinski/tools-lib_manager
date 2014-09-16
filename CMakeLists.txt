project(lib_manager)
set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "A library for loading dynamic libraries")
cmake_minimum_required(VERSION 2.6)

if(WIN32)
    # this fixes the error 998 from the LibManager
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--enable-auto-import")
    set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--enable-auto-import")
else(WIN32)
    set(CMAKE_CXX_FLAGS "-fPIC")
endif(WIN32)
  
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

set(SOURCES 
    src/LibManager.cpp
)
set(HEADERS
    src/LibInterface.h
    src/LibManager.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})

if(UNIX)
    target_link_libraries(${PROJECT_NAME} dl)
    target_link_libraries(${PROJECT_NAME}_static dl)
endif(UNIX)

if(WIN32)
    set(LIB_INSTALL_DIR bin) # .dll are in PATH, like executables
else(WIN32)
    set(LIB_INSTALL_DIR lib)
endif(WIN32)


set(_INSTALL_DESTINATIONS
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION lib
)


# Install the library into the lib folder
install(TARGETS ${PROJECT_NAME} ${_INSTALL_DESTINATIONS})
install(TARGETS ${PROJECT_NAME}_static ${_INSTALL_DESTINATIONS})

# Install headers into mars include directory
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

# Prepare and install necessary files to support finding of the library 
# using pkg-config
configure_file(src/${PROJECT_NAME}.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)
