import LSystem
import SVG

main :: IO ()
main = do
  -- Figuras básicas
  savesvg "triangulo" (tplot (1,120,(0,0),0) triangleCommands)
  savesvg "cuadrado" (tplot (1,90,(0,0),0) squareCommands)
  savesvg "circulo" (tplot (1,10,(0,0),0) (circleCommands 36))
  -- L-Systems
  savesvg "koch" (tplot (1,60,(0,0),0) (lsystem ruleKoch "F" 3))
  savesvg "koch_snowflake" (tplot (1,60,(0,0),0) (lsystem ruleKoch "F++F++F" 3))
  savesvg "koch_cuadrada" (tplot (1,90,(0,0),0) (lsystem ruleKochSquare "F" 3))
  savesvg "minkowski" (tplot (1,90,(0,0),0) (lsystem ruleMinkowski "F+F+F+F" 2))
  savesvg "sierpinski_triangle" (tplot (1,120,(0,0),0) (lsystem ruleSierpinskiTriangle "F-G-G" 3))
  savesvg "arrowhead" (tplot (1,60,(0,0),0) (lsystem ruleArrowhead "F" 4))
  savesvg "hilbert" (tplot (1,90,(0,0),0) (lsystem ruleHilbert "f" 4))
  savesvg "gosper" (tplot (1,60,(0,0),0) (lsystem ruleGosper "F" 3))