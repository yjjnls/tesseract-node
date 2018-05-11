
cam_find_gstreamer(1.14.0)


pkg_check_modules(GST_MODULES  REQUIRED
                   gstreamer-1.0>=1.14.0
                   gstreamer-base-1.0>=1.14.0
                )
include_directories(${GST_MODULES_INCLUDE_DIRS}) 
link_directories   (${GST_MODULES_LIBRARY_DIRS})
                