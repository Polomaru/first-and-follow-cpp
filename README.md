# first-and-follow-cpp
Primeros y Siguientes 

## Acerca 

Grammar First and Next, and also the LL(1) table I guess(?)

### Built With

* c++
* linux
* flex (?)

### Prerequisites

We need flex.
* flex
  ```sh
  sudo apt-get update
  sudo apt-get install flex	
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Polomaru/first-and-follow-cpp
   ```

## Usage

Para hacer uso de los primeros y siguientes, primero debe de tener una grámatica.
Esta grámatica tiene que estar bien separada, mediante espacios podemos separar las sentencias (` `) y las reglas mediante ` | ` , además que para poder separar un conjunto de reglas usamos ` -> `; de tal manera que puede quedar como alguno de los ejemplos que esta en la carpeta `grammars`


Por ejemplo:
```sh
  S -> A B C D E
  A -> a | _e
  B -> b | _e
  C -> c
  D -> d | _e
  E -> e | _e
```

Cabe aclarar que la palabra `_e` hace alución a `epsilon` y es una palabra reservada.


De momento, ahora solo corriendo. En la carpeta `sin`.

```sh
  g++ Gtest.cpp
  ./a.out	
```

Si necesita cambiar la grámatica, abre el archivo Gtest.cpp, y cambia por el otro nombre del archivo que está en la carpeta `grammars`.
Por ejemplo:

```c++
  Grammar reader("3"); //referenciandose al archivo 3.txt en la carpeta grammars.
```

## Funciones

De momento tenemos 2 funciones que están en la clase `Grammar`.

```c++
  unordered_map<string,vector<string>> first(); 
  // que te devuelve un unordered_map de los no terminales y sus primeros
```
```c++
  unordered_map<string,vector<string>> follow(unordered_map<string,vector<string>> first) 
  // que te devuelve un unordered_map de los no terminales y sus segundos, usando parte de los primeros.
```
# osuna
Compilar:
	flex fb.l
	g++ main.cpp lex.yy.cc

Ejecutar:
	./a.out < test.txt
