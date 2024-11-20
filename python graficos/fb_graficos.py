import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

# Cargar el archivo CSV
csv_path = "../resultado_fb.csv"  # Cambia esto a la ubicación de tu archivo CSV
df = pd.read_csv(csv_path)

# Convertir tiempo de nanosegundos a milisegundos
df["Tiempo (ms)"] = df["Tiempo (ns)"] / 1e6


# Definir la función exponencial para el ajuste
def exponencial(x, a, b):
    return a * np.exp(b * x)


# Configuración del gráfico
plt.figure(figsize=(12, 8))

# Graficar un scatter plot y el ajuste exponencial para cada tipo
tipos = df["Tipo"].unique()
for tipo in tipos:
    tipo_df = df[df["Tipo"] == tipo]
    x_data = tipo_df["Tamaño"]
    y_data = tipo_df["Tiempo (ms)"]

    # Realizar el ajuste exponencial
    try:
        params, _ = curve_fit(exponencial, x_data, y_data, p0=(1, 0.1))
    except RuntimeError:
        print(f"No se pudo ajustar el tipo {tipo}")
        continue

    # Graficar los puntos
    plt.scatter(x_data, y_data, label=f"{tipo} - Datos", s=60, alpha=0.7)

    # Graficar la curva de ajuste
    ajuste_x = np.linspace(x_data.min(), x_data.max(), 100)
    ajuste_y = exponencial(ajuste_x, *params)
    plt.plot(ajuste_x, ajuste_y, linestyle="--", label=f"{tipo} - Ajuste Exponencial")

# Configuración de etiquetas y leyenda
plt.xlabel("Tamaño")
plt.ylabel("Tiempo (ms)")
plt.title("Gráfico de Dispersión: Tamaño vs Tiempo (ms) con Ajuste Exponencial para cada Tipo")
plt.legend(title="Tipo y Ajuste")
plt.grid(True)

# Mostrar el gráfico
plt.show()
