-- John Stockton
-- CS-231, Section 1
-- Dr. Vineyard
-- Winter 2022

import System.Environment ( getArgs )
import Data.Char ( isAlpha, isSpace, toLower )
import Data.List ( sort )

-- WordNode is a new data type which contains a string, the word,
--     and the position of the word in an input file as a tuple. It implements
--     a custom Show for easier printing and Eq, Ord to use the Data.List.sort
--     function. Ord is based on the words only, not the position tuple
data WordNode = WordNode { word :: String,
                           position :: (Int,Int) }
instance Show WordNode where
    show (WordNode word position) = show word ++" " ++show position
instance Eq WordNode where
    (WordNode word1 _)==(WordNode word2 _) = word1==word2
instance Ord WordNode where
    compare (WordNode word1 _) (WordNode word2 _) = compare word1 word2
    -- Uncomment this and comment line above to base Ord on words
    --     AND position tuple
    -- compare (WordNode word1 tup1) (WordNode word2 tup2) 
    --     | word1==word2        = compare tup1 tup2
    --     | otherwise           = compare word1 word2

-- This function will take an input string and scrub all non-letter and
--     non-space characters from the string. All letters are sent to lowercase
-- Inputs: String, the string to scrub 
-- Outputs: String, the processed and scrubbed string
scrubString :: String -> String
scrubString [] = []
scrubString (char:chars) 
    -- Add char to output only if it is a letter or a whitespace
    | isAlpha char || isSpace char = toLower char : scrubString chars
    | otherwise                    = ' ' : scrubString chars

-- Get words takes a single string and has the value of a list of 
--     WordNodes, each containing a single word and the position of
--     said word in the input string, sorted by lexigraphical position
--     of the word in wordNode
-- Inputs: String, the string to split into individual wordds
-- Outputs: [WordNode], a list of WordNodes, each containing a word and
--                      position information
getWords :: String -> [WordNode]
getWords str = sort $ getWordsRec1 $ lines str

-- This is the primary helper function for getWords, it takes in a list of lines
--     and has the value of a list of WordNodes, containing the words
--     in that line. This function primarily exists to keep track of which
--     line we are on from getWords
-- Inputs: [String], the list of text lines to split
-- Outputs: [WordNode], a list of WordNodes, each containing a word and
--                      position information
getWordsRec1 :: [String] -> [WordNode]
getWordsRec1 [] = []
getWordsRec1 lines 
    | length lines==1 = getWordsRec2 currLineWords (1,currLineLen)
    | otherwise       = getWordsRec2 currLineWords (currLine,currLineLen) ++ getWordsRec1 (init lines)
        where currLine      = length lines
              currLineWords = words $ last lines
              currLineLen   = length $ words $ last lines

-- This is secondary helper function for getWords (or a primary helper 
--     function to getWordsRec2), it takes in a list of words and has the
--     value of a list of WordNodes, containing the words in that line. 
--     This function primarily exists to keep track of which word we are on from 
--     the line given by getWordsRec1
-- Inputs: [String], the list of text words to split
--         (Int,Int), the line number we are currently on (in the original input)
--                    and the word number we are currently on (in the line)
-- Outputs: [WordNode], a list of WordNodes, each containing a word and
--                      position information
getWordsRec2 :: [String] -> (Int,Int) -> [WordNode]
getWordsRec2 [] _ = []
getWordsRec2 [word] (linePos,1) = [WordNode word (linePos,1)]
getWordsRec2 words (lineNum,wordNum) = 
    WordNode (last words) (lineNum,wordNum) : getWordsRec2 (init words) (lineNum,wordNum-1)

-- This function takes a SORTED WordNode list (the words to spellcheck)
--     and a list of words (the dictionary), comparing them and updating 
--     the current position of one of the lists depending on the result 
--     of the current recursive call
-- Inputs: [WordNode], the list of words to be spellchecked
--         [String], the list of words to be used as a dictionary
-- Outputs: [String], the results of each word's spellcheck as an individual
--          result string
spellCheck :: [WordNode] -> [String] -> [String]
spellCheck [] _ = []
spellCheck _ [] = []
spellCheck (wrd:wrds) (dict:dicts)
    | word wrd < dict = ("\t\t" ++ show wrd ++ " -> INCORRECT") : spellCheck wrds (dict:dicts)
    | word wrd > dict = spellCheck (wrd:wrds) dicts
    | otherwise = (show wrd ++ " -> CORRECT") : spellCheck wrds (dict:dicts)

-- Main takes 3 arguments: the input, dictionary, and output file names
-- It then reads the input and dictionary files, parsing the input for
--     words and their respective locations and the dictionary just for the words
-- Then, it runs a spellcheck on the sorted word/position list with the dictionary,
--       writing the results of each word to the output file
main :: IO ()
main = do
    -- Grab args
    [inFile, dictFile, outFile] <- getArgs

    -- Read input file
    rawInput <- readFile inFile
    rawDict  <- readFile dictFile

    -- Parse input file for words and positions
    let inputWords = scrubString rawInput
    let inputWords2 = getWords inputWords

    -- Parse dictionary for words
    let dictWords = words rawDict

    -- Run spellcheck on input
    let results = spellCheck inputWords2 dictWords
    writeFile outFile $ unlines results    