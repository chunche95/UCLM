#!/bin/bash
echo "Estado  actual"
git st
echo "Añadiendo archivos"
git add .
echo "Preparando nota para los archivos"
git nota $1
echo "Subiendo archivos"
git main
