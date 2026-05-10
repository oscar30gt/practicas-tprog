module BinaryTree(BinaryTree, empty, leaf, tree, size, add, build, buildBalanced, preorder, inorder, postorder, balance, between) where
import Data.List (sort)

-- Definicion del tipo de dato BinaryTree
data BinaryTree a = Empty | Node a (BinaryTree a) (BinaryTree a)

-- Constructores
empty :: BinaryTree a
empty = Empty -- Un árbol vacío

leaf :: a -> BinaryTree a
leaf x = Node x Empty Empty -- Un árbol con un solo nodo

tree :: a -> BinaryTree a -> BinaryTree a -> BinaryTree a
tree x lc rc = Node x lc rc -- Un árbol con un nodo raíz y dos subárboles

-- Número de nodos en el árbol
size :: BinaryTree a -> Int
size Empty = 0 -- El tamaño de un árbol vacío es 0
size (Node _ l r) = 1 + size l + size r -- El tamaño de un árbol es 1 más el tamaño de sus subárboles

-- Instanciamos la clase Show para BinaryTree
instance Show a => Show (BinaryTree a) where
    show t = concat (map (++ "\n") (showTree "" t)) -- Utilizamos la función auxiliar showTree para mostrar el árbol de forma legible

-- Función auxiliar para mostrar el árbol de forma legible
showTree :: Show a => String -> BinaryTree a -> [String]
showTree _ Empty = ["()"] -- Un árbol vacío se muestra como ()
showTree prefix (Node x Empty Empty) = [prefix ++ show x] -- Un nodo hoja se muestra con su valor
showTree prefix (Node x l r) =
    (prefix ++ show x) : showChild prefix l ++ showChild prefix r -- Un nodo con hijos se muestra con su valor y luego sus hijos

-- Función auxiliar para mostrar los hijos de un nodo
showChild :: Show a => String -> BinaryTree a -> [String]
showChild prefix Empty = [prefix ++ "\\- ()"] -- Un hijo vacío se muestra como \- ()
showChild prefix t =
    let (h:ts) = showTree (prefix ++ "   ") t
    in  (prefix ++ "\\- " ++ drop (length prefix + 3) h) : ts -- El primer hijo se muestra con el prefijo actual y los siguientes hijos se muestran
                                                              -- con un prefijo adicional para indicar que son hijos del nodo actual

-- Función para agregar un elemento al árbol manteniendo el orden
add :: Ord a => BinaryTree a -> a -> BinaryTree a
add Empty x = leaf x -- Agregar a un árbol vacío crea un nodo hoja
add (Node v l r) x
    | x < v = Node v (add l x) r -- Si el valor a agregar es menor que el valor del nodo actual, se agrega al subárbol izquierdo
    | otherwise = Node v l (add r x) -- Si el valor a agregar es mayor o igual que el valor del nodo actual, se agrega al subárbol derecho

-- Función para construir un árbol a partir de una lista de elementos
build :: Ord a => [a] -> BinaryTree a
build = foldl add empty -- Se construye el árbol agregando cada elemento de la lista al árbol vacío utilizando la función add

-- Función para construir un árbol equilibrado a partir de una lista de elementos
buildBalanced :: Ord a => [a] -> BinaryTree a
buildBalanced = buildBalancedRec . sort -- Se construye un árbol equilibrado ordenando la lista y luego utilizando la función auxiliar
                                        -- buildBalancedRec para construir el árbol de forma equilibrada

-- Función auxiliar para construir un árbol equilibrado a partir de una lista ordenada
buildBalancedRec :: Ord a => [a] -> BinaryTree a
buildBalancedRec [] = Empty -- Un árbol vacío se construye a partir de una lista vacía
buildBalancedRec xs =
    let mid = length xs `div` 2 -- Se encuentra el índice del elemento medio de la lista
        (leftPart, x:rightCandidates) = splitAt mid xs -- Se divide la lista en dos partes: la parte izquierda y el elemento medio
                                                       -- (que será la raíz del árbol)
        (leftFinal, duplicates) = span (< x) leftPart -- Se separan los elementos de la parte izquierda que son menores que el elemento medio
                                                       -- (que serán el subárbol izquierdo) y los elementos que son iguales al elemento medio
                                                       -- (que serán agregados al subárbol derecho)
    in  Node x
            (buildBalancedRec leftFinal) -- Se construye el subárbol izquierdo a partir de los elementos menores que el elemento medio
            (buildBalancedRec (duplicates ++ rightCandidates)) -- Se construye el subárbol derecho a partir de los elementos iguales al
                                                               -- elemento medio y los elementos mayores que el elemento medio

-- Funciones para recorrer el árbol en diferentes órdenes
preorder :: BinaryTree a -> [a]
preorder Empty = [] -- El recorrido en preorden de un árbol vacío es una lista vacía
preorder (Node x l r) = x : preorder l ++ preorder r -- El recorrido en proorden visita primero el nodo raíz, luego el subárbol izquierdo y
                                                     -- finalmente el subárbol derecho

inorder :: BinaryTree a -> [a]
inorder Empty = [] -- El recorrido en inorden de un árbol vacío es una lista vacía
inorder (Node x l r) = inorder l ++ x : inorder r -- El recorrido en inorden visita primero el subárbol izquierdo, luego el nodo raíz y
                                                  -- finalmente el subárbol derecho

postorder :: BinaryTree a -> [a]
postorder Empty = [] -- El recorrido en postorden de un árbol vacío es una lista vacía
postorder (Node x l r) = postorder l ++ postorder r ++ [x] -- El recorrido en postorden visita primero el subárbol izquierdo, luego el
                                                           -- subárbol derecho y finalmente el nodo raíz

-- Función para equilibrar un árbol binario (reutiliza inorder + buildBalanced)
balance :: Ord a => BinaryTree a -> BinaryTree a
balance = buildBalanced . inorder -- Para equilibrar un árbol, primero se obtiene la lista de elementos en orden utilizando inorder y
                                  -- luego se construye un árbol equilibrado a partir de esa lista utilizando buildBalanced

-- Función para obtener los elementos del árbol que están entre dos valores dados
between :: Ord a => BinaryTree a -> a -> a -> [a]
between Empty _ _ = [] -- Si el árbol está vacío, no hay elementos entre los valores dados
between (Node x l r) xmin xmax
    | x < xmin = between r xmin xmax -- Si el valor del nodo actual es menor que el valor mínimo
                                      -- se buscan los elementos entre los valores dados en el subárbol derecho
    | x > xmax = between l xmin xmax -- Si el valor del nodo actual es mayor que el valor máximo
                                      -- se buscan los elementos entre los valores dados en el subárbol izquierdo
    | otherwise = [x] ++ between l xmin xmax ++ between r xmin xmax -- Si el valor del nodo actual está entre los valores dados
                                                                     -- se incluye ese valor en la lista de resultados y se buscan los 
                                                                     -- elementos entre los valores dados en ambos subárboles