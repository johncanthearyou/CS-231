-- John Stockton
-- CS-231, Section 1
-- Dr. Vineyard
-- Winter 2022

wrapInsert :: a -> [a] -> [a]
wrapInsert item [] = [item]
wrapInsert item [x] = [item,x,item]
wrapInsert item (x:xs) = [item,x] ++ wrapInsert item xs