import pandas as pd
import matplotlib.pyplot as plt

# Cargar los datos desde un archivo CSV
data = pd.read_csv('resultado_dp.csv')

# Lista de casos únicos
casos = data['Caso'].unique()

# Crear gráficos separados por cada combinación de Caso y Tamaño_m
for caso in casos:
    # Filtrar los datos para el caso actual
    df_caso = data[data['Caso'] == caso]

    # Lista de tamaños únicos de 'Tamaño_m' dentro del caso
    tamanos_m = df_caso['Tamaño_m'].unique()

    for tamano_m in tamanos_m:
        # Filtrar los datos para el tamaño m actual dentro del caso
        df_m = df_caso[df_caso['Tamaño_m'] == tamano_m]

        # Gráfico para el método de Fuerza Bruta
        plt.figure(figsize=(10, 6))
        plt.plot(df_m['Tamaño_n'], df_m['TiempoFB (ns)'], label='Fuerza Bruta', color='blue', marker='o')
        plt.title(f'Caso: {caso} - Tamaño_m: {tamano_m} - Método: Fuerza Bruta')
        plt.xlabel('Tamaño n')
        plt.ylabel('Tiempo (ns)')
        plt.legend()
        plt.grid(True)
        plt.savefig(f'grafico_{caso}_m{tamano_m}_FuerzaBruta.png')
        plt.show()

        # Gráfico para el método de Programación Dinámica
        plt.figure(figsize=(10, 6))
        plt.plot(df_m['Tamaño_n'], df_m['TiempoDP (ns)'], label='Programación Dinámica', color='red', marker='o')
        plt.title(f'Caso: {caso} - Tamaño_m: {tamano_m} - Método: Programación Dinámica')
        plt.xlabel('Tamaño n')
        plt.ylabel('Tiempo (ns)')
        plt.legend()
        plt.grid(True)
        plt.savefig(f'grafico_{caso}_m{tamano_m}_ProgDinamica.png')
        plt.show()
