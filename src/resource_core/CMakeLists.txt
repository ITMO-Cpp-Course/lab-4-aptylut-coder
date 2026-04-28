add_library(resource_core
        src/FileHandle.cpp
        src/ResourceManager.cpp
)

target_include_directories(resource_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
