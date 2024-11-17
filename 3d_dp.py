import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Cargar los datos desde un archivo CSV
data = pd.read_csv('resultados_varios_largos.csv')

# Crear la malla para la superficie de DP
X_mesh, Y_mesh = np.meshgrid(
    np.unique(data['Tamaño_m']),
    np.unique(data['Tamaño_n'])
)
Z_mesh = np.array(data.pivot_table(index='Tamaño_m', columns='Tamaño_n', values='TiempoDP (ns)'))

# Configurar la figura y ejes
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# Graficar la superficie para el tiempo de DP
surface = ax.plot_surface(X_mesh, Y_mesh, Z_mesh, cmap='viridis', edgecolor='none')

# Etiquetas y título
ax.set_xlabel('Tamaño m')
ax.set_ylabel('Tamaño n')
ax.set_zlabel('Tiempo de Ejecución DP (ns)')
ax.set_title('Tiempo de Ejecución de DP en Función de Tamaño m y Tamaño n')

# Añadir barra de color
fig.colorbar(surface, ax=ax, shrink=0.5, aspect=10)

# Insertar la vista desde arriba en la esquina
ax_inset = fig.add_axes([0.7, 0.7, 0.25, 0.25], projection='3d')
ax_inset.plot_surface(X_mesh, Y_mesh, Z_mesh, cmap='viridis', edgecolor='none')
ax_inset.view_init(elev=90, azim=-90)  # Vista desde arriba
ax_inset.set_axis_off()  # Ocultar ejes en el gráfico de la esquina

# Mostrar la gráfica
plt.show()
