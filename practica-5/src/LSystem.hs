module LSystem
  ( tplot,
    lsystem,
    triangleCommands,
    squareCommands,
    circleCommands,
    ruleKoch,
    ruleMinkowski,
    ruleSierpinskiTriangle,
    ruleKochSquare,
    ruleArrowhead,
    ruleHilbert,
    ruleGosper,
  )
where

import Data.Char (isUpper)
import Turtle

-- Interpreta una cadena de órdenes con la tortuga y devuelve la lista de posiciones recorridas.
tplot :: Turtle -> String -> [Position]
tplot turtle = map getPos . scanl step turtle
  where
    getPos (_, _, pos, _) = pos
    step t '>' = moveTurtle t Forward
    step t '+' = moveTurtle t TurnRight
    step t '-' = moveTurtle t TurnLeft
    step t c | isUpper c = moveTurtle t Forward
    step t _ = t

-- Aplica un sistema-L al axioma dado durante n iteraciones.
lsystem :: (Char -> String) -> String -> Int -> String
lsystem rules axiom n = iterate (concatMap rules) axiom !! n

-- Comandos para figuras geométricas básicas.
triangleCommands :: String
triangleCommands = ">+>+>+"

squareCommands :: String
squareCommands = ">+>+>+>+"

-- Genera los comandos para una aproximación de círculo con el número de lados dado.
circleCommands :: Int -> String
circleCommands sides = concat (replicate sides ">+")

--------------------------------------------------------------------------
-- Reglas de producción para los distintos lsystems.
--------------------------------------------------------------------------

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