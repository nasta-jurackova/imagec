cmake_minimum_required(VERSION 3.28)
project(imagec CXX)

find_package(Qt6 CONFIG REQUIRED)
set(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS} Qt6::Widgets Qt6::Core Qt6::Gui)

set(IMAGEC_COMPILE_FLAGS /W4)
set(CMAKE_AUTOMOC TRUE)

set(CORE_SOURCES 
	src/core/image.cpp
)
set(GUI_SOURCES
	src/gui/main_bar.cpp
	src/gui/image_dialog.cpp
	src/gui/image_label.cpp
	src/gui/parameters_dialog.cpp
	src/gui/main_window.cpp
)

set(ALGO_SOURCES
	src/algorithms/save.cpp
	src/algorithms/duplicate.cpp
	src/algorithms/change_name.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${CORE_SOURCES} ${GUI_SOURCES} ${ALGO_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_link_libraries(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${IMAGEC_COMPILE_FLAGS})


# Devel project
add_executable(devel devel/main.cpp devel/zoomable_image_widget.cpp devel/image_with_info_widget.cpp devel/main_window.cpp)
target_include_directories(devel PUBLIC devel/)
target_link_libraries(devel PRIVATE ${THIRD_PARTY_LIBS})
target_compile_options(devel PRIVATE ${IMAGEC_COMPILE_FLAGS})