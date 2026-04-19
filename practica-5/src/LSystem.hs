module LSystem (
  tplot, lsystem, triangleCommands, squareCommands, circleCommands, ruleKoch, ruleMinkowski,
  ruleSierpinskiTriangle, ruleKochSquare, ruleArrowhead, ruleHilbert, ruleGosper
) where

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
    recorrer tortugaActual (c:cs) puntos
      | c == '>'  =  -- Si la orden es '>'
          let nuevaTortuga = moveTurtle tortugaActual Forward -- Mueve la tortuga hacia adelante
          in recorrer nuevaTortuga cs (obtenerPos nuevaTortuga : puntos)  -- Agrega la nueva posición a la lista de puntos y continúa recorriendo
      | c == '+'  =  -- Si la orden es '+'
          recorrer (moveTurtle tortugaActual TurnRight) cs puntos -- Gira la tortuga a la derecha y continúa recorriendo
      | c == '-'  =  -- Si la orden es '-'
          recorrer (moveTurtle tortugaActual TurnLeft) cs puntos  -- Gira la tortuga a la izquierda y continúa recorriendo
      | c >= 'A' && c <= 'Z' =  -- Si la orden es una letra mayúscula (representa un comando de movimiento)
          let nuevaTortuga = moveTurtle tortugaActual Forward -- Mueve la tortuga hacia adelante
          in recorrer nuevaTortuga cs (obtenerPos nuevaTortuga : puntos)  -- Agrega la nueva posición a la lista de puntos y continúa recorriendo
      | otherwise = -- Si la orden no es reconocida
          recorrer tortugaActual cs puntos  -- Continúa recorriendo sin cambiar la tortuga ni agregar puntos

-- Función para generar la cadena resultante del sistema L a partir de las reglas, el axioma y el número de iteraciones
lsystem :: (Char -> String) -> String -> Int -> String
lsystem reglas axioma 0 = axioma -- Si el número de iteraciones es 0, devuelve el axioma sin cambios
lsystem reglas axioma n = lsystem reglas (reescribir reglas axioma) (n - 1) -- Si no, reescribe el axioma y llama recursivamente

-- Función auxiliar para reescribir la cadena según las reglas dadas
reescribir :: (Char -> String) -> String -> String
reescribir reglas [] = [] -- Si la cadena está vacía, devuelve una cadena vacía
reescribir reglas (x:xs) = reglas x ++ reescribir reglas xs -- Reescribe el primer carácter según las reglas y luego reescribe el resto de la cadena

-- Funciones para generar comandos de figuras básicas
triangleCommands :: String
triangleCommands = ">+>+>+"

squareCommands :: String
squareCommands = ">+>+>+>+"

circleCommands :: Int -> String
circleCommands sides = concat (replicate sides ">+")

-- Reglas para diferentes sistemas L
ruleKoch :: Char -> String
ruleKoch 'F' = "F-F++F-F"
ruleKoch c = [c]

ruleMinkowski :: Char -> String
ruleMinkowski 'F' = "F-F+F+FF-F-F+F"
ruleMinkowski c = [c]

ruleSierpinskiTriangle :: Char -> String
ruleSierpinskiTriangle 'F' = "F-G+F+G-F"
ruleSierpinskiTriangle 'G' = "GG"
ruleSierpinskiTriangle c = [c]

ruleKochSquare :: Char -> String
ruleKochSquare 'F' = "F-F+F+F-F"
ruleKochSquare c = [c]

ruleArrowhead :: Char -> String
ruleArrowhead 'F' = "G+F+G"
ruleArrowhead 'G' = "F-G-F"
ruleArrowhead c = [c]

ruleHilbert :: Char -> String
ruleHilbert 'f' = "-g>+f>f+>g-"
ruleHilbert 'g' = "+f>-g>g->f+"
ruleHilbert c = [c]

ruleGosper :: Char -> String
ruleGosper 'F' = "F-G--G+F++FF+G-"
ruleGosper 'G' = "+F-GG--G-F++F+G"
ruleGosper c = [c]