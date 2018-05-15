project(tesseract-plugin)

file(GLOB_RECURSE  _SOURCES 
     ${CMAKE_CURRENT_SOURCE_DIR}/*.[ch] 
     ${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]pp)

cam_project_group( _SOURCES ${CMAKE_CURRENT_SOURCE_DIR})

cam_find_pkgconfig( 0.29.1 )
pkg_check_modules(_MODULES  REQUIRED
                   lept
                   tesseract
                )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${_MODULES_INCLUDE_DIRS}) 
link_directories   (${_MODULES_LIBRARY_DIRS})

add_library(tesseract-plugin  SHARED ${_SOURCES} )
target_link_libraries(tesseract-plugin ${_MODULES_LIBRARIES} )


set(instd ${CMAKE_HOME_DIRECTORY}/bin)
if( MSVC )
	set(instd ${instd}/win )
else()
	set(instd ${instd}/linux )
endif()

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL AMD64 )
    set(instd "${instd}/x64")
else()
	set(instd "${instd}/x86")
endif()

install(TARGETS tesseract-plugin RUNTIME DESTINATION ${instd})

#set(npm npm)
#if(MSVC)
#	set(npm npm.cmd)
#endif()
#add_test(NAME npm-install
#         COMMAND ${npm} install webstreamer -s
#		 WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY})
# 
#add_test(NAME run-webstreamer-test
#         COMMAND ${npm} test
#		 WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/node_modules/webstreamer)
#
#SET_TESTS_PROPERTIES(run-webstreamer-test
# PROPERTIES ENVIRONMENT "LIBWEBSTREAMER_PATH=${instd}")
