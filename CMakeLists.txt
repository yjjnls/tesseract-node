cmake_minimum_required(VERSION 2.8)
project(gsttesseract)

include(cam.camke)


enable_testing()
cam_compiler_flags()
cam_find_pkgconfig(0.29.1)

#find tesseract lib

##add_subdirectory( static )
add_subdirectory( plugin )
add_subdirectory( test   )
