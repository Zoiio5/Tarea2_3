import pandas as pd
import matplotlib.pyplot as plt

# Cargar los datos desde el archivo CSV
df = pd.read_csv("../graficos m=n/resultados_n=m.csv")

# Lista de casos únicos
casos = df['Caso'].unique()

# Crear gráficos para cada caso
for caso in casos:
    # Filtrar los datos por el caso actual
    df_caso = df[df['Caso'] == caso]

    # Graficar los tiempos de FB y DP en función del tamaño
    plt.figure(figsize=(10, 6))
    plt.plot(df_caso['Tamaño'], df_caso['TiempoFB (ns)'], label='Fuerza Bruta (FB)', color='blue', marker='o')
    plt.plot(df_caso['Tamaño'], df_caso['TiempoDP (ns)'], label='Programación Dinámica (DP)', color='green', marker='o')

    # Títulos y etiquetas
    plt.title(f"Comparación de tiempos de ejecución: {caso}")
    plt.xlabel("Tamaño de Entrada")
    plt.ylabel("Tiempo (ns)")
    plt.legend()

    # Guardar el gráfico como archivo PNG y mostrarlo
    plt.savefig(f"{caso}_comparacion_tiempos.png")
    plt.show()
