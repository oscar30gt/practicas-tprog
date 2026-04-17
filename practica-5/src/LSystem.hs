module LSystem (tplot, lsystem) where

import Turtle

-- Función para generar la lista de posiciones a partir de las órdenes de la tortuga
tplot :: Turtle -> String -> [Position]
tplot tortuga ordenes = reverse (recorrer tortuga ordenes [obtenerPos tortuga])
  where
    -- Función auxiliar para obtener la posición actual de la tortuga
    obtenerPos :: Turtle -> Position
    obtenerPos (_, _, pos, _) = pos

    -- Función recursiva para recorrer las órdenes de la tortuga y acumular las posiciones
    recorrer :: Turtle -> String -> [Position] -> [Position]
    recorrer tortugaActual [] puntos = puntos -- Si no hay más órdenes, devuelve las posiciones acumuladas

    recorrer tortugaActual (c:cs) puntos =
      case c of
        '>' ->    -- Si la orden es '>'
          let nuevaTortuga = moveTurtle tortugaActual Forward -- Mover hacia adelante
          in recorrer nuevaTortuga cs (obtenerPos nuevaTortuga : puntos)  -- Agregar la nueva posición a la lista de puntos
        '+' ->    -- Si la orden es '+'
          recorrer (moveTurtle tortugaActual TurnRight) cs puntos -- Girar a la derecha y continuar con las órdenes restantes
        '-' ->    -- Si la orden es '-'
          recorrer (moveTurtle tortugaActual TurnLeft) cs puntos -- Girar a la izquierda y continuar con las órdenes restantes
        letra ->  -- En cualquier otro caso
          if letra >= 'A' && letra <= 'Z' -- Si la letra es una letra mayúscula
          then
            let nuevaTortuga = moveTurtle tortugaActual Forward -- Mover hacia adelante
            in recorrer nuevaTortuga cs (obtenerPos nuevaTortuga : puntos)  -- Agregar la nueva posición a la lista de puntos
          else  -- Si la letra no es una letra mayúscula
            recorrer tortugaActual cs puntos  -- Continuar con las órdenes restantes sin mover la tortuga

-- Función para generar la cadena resultante del sistema L a partir de las reglas, el axioma y el número de iteraciones
lsystem :: (Char -> String) -> String -> Int -> String
lsystem reglas axioma veces
  | veces <= 0 = axioma -- Si el número de iteraciones es 0 o negativo, devuelve el axioma sin cambios
  | otherwise = lsystem reglas (reescribir reglas axioma) (veces - 1) -- Si no, reescribe el axioma y llama recursivamente

-- Función auxiliar para reescribir la cadena según las reglas dadas
reescribir :: (Char -> String) -> String -> String
reescribir reglas [] = [] -- Si la cadena está vacía, devuelve una cadena vacía
reescribir reglas (x:xs) = reglas x ++ reescribir reglas xs -- Reescribe el primer carácter según las reglas y luego reescribe el resto de la cadena