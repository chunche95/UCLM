# Datos
GDP <- c(4139, 5101, 6018, 7234, 9178, 11224, 13156)
PDC <- c(2968, 3635, 4288, 5226, 6649, 8065, 9476)

# a) Gráfico de dispersión
plot(GDP, PDC, xlab = "PIB (GDP)", ylab = "Consumo Doméstico Privado (PDC)", main = "Gráfico de dispersión")

# b) Coeficiente de correlación y coeficiente de determinación
correlacion <- cor(GDP, PDC)
coef_determinacion <- correlacion^2

# Imprimir resultados
cat("Coeficiente de correlación:", correlacion, "\n")
cat("Coeficiente de determinación:", coef_determinacion, "\n")

# c) Línea de regresión
modelo <- lm(PDC ~ GDP)
abline(modelo, col = "red")

# d) Estimación del PDC para valores de GDP
GDP_estimado <- c(10000, 150000)
PDC_estimado <- predict(modelo, newdata = data.frame(GDP = GDP_estimado))

# Imprimir resultados
cat("Estimación del PDC para GDP =", GDP_estimado[1], ":", PDC_estimado[1], "\n")
cat("Estimación del PDC para GDP =", GDP_estimado[2], ":", PDC_estimado[2], "\n")
