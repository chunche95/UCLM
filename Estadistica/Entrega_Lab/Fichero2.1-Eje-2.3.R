# Datos
numeros <- c(1.17, 1.61, 1.16, 1.38, 3.53, 1.23, 3.76, 1.94, 0.96, 3.78, 0.15, 2.41, 0.71, 0.02, 1.59, 0.19, 0.82, 0.47, 2.16, 2.01)
intervalos <- cut(numeros, breaks = c(0.02, 0.96, 1.90, 2.84, 3.78))

# Tabla de distribución de fercuencias
table(intervalos)
frec_absolutas <- table(intervalos)
frec_relativas <- prop.table(frec_absolutas)
limites_intervalos <- levels(intervalos)
marcas_clase <- sapply(limites_intervalos, function(x) {
  lim <- as.numeric(strsplit(x, ",")[[1]])
  mean(lim)
})
tabla <- data.frame(Límites = limites_intervalos, FrecuenciaAbsoluta = frec_absolutas, FrecuenciaRelativa = frec_relativas, MarcaClase = marcas_clase)

# Histogram
hist(numeros, breaks = c(0.02, 0.96, 1.90, 2.84, 3.78), main = "Histogram", xlab = "Values", ylab = "Frequency", col = "lightblue")
