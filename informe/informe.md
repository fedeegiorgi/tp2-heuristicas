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