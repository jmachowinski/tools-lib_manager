rock_library(lib_manager
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(lib_manager_bin Main.cpp
    DEPS lib_manager)

