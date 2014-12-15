#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
project(Exordium)

set(OGRE_PATH $ENV{OGRE_HOME} CACHE PATH "OGRE DIR")
#set(OGRE_PATH $ENV{OGRE_HOME} CACHE PATH "OGRE DIR")

include_directories(${OGRE_PATH}/include)
include_directories(${OGRE_PATH}/include/OIS)
include_directories(${OGRE_PATH}/include/OGRE)
include_directories(${OGRE_PATH}/include/OGRE/Overlay)
include_directories(${OGRE_PATH}/boost)

file(GLOB EXORDIUM_SOURCES
	src/*.cpp
	src/*.h
)

link_directories(${OGRE_PATH}/lib)
link_directories(${OGRE_PATH}/boost/lib)

IF(WIN32)
	SET(GUI_TYPE WIN32)
ENDIF(WIN32)
# Set some Apple MacOS Specific settings
IF (APPLE)
	SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

add_executable(Exordium ${GUI_TYPE} ${EXORDIUM_SOURCES})

# find_library(OGREMAIN_DEBUG_LIB OgreMain_d.lib)

target_link_libraries(Exordium
    debug OgreMain_d.lib
    debug OIS_d.lib
    debug OgreOverlay_d.lib
	optimized OgreMain.lib
    optimized OIS.lib
    optimized OgreOverlay.lib
)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

configure_file(${PROJECT_SOURCE_DIR}/ogrecfg/plugins_d.cfg
			${CMAKE_BINARY_DIR}/Debug/plugins_d.cfg COPY_ONLY)
configure_file(${PROJECT_SOURCE_DIR}/ogrecfg/plugins.cfg
			${CMAKE_BINARY_DIR}/Release/plugins.cfg COPY_ONLY)
		
add_custom_command(TARGET Exordium POST_BUILD
		   COMMAND ${CMAKE_COMMAND} -E copy_directory
			   ${OGRE_PATH}/bin/$(Configuration) $<TARGET_FILE_DIR:Exordium>)
