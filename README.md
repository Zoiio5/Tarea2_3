# Proyecto de Algoritmos y Análisis de Rendimiento

Este repositorio contiene el código fuente y los scripts necesarios para realizar análisis de rendimiento de diversos algoritmos. Incluye herramientas para procesar datos, generar gráficas y comparar diferentes enfoques implementados en C++ y Python.

---

## Requisitos del Sistema

### Hardware
- **Procesador:** 12th Gen Intel(R) Core(TM) i7-12700H @ 2.70 GHz
- **RAM:** 16 GB
- **GPU:** No utilizada (NVIDIA GeForce RTX 3070 Ti y Intel Iris Xe Graphics)

### Software
- **Sistema Operativo:** Windows 11 Home (versión 22H2)
- **Compilador:** Microsoft C++ Compiler (MSVC) v14.34 o compatible
- **Python:** Versión 3.9 o superior
- **Librerías de Python:**
  - `numpy`
  - `pandas`
  - `matplotlib`

---

## Instalación

### Clonar el Repositorio
1. Abre una terminal y ejecuta:
   ```bash
   git clone https://github.com/Zoiio5/Tarea2_3.git
   cd Tarea2_3
## Configuración del Entorno C++
Instala CLion u otro IDE compatible con CMake.
Asegúrate de tener instalado el compilador MSVC o cualquier compatible con C++17.
Abre el proyecto en CLion. El archivo CMakeLists.txt configurará automáticamente el entorno.

## Compilación del Proyecto
1. Abre el proyecto en CLion o utiliza una terminal con CMake configurado.
Ejecuta el comando para compilar:
bash
Copiar código
cmake --build .
Los ejecutables se generarán en la carpeta cmake-build-debug (o similar).
Ejecución del Proyecto
Algoritmos en C++
Navega a la carpeta donde se generaron los ejecutables:
  ```bash
  Copiar código
  cd cmake-build-debug
Ejecuta el programa deseado:
bash
Copiar código
./nombre_del_programa
Por ejemplo:

  ```bash
  Copiar código
  ./algoritmo_fb
Procesamiento y Visualización en Python
Asegúrate de que el entorno virtual esté activado.
Ejecuta el script de procesamiento de datos:
bash
Copiar código
python procesar_datos.py
Genera las gráficas correspondientes:
bash
Copiar código
python graficar_resultados.py
