module LSystem (
  tplot, lsystem, triangleCommands, squareCommands, circleCommands, ruleKoch, ruleMinkowski,
  ruleSierpinskiTriangle, ruleKochSquare, ruleArrowhead, ruleHilbert, ruleGosper
) where

import Turtle
import Data.Char (isUpper)

-- Función para generar la lista de posiciones a partir de las órdenes de la tortuga
tplot :: Turtle -> String -> [Position]
tplot tortuga ordenes = reverse (recorrer tortuga ordenes [obtenerPos tortuga])
  where
    -- Función auxiliar para obtener la posición actual de la tortuga
    obtenerPos :: Turtle -> Position
    obtenerPos (_, _, pos, _) = pos

    -- Función recursiva para recorrer las órdenes de la tortuga y acumular las posiciones
    recorrer :: Turtle -> String -> [Position] -> [Position]
    recorrer tortugaActual [] puntos = puntos
    recorrer tortugaActual (c:cs) puntos
      | c == '>'  =
          let nuevaTortuga = moveTurtle tortugaActual Forward
          in recorrer nuevaTortuga cs (obtenerPos nuevaTortuga : puntos)
      | c == '+'  =
          recorrer (moveTurtle tortugaActual TurnRight) cs puntos
      | c == '-'  =
          recorrer (moveTurtle tortugaActual TurnLeft) cs puntos
      | isUpper c =
          let nuevaTortuga = moveTurtle tortugaActual Forward
          in recorrer nuevaTortuga cs (obtenerPos nuevaTortuga : puntos)
      | otherwise =
          recorrer tortugaActual cs puntos

-- Función para generar la cadena resultante del sistema L a partir de las reglas, el axioma y el número de iteraciones
lsystem :: (Char -> String) -> String -> Int -> String
lsystem reglas axioma 0 = axioma
lsystem reglas axioma n = lsystem reglas (reescribir reglas axioma) (n - 1)

-- Función auxiliar para reescribir la cadena según las reglas dadas
reescribir :: (Char -> String) -> String -> String
reescribir reglas [] = []
reescribir reglas (x:xs) = reglas x ++ reescribir reglas xs

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