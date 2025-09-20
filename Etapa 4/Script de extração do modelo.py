import numpy as np
import matplotlib.pyplot as plt

# Distâncias reais medidas (em centimetros)
distancia = np.array([10, 20, 40, 80, 160])

# Valores de RSSI correspondentes (em dBm)
db = np.array([-22, -28, -35, -46, -60])

# Cria matriz com termo de intercepto
distancia_com_intercepto = np.vstack([np.ones(len(distancia)), distancia]).T

# Regressão linear via equação normal
coeficientes = np.linalg.inv(distancia_com_intercepto.T @ distancia_com_intercepto) @ distancia_com_intercepto.T @ db

intercepto = coeficientes[0]
inclinacao = coeficientes[1]

print(f"Modelo Linear: db = {inclinacao:.2f} * distancia + {intercepto:.2f}")

# Valores previstos
db_previsto = inclinacao * distancia + intercepto

# Erro médio quadrático
mse = np.mean((db - db_previsto) ** 2)
print(f"Erro Quadrático Médio (MSE): {mse:.2f}")

# -----------------------------
# Plotando pontos e modelo
# -----------------------------
plt.scatter(distancia, db, color="blue", label="Valores Medidos")      # Pontos reais
plt.plot(distancia, db_previsto, color="red", label="Modelo Linear")   # Reta ajustada

plt.xlabel("Distância (m)")
plt.ylabel("RSSI (dBm)")
plt.title("Ajuste Linear: Distância vs RSSI")
plt.legend()
plt.grid(True)
plt.show()