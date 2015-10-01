# Tp1Compus

Primera entrega: Jueves 24 de septiembre, 2015  
Devolución: Jueves 1° de octubre, 2015  

Última entrega y presentación: Jueves 8 de octubre, 2015  
  
  
### Versión Assembly  
El mismo se compila cómo:   
gcc -c proximo.S  
gcc -std=c99 -c matrix.c  
gcc -std=c99 -c tp.c  
gcc proximo.o matrix.o tp.o -o autcel  
  
  
### Versión C  
El mismo se compila cómo:  
```text```
gcc -std=c99 -c matrix.c  
gcc -std=c99 -c tp.c  
gcc matrix.o tp.o -o autcel  
```
  
O ejecutando el makefile que se provee.  
  
  
### Cómo utilizar el programa  
El programa provee un comando de ayuda: -h y otro para indicar la versión: -V.  
Para utilizar el mismo se debe indicar un archivo de entrada donde se encontrará 
la primera fila de la matriz a expandir, el largo que la matriz tendrá (que debe 
ser consistente con el archivo de entrada), la regla para expandir la matriz y el 
archivo de salida donde se cargará la imagen generada (este último parámetro es 
opcional; en caso de no indicarse, el archivo de salida tendra el mismo nombre 
que el de entrada + .pbm).  
Implementado la primera mejora, salida por consola, para su uso utilizar -t 
o --terminal. Ejemplo:  
```text```
./autcel 30 80  input -o output -t
```

