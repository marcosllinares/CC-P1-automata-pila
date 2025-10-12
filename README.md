# Práctica 01 - Autómata con pila
Práctica que implementa un simulador básico de Autómata con Pila (PDA) con implementación por estados finales (APf). 

Enlace: [https://github.com/marcosllinares/CC-P1-automata-pila](https://github.com/marcosllinares/CC-P1-automata-pila)

## Autor
Trabajo realizado por Marcos Llinares Montes (alu0100972443)

## Estructura del proyecto
- `include/` : cabeceras (.hpp)
- `src/`     : implementación (.cpp)
- `data/`    : archivos de ejemplo (definiciones de autómatas y entradas)
- `build/`, `bin/` : artefactos de compilación (creados por `make`)

```
.
├── Makefile
├── README.md
├── data
│   ├── APf
│   │   ├── APf-1.txt
│   │   ├── APf-2.txt
│   │   └── APf-3.txt
│   └── Inputs
│       └── Input1.txt
├── include
│   ├── Alphabet.hpp
│   ├── PDA.hpp
│   ├── Parser.hpp
│   ├── State.hpp
│   ├── Symbol.hpp
│   ├── TraceLogger.hpp
│   └── Transition.hpp
└── src
    ├── Alphabet.cpp
    ├── PDA.cpp
    ├── Parser.cpp
    ├── State.cpp
    ├── Symbol.cpp
    ├── TraceLogger.cpp
    ├── Transition.cpp
    └── main.cpp
```

## Compilación
El proyecto se compila mediante `make` (Makefile incluido). Basta ejecutar desde la raíz del proyecto:

```sh
make
```

El binario resultante es `bin/pda`.

## Ejecución
Uso básico:

```sh
./bin/pda <definition_file> <inputs_file> [--trace]
```

- `definition_file`: fichero con la definición del PDA (APf) (ej. `data/APf/APf-1.txt`).
- `inputs_file`: fichero con cadenas de entrada, una por línea (ej. `data/Inputs/Input1.txt`).
- `--trace` (opcional): muestra información de trazas / transiciones.

Ejemplo:

```sh
./bin/pda data/APf/APf-1.txt data/Inputs/Input1.txt --trace
```

