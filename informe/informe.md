---
output:
  pdf_document: 
    highlight: zenburn
  html_document: default
---

#### Tecnología Digital V: Diseño de Algoritmos

# TP2 - Logística centralizada de primera milla

##### Autores: Federico Giorgi, Gastón Loza Montaña y Tomás Curzio.

## Introducción

### Contexto

En los últimos años, el e-commerce ha crecido de manera exponencial en el mundo, incluyendo nuestra región. Las empresas, como en cualquier otro rubro, buscan reducir sus costos operativos, con el objetivo de obtener un mayor margen de ganancia. Para vendedores con un gran volumen de ventas, se suelen planificar visitas para recolectar los productos, pero realizar esta acción con muchos vendedores pequeños (que no realizan tantas ventas) es muy costoso en terminos logísticos, por lo que se les suele encargar a ellos que entreguen los paquetes a un punto de recolección de la empresa (usualmente llamado _primera milla_).

### El problema y la decisión a tomar

El trabajo nos pone en el contexto de consultores de la empresa **ThunderPack** que provee servicios logísticos y además ofrece la posibilidad a otras empresas logísticas de almacenar paquetes en depósitos (puntos) de ThunderPack para que luego las mismas pasen a recogerlos por dichos puntos (la primera milla ya no seria un depósito propiedad de la empresa si no un depósito alquilado).

ThunderPack actualmente tiene un sistema donde los vendedores eligen a que depósito mandan los paquetes y pueden cambiarlo sin previo aviso. La empresa ha realizado estudios y nota que muchas veces esto resulta en un uso ineficiente de su red de depósitos, por lo que consideran cambiarse a una modalidad centralizada donde cada vendedor tendrá su depósito asignado al cual hará envios regularmente. Estas asignaciones se harán buscando maximizar la demanda y minimizar las distancias que los vendedores recorren.

La empresa tiene tres preguntas que querría idealmente responder:

- "¿Es suficiente la capacidad de la red de depósitos, o es necesario expandir la misma para poder
dar respuesta a todos los vendedores?"
- "¿Es posible encontrar una asignación donde los vendedores recorran una distancia razonable
para entregar sus paquetes?"
- "¿Es factible desarrollar una herramienta que nos permita experimentar con distintos escenarios
y obtener soluciones de buena calidad en unos pocos minutos?"

Al final de este informe, con modelos para el problema y análisis sobre los mismos, buscaremos responder dichas preguntas.

### El modelo - Generalized Assignation Problem: 

El problema será modelado mediante el Problema de Asignación Generalizada (GAP), el cual formularemos para el contexto de **ThunderPack** de la siguiente manera. Sea $N = \{1, \ldots, n\}$ el conjunto de vendedores y $M = \{1, \ldots, M\}$ el conjunto de depósitos, cada depósito $i\in M$ tiene una capacidad máxima de $c_i$. Dado un vendedor $j \in N$ y un depósito $i \in M$, $d_{ij}$ determina la demanda y $c_{ij}$ la distancia a recorrer del vendedor $j$ en caso de ser asignado al depósito $i$. Una vez definidos los elementos, podemos representar a la solución como los conjuntos $\Gamma_1, \ldots, \Gamma_m \subseteq N$, con $\Gamma_i$ el conjunto de vendedores asignados al depósito $i \in M$. Así, el problema consiste en:

1. Asignar cada vendedor $j \in N$ a exáctamente un depósito $i \in M$, es decir que $, \Gamma_i \cap \Gamma_k = \emptyset \text{ si } i \neq k, i, k \in M$

2. No se debe superar la capacidad de cada depósito, es decir que para cada $i\in M$:
$$\sum_{j \in \Gamma_i} d_{ij} \leq c_i$$ 

3. Minimizar la distancia total de la asignación:
$$\sum_{i=1}^{n} \sum_{j \in \Gamma_i} c_{ij}$$

Además, es importante notar que dependiendo las capacidades y demandas dadas, podría dificultarse encontrar una solución factible. Definimos: 
$$c_{\text{max}} = \max_{i \in M, j \in N} c_{ij}$$
como la distancia máxima posible a recorrer por cada vendedor. Podríamos tener soluciones parciales en las cuales haya vendedores que no sean asignados a ningún depósito, en aquellos casos se tomará una penalización de $3 \times \text{dmax}$ para cada uno. 

### Distancia mínima

Se pueden plantear diferentes heurísticas para resolver el problema de GAP, la primera que planteamos consiste en asignar a cada vendedor con el almacen que menos distancia supone, sin excedernos de su respectiva capacidad. Podemos dividir la heurística en los siguientes pasos: 

