project(Cmake_project)
cmake_minimum_required(VERSION 2.8)

include_directories(".")
include_directories("/opt/rh/devtoolset-7/root/usr/include/c++/7/")

link_directories("/opt/rh/devtoolset-7/root/usr/lib/")

add_definitions(${PCL_DEFINITIONS})

aux_source_directory(. SRC_LIST)
add_executable(fuidos.x fluido_pelotas.cpp Vector.cpp Vector.h Random64.h constantes.h cuerpo.cpp cuerpo.h colisionador.cpp colisionador.h)
