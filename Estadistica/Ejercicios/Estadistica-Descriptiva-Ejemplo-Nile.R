## 
#  Ejc. 2.1 Fichero R Estadística Descriptiva, histograma, componentes de (hist).
#
# - Utilizar el ejemplo Nile para interpretar los componentes de la función hist utilizando,
# donde se puede el vocabulario de clase. Ejemplo: breaks – límites de intervalos
##

getwd()
########################
# Cargamos el fichero. #
########################
# Con la asignación anterior '<-' en el objeto wtime hemos introducido los datos del fichero.
# Debe estar en el directorio de trabajo para poderse cargar los datos.
wtime <- scan("F:/UCLM/2do/2º/ESTA/Lab/waitingtimes.txt") #Recordad: sentencia entre paréntesis -> muestra resultado
pwd
wtime
# Contiene los datos anuales del flujo del río Nilo a su paso por la presa de Asuan (Egipto) 
Nile
# Obtener información sobre su contenido y significado de cara a identificar mejor que tipo de variable es
# mejor consultar con ?discoveries
?discoveries
discoveries

mtcars$mpg
head(mtcars)
########################
# Graficos
########################
# Histograma hist()
par(mfrow = c(1,2))
hist(wtime);rug(wtime)
hist(Nile); rug(Nile)
hist(discoveries); rug(discoveries)
hist(mtcars$mpg); rug(mtcars$mpg)

# La clave es el area
# El histograma ha de leerse por áreas, dado que intenta mostrar la densidad de la distribución de probabilidad que hay detras de los datos.
# Dicha densidad se obtiene usando frecuencias relativas, en lugar de las absolutas. Para ello añadimos 'prob = TRUE'

par(mfrow = c(1,2))
hist(Nile, prob = T, col = "blue")

# Componentes
histog_Nilo <- hist(Nile) #guardamos el "objeto" generado con la función hist
# En dicho objeto se incluyen componentes, descritos en el apartado values el la ayuda de la función hist(), que se pueden obtener usando la funcion names()
names(histog_Nilo)

# Explicar c/u de los componentes usando '$'
histog_Nilo$breaks # puntos de corte, extremis de los intervalos.
histog_Nilo$count # numero de datos includios en cada clase

# Argumentos.
# Por defecto las clases son cerradas en su extremo superior, si se quiere que sean en su extremo inferior, debemos lanzar 'rigth = FALSE'
hist(Nile, right=FALSE)$count
# Ayuda
?hist
# Sugerir el numero de clases en las que se deben agrupar los datos, añadiendo el argumento 'breaks = '
hist(wtime, breaks = 4)$breaks
length(hist(wtime, breaks = 30)$breaks)

########################
## BOXPLOT boxplot()  ##
########################
# Grafico que resume la variabilidad contenida en una variable - continua o discreta - Se construye calculando los cuartiles Q1Q1, Q2 = Me·Q2 = Me Y Q3Q3.
# y el rango intercuartilico IQR.
#
# Se usa para detectar valores atipicos/outliers.
par(mfrow = c(1,2))
boxplot(Nile, horizontal = T); rug(Nile)

boxplot(wtime, horizontal = TRUE); rug(wtime)
# Encontramos 4 puntos atípicos
boxplot(c(discoveries, 2, horizontal = T))$out

# El componente $stats proporciona los cinco valores siguientes basados en los cuartiles.
boxplot(discoveries, plot = T)$stats

# fivenum() y boxplot()$stats.
# Proporcionan 5 valores y podrían pensarse que son los citados arriba, pero 'fivenum' obtiene los definidos por Tukey.
# el mínimo, los 3 cuartiles y el máximo de los datos.
fivenum(discoveries)


#############################################
## Diagramas de barras barplot()
#############################################
par(mfrow = c(1,2))
barplot(table(discoveries))
hist(discoveries); rug(discoveries)

par(mfrow = c(1,2))
barplot(table(wtime))
hist(wtime); rug(wtime)

par(mfrow = c(1,2))
barplot(table(Nile))
hist(Nile); rug(Nile)

par(mfrow = c(1,2))
barplot(table(mtcars$mpg))
hist(mtcars$mpg); rug(mtcars$mpg)

#############################################
## CALCULO DE MEDIDAS DE RESUMEN
#############################################
summary(wtime)
summary(Nile)
summary(discoveries)

#############################################
## MEDIDAS DE CENTRALIZACIÓN
#############################################
mean(wtime); median(wtime)
mean(Nile); median(Nile)
mean(discoveries); median(discoveries)

# Interpretacion
hist(wtime)
abline(v = mean(wtime), col='red')
abline(v = median(wtime), col='blue')

hist(Nile)
abline(v = mean(Nile), col='red')
abline(v = median(Nile), col='blue')

hist(discoveries)
abline(v = mean(discoveries), col='red')
abline(v = median(discoveries), col='blue')
