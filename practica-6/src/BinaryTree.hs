module BinaryTree(BinaryTree, empty, leaf, tree, size, add, build, buildBalanced, preorder, inorder, postorder, balance, between) where
import Data.List (sort)

-- Definicion del tipo de dato BinaryTree
data BinaryTree a = Empty | Node a (BinaryTree a) (BinaryTree a)

-- Constructores
empty :: BinaryTree a
empty = Empty

leaf :: a -> BinaryTree a
leaf x = Node x Empty Empty

tree :: a -> BinaryTree a -> BinaryTree a -> BinaryTree a
tree x lc rc = Node x lc rc

-- Número de nodos en el árbol
size :: BinaryTree a -> Int
size Empty = 0
size (Node _ l r) = 1 + size l + size r

-- Instanciamos la clase Show para BinaryTree
instance Show a => Show (BinaryTree a) where
    show t = unlines (showTree "" t)

-- Función auxiliar para mostrar el árbol de forma legible
showTree :: Show a => String -> BinaryTree a -> [String]
showTree _ Empty = ["()"]

-- Caso hoja: no mostrar hijos vacíos
showTree prefix (Node x Empty Empty) =
    [prefix ++ show x]

-- Caso general
showTree prefix (Node x l r) =
    (prefix ++ show x) :
    showChild prefix l ++
    showChild prefix r

-- Función auxiliar para mostrar los hijos de un nodo
showChild :: Show a => String -> BinaryTree a -> [String]
showChild prefix t =
    case t of
        Empty ->
            [prefix ++ "\\- ()"]

        Node _ _ _ ->
            let
                linesSub = showTree (prefix ++ "   ") t
            in
                case linesSub of
                    [] -> []

                    (h:ts) ->
                        (prefix ++ "\\- " ++ drop (length prefix + 3) h) : ts

-- Función para agregar un elemento al árbol manteniendo el orden
add :: Ord a => BinaryTree a -> a -> BinaryTree a
add Empty x = Node x Empty Empty
add (Node v l r) x
    | x < v     = Node v (add l x) r
    | otherwise = Node v l (add r x)

-- Función para construir un árbol a partir de una lista de elementos
build :: Ord a => [a] -> BinaryTree a
build = foldl add empty

-- Función para construir un árbol equilibrado a partir de una lista de elementos
buildBalanced :: Ord a => [a] -> BinaryTree a
buildBalanced [] = Empty
buildBalanced xs = buildBalanced' (sort xs)

-- Función auxiliar para construir un árbol equilibrado a partir de una lista ordenada
buildBalanced' :: Ord a => [a] -> BinaryTree a
buildBalanced' [] = Empty
buildBalanced' xs =
    let
        mid = length xs `div` 2
        (leftPart, rest) = splitAt mid xs

        -- rest siempre tiene al menos un elemento
        (x:rightCandidates) = rest

        -- Ajuste para duplicados (>= a la derecha)
        (leftFinal, duplicates) = span (< x) leftPart
        rightFinal = duplicates ++ rightCandidates

    in
        Node x
            (buildBalanced' leftFinal)
            (buildBalanced' rightFinal)

-- Funcion para obtener el recorrido en preorden del árbol
preorder :: BinaryTree a -> [a]
preorder Empty = []
preorder (Node x l r) =
    [x] ++ preorder l ++ preorder r

-- Funcion para obtener el recorrido en inorden del árbol
inorder :: BinaryTree a -> [a]
inorder Empty = []
inorder (Node x l r) =
    inorder l ++ [x] ++ inorder r

-- Funcion para obtener el recorrido en postorden del árbol
postorder :: BinaryTree a -> [a]
postorder Empty = []
postorder (Node x l r) =
    postorder l ++ postorder r ++ [x]

-- Función para equilibrar un árbol binario
balance :: Ord a => BinaryTree a -> BinaryTree a
balance t = buildBalanced (inorder t)

-- Función para obtener los elementos del árbol que están entre dos valores dados
between :: Ord a => BinaryTree a -> a -> a -> [a]
between Empty _ _ = []

between (Node x l r) xmin xmax
    | x < xmin =
        between r xmin xmax

    | x > xmax =
        between l xmin xmax

    | otherwise =
        [x] ++ between l xmin xmax ++ between r xmin xmax