
## Código Fuente
El código fuente que implementa los métodos de Eliminación Gaussiana y de Factorización LU puede encontrarse dentro de la carpeta tp1/src. Los tests unitarios están construidos utilizando la biblioteca GTest.

## Requisitos
Es necesario contar con los siguientes programas instalados:
* CMake (3.11 o superior).
* Algún C++ Compiler (con soporte para C++17 en adelante).

## Compilación
Dentro de la carpeta src, se encuentra el archivo CMakeLists.txt. Se deben ejecutar los siguientes comandos:
* cmake CMakeLists.txt
* cmake --build . --config Release 

## Ejecución
Finalizada la compilación, dentro de la carpeta *Release* (o Debug, dependiendo de la configuración utilizada) vamos a encontrar los siguientes ejecutables:
* tp1 (tp1.exe)
* tp1Test (tp1Test.exe)

El primero puede ejecutarse de la siguiente manera:
```
$ tp1 <archivo de entrada> <archivo de salida> <metodo>
```

Ejemplo para ejecutar EG:
```
$ tp1 tests_alu\test1.in tests_alu\test1.out 0
```

Para ejecutar LU:
```
$ tp1 tests_alu\test2.in tests_alu\test2.out 1
```

También debería ser posible ejecutar los test unitarios de la siguiente manera:
Para ejecutar LU:
```
$ tp1test
```

## Otros
Hay otras carpetas como *exp* o *scripts* que contienen Jupyter Notebooks o scripts de Python que se utilizaron con propósitos de experimentación.
