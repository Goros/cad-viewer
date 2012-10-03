set(PROJECT cad-viewer)

project(${PROJECT})

cmake_minimum_required(VERSION 2.6.0)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

#qt4_add_resources(CAD_RCS cad.qrc)

set (CMAKE_BUILD_TYPE "Release")
set (CMAKE_CXX_FLAGS "-Wall")

set (SRC_DIR ../src)

set(SOURCES
    ${SRC_DIR}/gui/actionlist.cpp
    ${SRC_DIR}/gui/cadviewerapplication.cpp
    ${SRC_DIR}/gui/childwindow.cpp
    ${SRC_DIR}/gui/inventorviewer.cpp
    ${SRC_DIR}/gui/mainwindow.cpp
    ${SRC_DIR}/gui/mainwindow_ui.cpp
    ${SRC_DIR}/gui/model.cpp
    ${SRC_DIR}/gui/view.cpp
    ${SRC_DIR}/main.cpp
	${CAD_RCS}
)

set(HEADERS
    ${SRC_DIR}/gui/cadviewerapplication.h
    ${SRC_DIR}/gui/childwindow.h
    ${SRC_DIR}/gui/inventorviewer.h
    ${SRC_DIR}/gui/mainwindow.h
    ${SRC_DIR}/gui/model.h
    ${SRC_DIR}/gui/view.h
)

if (UNIX)
	find_package(X11 REQUIRED)

	set(OPENCASCADE_INCLUDE
		/usr/include/opencascade
	)
endif()

find_package(OpenGL REQUIRED)

set(OPENCASCADE_LIB
	TKernel
	PTKernel
	TKG3d
	TKMath
	TKBRep
	TKIGES
	TKSTL
	TKSTEP
	TKSTEPAttr
	TKSTEP209
	TKSTEPBase
	TKShapeSchema
	TKGeomBase
	TKGeomAlgo
	TKXSBase
	TKPShape
	TKShHealing
	TKHLR
	TKTopAlgo
	TKMesh
	TKPrim
	TKCDF
	TKBool
	TKBO
	TKFillet
	TKOffset
)

set (coin3d_lib
	Coin
	SoQt4
)

set (base_directory .)

if (WIN32)
	set (WINDOWS_INCLUDE
		c:/opencascade/ros/inc
		c:/boost_1_46_1/libs
		c:/SoQt/src
		c:/coin/include)

	add_definitions(-DWNT)
	add_definitions(-DWIN32)
	add_definitions(-D_WINDOWS)
	add_definitions(-DSOQT_DLL)
	add_definitions(-DCOIN_DLL)

	set (OPENCASCADE_LIB_DIR
		c:/opencascade/ros/win32/vc9/lib)

	set (COIN_LIB_DIR
		c:/coin/lib)

	link_directories(${OPENCASCADE_LIB_DIR} ${COIN_LIB_DIR})
endif()

include_directories(${CMAKE_SOURCE_DIR} ${OPENCASCADE_INCLUDE} ${SRC_DIR}
	${base_directory} ${base_directory}/gui
	${base_directory}/gui/widget
	${base_directory}/common ${base_directory}/action
	${base_directory}/sketcher/gui ${base_directory}/sketcher/mod ${base_directory}/gui/command
	${base_directory}/sketcher/command ${base_directory}/sketcher ${WINDOWS_INCLUDE})

qt4_wrap_cpp(SOURCES ${HEADERS})

if (UNIX)
  add_executable(${PROJECT} ${SOURCES})
  target_link_libraries(${PROJECT} ${QT_LIBRARIES} ${OPENCASCADE_LIB} ${OPENGL_LIBRARIES} ${QT_QTOPENGL_LIBRARY} ${coin3d_lib})
elseif(WIN32)
  add_executable(${PROJECT} WIN32 ${SOURCES})
  target_link_libraries(${PROJECT} ${QT_LIBRARIES} ${OPENCASCADE_LIB} ${OPENGL_LIBRARIES} ${QT_QTOPENGL_LIBRARY} ${coin3d_lib} ${QT_QTMAIN_LIBRARY})
endif()
