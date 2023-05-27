# Tasa de fallos por minuto
tasa_fallos <- 10^(-4)
# Número de minutos en el viaje
minutos_viaje <- 180
# Valor esperado o media
lambda <- tasa_fallos * minutos_viaje
# Número de eventos (fallos) que queremos calcular
k <- 1 # En este caso, queremos calcular la probabilidad de que falle al menos una vez.
# Calcula la probabilidad usando la distribución de Poisson
probabilidad <- 1 - ppois(k - 1, lambda)
# Imprime el resultado
probabilidad