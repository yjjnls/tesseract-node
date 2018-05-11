set( __name__ tesseract-test)
project(${__name__})

file(GLOB_RECURSE  _SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.[ch] ${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]pp)
cam_project_group(_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

pkg_check_modules(_MODULES  REQUIRED
                   lept
                   tesseract
                )
include_directories(${_MODULES_INCLUDE_DIRS}) 
link_directories   (${_MODULES_LIBRARY_DIRS})


add_executable( ${__name__} ${_SOURCES} )

# lib to link
#
target_link_libraries(${__name__} ${_MODULES_LIBRARIES} )


#install(TARGETS libwebstreamer RUNTIME DESTINATION )

#add_test(NAME run-executale
#         COMMAND ${__name__}
#         WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY})


#SET_TESTS_PROPERTIES("ENVIRONMENT"
# PROPERTIES ENVIRONMENT "CURRENT_RUNING_PROJECT=${__name__}")
