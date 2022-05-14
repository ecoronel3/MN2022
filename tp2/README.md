# Reconocimiento de Dígitos

## Requisitos

- CMake 3.13 o superior
- Compilador de C++ con soporte para C++17
- Python 3

## Estructura
El proyecto se compone de los siguientes directorios:
- mn: Contiene la implementación de PCA y kNN escrita en C++.
- mnpy: Contiene los bindings para ejecutar los métodos de PCA y kNN desde Python.
- scripts: Disintos scripts de Python.
- tests: Casos de tests unitarios.

## Compilación
Para configurar y compilar el proyecto, se debe acceder a la carpeta tp2 y ejecutar los siguientes comandos:

```
$ mkdir build
$ cd build
$ cmake ..
```

## Documentación y Enlaces Útiles

- https://pybind11.readthedocs.io/en/stable/advanced/cast/eigen.html
- https://pybind11.readthedocs.io/en/stable/compiling.html#compiling
