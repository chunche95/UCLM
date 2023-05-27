# Datos
X <- c(39, 42, 44, 46, 49)
Y <- c(104, 103.7, 103.4, 103.1, 103)

# Coeficiente de variación
CV_X <- sd(X) / mean(X) * 100
CV_Y <- sd(Y) / mean(Y) * 100

CV_X
CV_Y

# Coeficiente de correlación
correlation <- cor(X, Y)

correlation

# Predecir la cantidad de visitantes al zoológico correspondiente a un cierto número de días de lluvia
zoo <- data.frame(Visitantes = c(104, 103.7, 103.4, 103.1, 103),
                  Lluvia = c(39, 42, 44, 46, 49))
modelo <- lm(Visitantes ~ Lluvia, data = zoo)
prediccion <- predict(modelo, newdata = data.frame(Lluvia = 56))
predicción

# El coeficiente de determinación representa la proporción de la variabilidad total en Y que es explicada por el modelo de regresión lineal
x <- c (39, 42, 44, 46, 49)
y <- c (104, 103.7, 103.4, 103.1, 103)
r = cor (x, y)
r2 = r^2
r2