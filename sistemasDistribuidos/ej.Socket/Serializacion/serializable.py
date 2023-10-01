#!/usr/bin/env python3

import pickle

# Crear un diccionario como objeto
data = {
    'nombre': 'Juan',
    'edad': 30,
    'ciudad': 'Ejemploville'
}

# Serializar el objeto en un archivo
with open('datos.pkl', 'wb') as archivo:
    pickle.dump(data, archivo)

# Deserializar el objeto desde el archivo
with open('datos.pkl', 'rb') as archivo:
    datos_cargados = pickle.load(archivo)

# Mostrar los datos cargados
print(datos_cargados)
