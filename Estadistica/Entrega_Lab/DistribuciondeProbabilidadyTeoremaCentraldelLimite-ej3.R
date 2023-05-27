# Tasa media de fallos
lambda <- 0.2

# Probabilidad deseada
probabilidad_deseada <- 0.99

# Calcula el tiempo necesario para asegurar con la probabilidad deseada
tiempo_cambio <- -log(probabilidad_deseada) / lambda

# Imprime el resultado
tiempo_cambio