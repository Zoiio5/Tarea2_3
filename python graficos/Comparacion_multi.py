import pandas as pd
import matplotlib.pyplot as plt
import math

# Cargar los datos desde un archivo CSV
data = pd.read_csv('../resultados_multi.csv')

# Lista de casos únicos
casos = data['Caso'].unique()

# Crear un gráfico para cada caso
for caso in casos:
    # Filtrar los datos para el caso actual
    df_caso = data[data['Caso'] == caso]

    # Obtener valores únicos de 'Tamaño_m'
    tamanos_m = df_caso['Tamaño_m'].unique()

    # Determinar el número de subgráficos (filas y columnas)
    num_plots = len(tamanos_m)
    num_cols = 3  # Número de columnas de subplots en cada figura
    num_rows = math.ceil(num_plots / num_cols)

    # Crear figura y subplots
    fig, axs = plt.subplots(num_rows, num_cols, figsize=(15, num_rows * 5))
    fig.suptitle(f'Comparación de Algoritmos para el Caso: {caso}', fontsize=16)

    # Ajustar axs para un índice fácil de manejar
    axs = axs.flatten()

    # Texto de índice de cada gráfico a la izquierda
    left_text = ""

    for i, tamano_m in enumerate(tamanos_m):
        # Filtrar los datos para el tamaño m actual
        df_m = df_caso[df_caso['Tamaño_m'] == tamano_m]

        # Crear texto del índice de m y rango de n
        n_min, n_max = df_m['Tamaño_n'].min(), df_m['Tamaño_n'].max()
        left_text += f'Tamaño_m = {tamano_m}, Tamaño_n = [{n_min}-{n_max}]\n'

        # Graficar Fuerza Bruta y Programación Dinámica para el tamaño m actual
        axs[i].plot(df_m['Tamaño_n'], df_m['TiempoFB (ns)'], label=f'FB', marker='o', linestyle='--')
        axs[i].plot(df_m['Tamaño_n'], df_m['TiempoDP (ns)'], label=f'DP', marker='o', linestyle='-')

        # Configurar título y etiquetas de cada subplot
        axs[i].set_title(f'Tamaño_m = {tamano_m}, Tamaño_n = [{n_min}-{n_max}]')
        axs[i].set_xlabel('Tamaño n')
        axs[i].set_ylabel('Tiempo (ns)')
        axs[i].legend()
        axs[i].grid(True)

    # Eliminar subplots vacíos en caso de que haya
    for j in range(i + 1, len(axs)):
        fig.delaxes(axs[j])

    # Añadir texto al borde izquierdo en blanco
    plt.figtext(0.02, 0.5, left_text, va="center", ha="left", fontsize=10, bbox=dict(facecolor="white", alpha=0.5))

    # Ajustar diseño y guardar la imagen
    plt.tight_layout(rect=[0.05, 0, 1, 0.96])
    plt.savefig(f'comparacion_{caso}.png')
    plt.show()
