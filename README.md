# PDA Simulator (Práctica 1)

Proyecto C++17 con diseño orientado a objetos para simular un autómata con pila (APv o APf).

## Estructura

- `include/pda/` Cabeceras del núcleo del simulador (solo declaraciones).
- `src/` Ficheros `.cpp` con implementaciones (ahora placeholders vacíos).
- `data/examples/` Ejemplos de definiciones de autómatas.
- `tests/` Carpeta para pruebas unitarias o de integración (opcional).
- `Makefile` y `CMakeLists.txt` para compilar.

## Elección del tipo (APv/APf)

Indica aquí qué modalidad implementarás:

- [ ] APv (aceptación por vaciado de pila)
- [ ] APf (aceptación por estado final)

Actualiza esta sección cuando lo decidas. El parser y la simulación deben validar la definición según la modalidad elegida.

## Formato del fichero de entrada

Sigue exactamente el descrito en `practica.txt`. En este proyecto el símbolo epsilon del alfabeto de entrada se manejará como `'.'` en el fichero y se convertirá a `EPSILON` internamente (char `\0`). Para la secuencia de apilado `A` se acepta `.` para epsilon o una cadena de símbolos de `Γ` sin espacios.

## Compilación

Con CMake:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/pda
```

Con Makefile sencillo:

```sh
make
./bin/pda
```

## Uso (skeleton)

```sh
./pda <definition_file> [--trace] [--mode=APv|APf]
```

## Notas de diseño

- `Types.hpp`: tipos básicos y `AcceptanceMode`.
- `State.hpp`: representación mínima de un estado.
- `Transition.hpp`: transición `(q, a, X) -> (p, γ)`; decide coherentemente la orientación de `pushSeq` al implementar.
- `PDA.hpp`: interfaz pública del simulador (setters, consultas y `accepts`).
- `Parser.hpp`: parseo del formato indicado y verificación de restricciones formales (p.ej., `s ∈ Q`).
- `TraceLogger.hpp`: soporte opcional de traza por paso.

## Próximos pasos sugeridos

1. Implementar `Parser` leyendo el fichero y construyendo `PDA`.
2. Definir la orientación de la pila y ejecutar transiciones con backtracking/DFS/BFS no determinista.
3. Implementar `accepts` según la modalidad elegida (APv/APf).
4. Añadir modo traza (`--trace`) que imprima estado, entrada restante, pila y transiciones aplicables.
5. Añadir pruebas con varios autómatas del aula virtual.
