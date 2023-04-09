# CMakeList.txt: proyecto de CMake para Practica1.2, incluya el origen y defina
# la lógica específica del proyecto aquí.
#

# Agregue un origen al ejecutable de este proyecto.
add_executable (Practica1.2 "manager.c" "manager.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Practica1.2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
