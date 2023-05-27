# Se ha medido el tiempo de reparación (en horas) y el coste (en euros) de un conjunto de instrumentos electrónicos. Los tiempos de reparación de varios instrumentos elegidos al azar es el siguiente:
#   
#   159, 280, 101, 212, 224, 379, 179, 264
# 
# Y sus costes:
#   
#   23.12, 43.15, 34.95, 54.23, 65.65, 22.45, 45.78, 87.65
# 
# Escriba el código necesario para:
#   
# · Crear un vector con los tiempos de reparación y otro con los costes.
# ..............................................................................
tiempos_reparacion <- c(159, 280, 101, 212, 224, 379, 179, 264)
costes_reparacion <- c(23.12, 43.15, 34.95, 54.23, 65.65, 22.45, 45.78, 87.65)
# ..............................................................................
# · Utilizar las funciones min y max para identificar el tiempo de reparación más alto y más bajo.
t_reparacion_mas_bajo = min(tiempos_reparacion)
t_reparacion_mas_alto = max(tiempos_reparacion)
# · Identificar las posiciones en el vector que ocupan los costes de reparación mínimo y máximo.
#     Obs: Existen diversas alternativas. Si se decanta por evaluar la condición de igualdad recuerde que el operador es == (no confundir con =).
# ..............................................................................
posicion_min_coste <- which( costes_reparacion == min(costes_reparacion))
posicion_max_coste <- which( costes_reparacion == max(costes_reparacion))
# ..............................................................................
# · Transformar el vector de tiempos en un nuevo vector en el que los tiempos de reparación se expresen en días.
tiempo_dias <- tiempos_reparacion / 24
# · Eliminar de dicho vector los valores mínimo y máximo.
#     Obs: para eliminar más de un elemento de un vector, además de usar el signo - es necesario “combinar” vector[c(-i, -j)].
tiempo_dias <- tiempo_dias[-which(tiempo_dias == t_reparacion_mas_bajo | tiempo_dias == t_reparacion_mas_alto)]
# · Crear un nuevo data frame llamado reparaciones que contenga los datos de tiempo y costes de todos los instrumentos.
reparaciones <- data.frame(tiempo = tiempos_reparacion, coste = costes_reparacion)
# · ¿Cuáles son los nombres de las columnas del nuevo data frame?
colnames(reparaciones)
# · Acceder a los datos de reparaciones de los instrumentos impares.
#     Ayuda: por ejemplo seq(from = ..., to = ..., by = ...)
reparaciones_impares <- reparaciones[seq(from = 1, to = nrow(reparaciones), by = 2)]