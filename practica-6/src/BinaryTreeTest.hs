import BinaryTree

tree0 = tree 1 (tree 2 (leaf 3) (leaf 4)) (tree 5 empty (leaf 6))
tree1 = tree "R" (tree "HI" (leaf "NII") (leaf "NID")) (tree "HD" (leaf "NDI") (leaf "NDD"))

abb = add (add (add (add empty 2) 4) 3) 1

names = ["Adolfo","Diego","Juan","Pedro","Tomas"]

main = do
  tree_test tree0
  tree_test tree1
  tree_test abb

  list_test [1]
  list_test [1, 2]
  list_test [1..16]
  list_test [3, 2, 2, 5, 1, 4, 4]
  list_test [2, 5, 1, 3, 2, 4, 4]
  list_test names
  list_test [3,3,3,3,3]
  list_test [1,3,3,3,5]

  putStrLn ""
  putStrLn "Search..."
  print $ between (build         [2, 5, 1, 3, 2, 4, 4]) 2 4
  print $ between (buildBalanced [2, 5, 1, 3, 2, 4, 4]) 2 4
  print $ between (build         names) "B" "Q"
  print $ between (buildBalanced names) "B" "Q"

  putStrLn "...done"

tree_test t = do
  putStrLn "--------------------------------------------"
  putStrLn "tree:"
  print $ t
  putStrLn $ "size: " ++ show (size t)
  putStrLn $ "pre : " ++ show (preorder t)
  putStrLn $ "post: " ++ show (postorder t)
  putStrLn $ "in  : " ++ show (inorder t)
  putStrLn "--------------------------------------------"

list_test l = do
  putStrLn "============================================"
  putStrLn $ "Test with list: " ++ (show l)
  putStrLn "-- direct"
  tree_test t
  putStrLn "-- balanced"
  tree_test b
  putStrLn "============================================"
  where
    t = build l
    b = buildBalanced l
