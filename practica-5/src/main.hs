import LSystem
import SVG
import Turtle

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

-- Funciones para guardar figuras y sistemas L en archivos SVG
saveFigureCommands :: String -> Turtle -> String -> IO ()
saveFigureCommands = saveFigure

saveGenerated :: String -> Turtle -> (Char -> String) -> String -> Int -> IO ()
saveGenerated = saveLSystemFigure

saveFigure :: String -> Turtle -> String -> IO ()
saveFigure name turtle commands = savesvg name (tplot turtle commands)

saveLSystemFigure :: String -> Turtle -> (Char -> String) -> String -> Int -> IO ()
saveLSystemFigure name turtle rules axiom iterations =
  savesvg name (tplot turtle (lsystem rules axiom iterations))

main :: IO ()
main = do
  -- Guardar figuras básicas
  saveFigure "triangulo" (1, 120, (0, 0), 0) triangleCommands
  saveFigure "cuadrado" (1, 90, (0, 0), 0) squareCommands
  saveFigure "circulo" (1, 10, (0, 0), 0) (circleCommands 36)

-- Guardar figuras generadas por sistemas L
  saveLSystemFigure "koch" (1, 60, (0, 0), 0) ruleKoch "F" 3
  saveLSystemFigure "koch_snowflake" (1, 60, (0, 0), 0) ruleKoch "F++F++F" 3
  saveLSystemFigure "koch_cuadrada" (1, 90, (0, 0), 0) ruleKochSquare "F" 3
  saveLSystemFigure "minkowski" (1, 90, (0, 0), 0) ruleMinkowski "F+F+F+F" 2
  saveLSystemFigure "sierpinski_triangle" (1, 120, (0, 0), 0) ruleSierpinskiTriangle "F-G-G" 3
  saveLSystemFigure "arrowhead" (1, 60, (0, 0), 0) ruleArrowhead "F" 4
  saveLSystemFigure "hilbert" (1, 90, (0, 0), 0) ruleHilbert "f" 4
  saveLSystemFigure "gosper" (1, 60, (0, 0), 0) ruleGosper "F" 3

-- Imprimir mensaje de confirmación
  putStrLn "SVG files generated."


