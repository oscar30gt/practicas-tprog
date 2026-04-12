module LSystem (tplot, lsystem) where

import Turtle

tplot :: Turtle -> String -> [Position]
tplot turtle commands = reverse (go turtle commands [initialPosition])
  where
    initialPosition = turtlePosition turtle

    turtlePosition :: Turtle -> Position
    turtlePosition (_, _, pos, _) = pos

    go :: Turtle -> String -> [Position] -> [Position]
    go current [] points = points
    go current (command:rest) points =
      case command of
        '>' -> let next = moveTurtle current Forward
               in go next rest (turtlePosition next : points)
        '+' -> go (moveTurtle current TurnRight) rest points
        '-' -> go (moveTurtle current TurnLeft) rest points
        letter
          | letter >= 'A' && letter <= 'Z' ->
              let next = moveTurtle current Forward
              in go next rest (turtlePosition next : points)
          | otherwise -> go current rest points

lsystem :: (Char -> String) -> String -> Int -> String
lsystem rules axiom iterations
  | iterations <= 0 = axiom
  | otherwise = lsystem rules (rewriteOnce rules axiom) (iterations - 1)

rewriteOnce :: (Char -> String) -> String -> String
rewriteOnce rules = concatMap rules