1. Tomar un vendedor $j \in N$.
2. Asignarlo al depósito $i\in M$ más cercano factible, es decir, cuya capacidad $c_i$ sea mayor o igual a la demanda $d_{ij}$. 
4. Actualizar la capacidad $c_j$ del depósito disminuyendole la demanda $d_{ij}$ del vendedor asignado. 
3. Repetir para todos los vendedores. 
4. Para todos los vendedores no asignados (en el caso de que hayan), sumo la penalidad de no poder asignarlos.

Esta estrategia es totalmente válida. Sin embargo, es posible que existan casos donde tener que recurrir a otro depósito debido a que el más cercano no es factible sea muy costoso y por lo tanto aumente considerablemente el valor de nuestra función objetivo. Por este motivo presentamos un enfoque similar pero ajustado en la próxima heurística. 

### Martello Toth

La idea de esta heurística fue tomada del paper "A class of greedy algorithms" de los autores Martello and Toth. En este caso, para cada vendedor $j \in N$, nos guardamos los dos depósitos $l, k \in M$ más cercanos, y además, almacenamos la diferencia entre estas distancias, es decir, calculamos $dif = d_{kj} - d_{lj}$ siendo $l$ el depósito más cercano al vendedor $j$ y $k$ el segundo más cercano. Luego, ordenamos los vendedores en base a las diferencias calculadas y los asignamos en este orden, es decir, aquellos vendedores con mayor diferencia serán asignados a su mejor depósito primero (si es que este es aún factible). La lógica detrás de esta heurística es que al calcular los dos mejores depósitos (en base a menor distancia) para cada vendedor y luego obteniendo la diferencia, podemos tener en cuenta aquellos vendedores cuya distancia entre ambos sea mayor asignándolos primero. Esto puede suponer importantes mejoras, debido a que nos aseguramos que aquellos vendedores que por capacidad se vean forzados a ir a su segundo depósito más cercano, no causarán un aumento significativo en el valor objetivo.

## Operadores de búsqueda local

### Swap

El operador swap toma dos vendedores de distintos depósitos y evalúa si intercambiándolos (siempre y cuando sea factible) conseguimos una mejora en el valor objetivo. Formalmente, siendo $s$ el conjunto solución tomamos $j_1, j_2 \in s$ asignados a los depósitos $i_1$ e $i_2$ respectivamente, con $i_1 \neq i_2$. Posteriormente, removeremos $j_1$ de $i_1$ para insertarlo en $i_2$, y a $j_2$ de $i_2$ para insertarlo en $i_1$ en caso de que se cumplan las siguientes condiciones: 
$$c_{i_1j_2} + c_{i_2j_1}  < c_{i_1j_1} + c_{i_2j_2}$$
$$d_{i_1j_2} \leq \bar{c}_{i_1} + d_{i_1j_1}$$
$$d_{i_2j_1} \leq \bar{c}_{i_2}+d_{i_2j_2}$$
siendo $\bar{c}_{k}$ la capacidad restante del depósito $k$. 

### Relocate 

El operador relocate toma un vendedor asignado a un depósito y evalúa los demás depósitos para ver si hay algún otro depósito factible cuya distancia sea menor. Formalmente, tomamos un vendedor $j \in s$ asignado al depósito i, consideramos todos los posibles depósitos $k \neq i$ y removemos $k$ del depósito $i$ para insertarlo en $k$ en caso de que se cumplan las siguiente condiciones:
$$c_{kj} < c_{ij}$$
$$d{kj} \leq \bar{c}_k$$ 
con $\bar{c}_k$ la capacidad restante del depósito $k$. Luego, repetimos estos pasos para todos los vendedores de la solución. 
Planteamos como hipótesis que el operador relocate por si solo probablemente nunca genere ninguna mejora en soluciones generadas por la heurística de distancia mínima, debido a que su función a grandes rasgos es revisar si hay algún depósito factible más cercano al asignado, pero esto no ocurrirá debido a que el funcionamiento de la heurística constructiva es exactamente ese, por lo que si existiese dicho depósito, ya se habría asignado previamente.
El operador relocate es especialmente útil para poder asignar los vendedores que no fue posible asignar a ningún depósito previamente, teniendo la posibilidad de evitar la alta penalización que estos suponían. 

## Metaheurística: VND

La metaheurística que utilizaremos será VND (Variable Neighborhood Descent), cuya idea principal es tomar una solución inicial y buscar una mejora en la solución en diferentes vecindarios. Definimos vecindario como todas las soluciones que podemos alcanzar aplicando una vez el operador de busqueda local. La busqueda se realiza en el vecindario actual hasta que se encuentra una solución que mejore la actual. Luego, se pasa al siguiente vecindario y se repite el proceso hasta que no podamos encontrar mejoras. 

### Implementación de VND

En nuestra solución, utilizaremos como operadores de busqueda local a swap y relocate. La implementación de VND realizada permite elegir el orden de aplicación de los operadores y si se utilizarán ambos o solo uno. (aca me está costando explicarlo la verdad).

## Experimentación
 
### Datos

