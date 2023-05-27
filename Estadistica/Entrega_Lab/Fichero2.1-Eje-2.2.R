# Datos de las temperaturas
temperaturas <- c(138, 167, 151, 170, 175, 138, 148, 153, 178, 142,
                  137, 157, 145, 146, 148, 155, 167, 142, 154, 133,
                  133, 152, 157, 149, 169, 159, 148, 150, 153, 145,
                  140, 161, 156, 149, 152, 140, 146, 151, 143, 140,
                  152, 138, 160, 153, 165, 157, 158, 162, 155, 144)
# Datos de intervalos
intervalos <- cut(temperaturas, breaks = c(131.5, 137.5, 143.5, 149.5, 155.5, 161.5, 167.5, 173.5, 179.5))

# Crear el archivo de texto
write.table(intervalos, "temperaturas.txt", row.names = FALSE, col.names = FALSE, quote = FALSE)

# Mensaje de confirmación
print("El archivo 'temperaturas.txt' ha sido creado y guardado correctamente.")

# Crear el histograma
histograma <- hist(temperaturas)

# Guardar el histograma en un archivo .R
save(histograma, file = "histograma.R")

# Mensaje de confirmación
print("El archivo 'histograma.R' ha sido creado y guardado correctamente.")


# Frecuencias absolutas
frec_absolutas <- table(intervalos)

# Frecuencias relativas
frec_relativas <- prop.table(frec_absolutas)

# Límites de intervalos
limites_intervalos <- levels(intervalos)

# Marcas de clase
marcas_clase <- sapply(limites_intervalos, function(x) {
  lim <- as.numeric(strsplit(x, ",")[[1]])
  mean(lim)
})

# Imprimir los resultados
resultado <- data.frame(Límites = limites_intervalos, FrecuenciaAbsoluta = frec_absolutas, FrecuenciaRelativa = frec_relativas, MarcaClase = marcas_clase)
print(resultado)