-- John Stockon
-- CS-231, Section 1
-- Dr. Vineyard
-- Summer 2022

-- This function is justified in using a do statement as we are taking input
--     from stdin which will yeild our result
-- Inputs: Int, the number of times we want to get a number
--         String, the string representation of the sum calculated so far
-- Outputs: IO String, an IO wrapped string representing the new sum based on 
--                     the current recursive iteration
accumulateNums :: Int -> String -> IO String
accumulateNums 0 finalSum = return finalSum --Base case: return the sum string
accumulateNums int sumStr = do
    putStrLn "Enter a number> "
    input <- getLine
    let num = (read input :: Int) -- read the user-input number to an Int
    let currSum = (read sumStr :: Int) -- read the previous sum string to an Int
    let newSum = show (num+currSum) -- Combine the old sum and the new number
    accumulateNums (int-1) newSum

-- Main will ask a user to input a number representing the number of 
--     integers (n) the user wants to add together
-- Then, main will ask for a number n times and add them together
-- Finally, it will print the result
main = do
    putStrLn "Please enter how many integers you would like to add> "
    numInts <- getLine
    putStrLn "======================================================" 
    putStrLn ("Enter " ++ numInts ++ " integers(s):")
    let numNums = read numInts :: Int
    result <- accumulateNums numNums "0"
    putStrLn "======================================================"
    putStrLn ("Sum> " ++ result)