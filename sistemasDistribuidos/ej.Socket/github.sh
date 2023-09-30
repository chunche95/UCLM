#!/bin/bash

# Script para bajar los cambios de los repositorios de github para sistemas distribuidos
s # git status del folder
baja main # es el pull de la rama main
git status # Revisamos de nuevo el estado del folder
ci -a $1 # Subir cambios con comentario a la rama
sube main # Sube los cambios a la rama main
