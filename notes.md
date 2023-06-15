### Estrategia para resolver el TP:

1. Resolver el punto de los greedy.
2. Crear dos operadores de busqueda local y despues mezclarlos -> ej: relocate, swap, relocate dsp swap, swap dsp relocate (ver cual da mejores resultados).
3. Metaheuristica GRASP ->  Agarramos el greedy, lo transformamos en random greedy y dsp partimos de soluciones de random greedy y les hacemos nuestra busqueda local. De todas las iteraciones nos quedamos con la mejor.
4. Experimentar y analizar los resultados como en el TP1 con las instancias de benchmarking.
5. Ver que sucede con la instancia real de ThunderPack.
6. Con esa data armar el informe.



### Posibles soluciones:
##### Heuristicas constructivas:
- Asigno el vendedor actual al almacen que mas demanda me da sin pasarse de la capacidad.
- Asigno el vendedor actual al almacen que menos costo suma.


##### Busqueda local: