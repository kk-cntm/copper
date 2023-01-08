set(CMAKE_CXX_STANDARD 17)

project(CopperTests)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fixtures/BaseApplicationTest.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fixtures/BaseApplicationTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Resource/BundleSerializeDeserializeTest.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DEBUG CPR_ENABLE_ASSERTS CPR_ENABLE_PROFILER)
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_RELEASE CPR_ENABLE_PROFILER)
elseif (CMAKE_BUILD_TYPE STREQUAL Dist)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DIST)
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor/spdlog/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/src)
target_include_directories(${PROJECT_NAME} PRIVATE src)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_dependencies(${PROJECT_NAME} CopperCore)

target_link_libraries(${PROJECT_NAME} CopperCore gtest)
