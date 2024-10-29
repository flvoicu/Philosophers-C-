# Philosophers - Problema de los Filósofos

El proyecto **philosophers** es una implementación del clásico problema de los filósofos comensales, que aborda la sincronización y la concurrencia en sistemas informáticos. Este problema es un buen ejemplo para aprender sobre el uso de hilos y la gestión de recursos compartidos.

## Objetivo

El objetivo es simular a un grupo de filósofos sentados a una mesa, donde cada uno alterna entre pensar y comer. Para comer, un filósofo necesita dos tenedores (uno a su izquierda y otro a su derecha). El reto es evitar condiciones de carrera y garantizar que todos los filósofos puedan comer sin entrar en un estado de inanición.

## Requisitos

- Conocimientos de programación en **C**.
- Familiaridad con la programación de hilos (pthreads).

## Compilación

Para compilar el proyecto, ejecuta el siguiente comando en el directorio raíz:

```bash
make
```

## Ejecución

```bash
./philo <número de filósofos> <tiempo de muerte> <tiempo de comer> <tiempo de pensar> [número de comidas]
```