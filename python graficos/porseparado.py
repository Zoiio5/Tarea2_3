import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Cargar los datos desde un archivo CSV
data = pd.read_csv('../resultados_varios_largos.csv')

# Obtener los casos únicos
casos_unicos = data['Caso'].unique()

# Determinar el número de filas (una por caso)
n_casos = len(casos_unicos)

# Crear la figura con subplots
fig = plt.figure(figsize=(16, 5 * n_casos))

# Iterar por cada caso y crear los gráficos FB y DP
for i, caso in enumerate(casos_unicos):
    # Filtrar los datos por caso
    data_caso = data[data['Caso'] == caso]

    # Crear la malla para la superficie
    X_mesh, Y_mesh = np.meshgrid(
        np.unique(data_caso['Tamaño_m']),
        np.unique(data_caso['Tamaño_n'])
    )

    # Preparar los datos para FB
    Z_mesh_FB = np.array(data_caso.pivot_table(index='Tamaño_m', columns='Tamaño_n', values='TiempoFB (ns)'))

    # Subplot para FB
    ax1 = fig.add_subplot(n_casos, 2, i * 2 + 1, projection='3d')
    surface_FB = ax1.plot_surface(X_mesh, Y_mesh, Z_mesh_FB, cmap='plasma', edgecolor='none')
    ax1.set_xlabel('Tamaño m')
    ax1.set_ylabel('Tamaño n')
    ax1.set_zlabel('Tiempo FB (ns)')
    ax1.set_title(f'Caso: {caso} - FB')
    fig.colorbar(surface_FB, ax=ax1, shrink=0.5, aspect=10)

    # Preparar los datos para DP
    Z_mesh_DP = np.array(data_caso.pivot_table(index='Tamaño_m', columns='Tamaño_n', values='TiempoDP (ns)'))

    # Subplot para DP
    ax2 = fig.add_subplot(n_casos, 2, i * 2 + 2, projection='3d')
    surface_DP = ax2.plot_surface(X_mesh, Y_mesh, Z_mesh_DP, cmap='viridis', edgecolor='none')
    ax2.set_xlabel('Tamaño m')
    ax2.set_ylabel('Tamaño n')
    ax2.set_zlabel('Tiempo DP (ns)')
    ax2.set_title(f'Caso: {caso} - DP')
    fig.colorbar(surface_DP, ax=ax2, shrink=0.5, aspect=10)

# Ajustar diseño para evitar solapamientos
plt.tight_layout()
plt.show()
