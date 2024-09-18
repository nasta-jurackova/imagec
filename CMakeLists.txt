cmake_minimum_required(VERSION 3.28)

project(imagec CXX)

find_package(Qt6 CONFIG REQUIRED)
set(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS} Qt6::Widgets Qt6::Core Qt6::Gui)

set(IMAGEC_COMPILE_FLAGS /W4)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOUIC TRUE)

set(CORE_SOURCES 
	src/core/image.cpp
)
set(GUI_SOURCES
	src/gui/AppManagerSingleton.cpp
	src/gui/windows/MainWindow.cpp
	src/gui/windows/ImageWindow.cpp
	src/gui/windows/ParametersDialog.cpp
	src/gui/utils/image.cpp
	src/gui/widgets/ImageWithInfoWidget.cpp
	src/gui/widgets/ZoomableImageWidget.cpp
)

set(ALGO_SOURCES
	src/algorithms/AlgorithmBase.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp 
	${CORE_SOURCES} 
	${GUI_SOURCES} 
	${ALGO_SOURCES}
)
target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_link_libraries(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${IMAGEC_COMPILE_FLAGS})
