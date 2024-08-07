cmake_minimum_required(VERSION 3.28)
project(imagec CXX)

find_package(Qt6 CONFIG REQUIRED)
set(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS} Qt6::Widgets Qt6::Core Qt6::Gui)

set(IMAGEC_COMPILE_FLAGS /W4 /wd4250)
set(CMAKE_AUTOMOC TRUE)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${IMAGEC_COMPILE_FLAGS})