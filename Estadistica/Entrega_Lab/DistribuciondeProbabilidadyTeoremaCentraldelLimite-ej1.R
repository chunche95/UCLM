# Número de ensayos
n <- 100
# Número de éxitos
k <- 100
# Probabilidad de éxito en un solo ensayo
p <- 0.998
# Calcula la probabilidad usando la distribución binomial
probabilidad <- choose(n, k) * p^k * (1 - p)^(n - k)
# Imprime el resultado
probabilidad