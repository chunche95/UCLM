x<-c(4139,5101,6018,7234,9178,11224,13156)
y<-c(2968,3635,4288,5226,6649,8065,9476)
# a

#Relacionamos Private con gross siendo Private dependiente de Gross
model <- y~x
#lm() se encarga de hacer el ajuste del modelo de regresion
reg <- lm(model)
#Representacion
par(pty = "s")
plot(model, main="Diagrama de dispersión", xlab = "X", ylab="Y")
abline(reg, col="red")


# b

r = cor (x, y, method = "pearson")
r 


# c

r = cor (x, y, method = "pearson")
r2 = r^2
r2

# d

# Coeficientes de la línea de regresión
beta_0 <- coef(model)[1]
beta_1 <- coef(model)[2]

# Valores de PIB para estimar el PDC
GDP_estimado <- c(10000, 150000)

# Estimación del PDC correspondiente
PDC_estimado <- beta_0 + beta_1 * GDP_estimado
PDC_estimado
