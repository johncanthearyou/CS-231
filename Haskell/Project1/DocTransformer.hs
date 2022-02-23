-- John Stockton
-- CS-231, Section 1
-- Dr. Vineyard
-- Winter 2022

module DocTransformer where
import Data.Char (toUpper, toLower, isAlpha, isSpace)

-- This function will take a string and split it out into individual words,
--     throw away any words not of a specified length, reverse the order of 
--     the words, send all vowels to lowercase, then recombine the words into
--     a single string, each word on a new line
-- Inputs: String, the string to be processed and transformed
--         Int, the length of words we want to keep
-- Outputs: String, the processed string
transformDoc :: String -> Int -> String
transformDoc [] _ = []
transformDoc fileData len = unlines processedStr
    where
        -- 1. wordGrab splits the input string
        -- 2. lengthCheck gets rid of all words which aren't a certain length
        -- 3. reverse gives all the words of specific length in reverse order
        -- 4. caseWorker changes the case of the words to meet the specification
        processedStr = caseWorker (reverse (lengthCheck (wordGrab fileData) len))

-- This function will take an input string and scrub all non-letter and
--     non-space characters from the string. It is a helper for wordGrab.
-- Inputs: String, the string to scrub
-- Outputs: String, the processed and scrubbed string
scrubString :: String -> String
scrubString [] = []
scrubString (char:chars) 
    -- Add char to output only if it is a letter or a whitespace
    | isAlpha char || isSpace char = char : scrubString chars
    | otherwise                    = scrubString chars

-- This function takes a single string, and splits it out into a 
--     list of individual words, not including any non-letter characters
-- Inputs: String, the string we want to break out into words
-- Outputs: [String], the list of words we got from the input string
wordGrab :: String -> [String]
wordGrab str = words (scrubString str)

-- This function will take a list of words and an int specifying the 
--     length of words we want to keep. All other words will be discarded
-- Inputs: [String], the list of words we want to parse for lengths
--         Int, the length of words we want to keep
-- Outputs: [String], the list of words of a given length
lengthCheck :: [String] -> Int -> [String]
lengthCheck [] _ = []
lengthCheck (xs:xss) len
    | length xs==len   = xs : lengthCheck xss len
    | otherwise        = lengthCheck xss len

-- This function takes a character and determines if it is a value
-- Inputs: Char, the character to check
-- Outputs: Bool, True if the input IS a vowel
--                False if the input IS NOT a vowel
isVowel :: Char -> Bool
isVowel char
    | charLower=='a' = True
    | charLower=='e' = True
    | charLower=='i' = True
    | charLower=='o' = True
    | charLower=='u' = True
    | otherwise      = False
        where charLower = toLower char

-- This function takes a character and determines if it is a consonant. We know it is a 
--     consonant if and only if it IS a letter and NOT a vowel
-- Inputs: Char, the character to check
-- Outputs: Bool, True if the input IS a consonant
--                False if the input IS NOT a consonant
isConsonant :: Char -> Bool
isConsonant char = isAlpha char && not (isVowel char)

-- This function takes a word, then changes all vowels to lowercase
--     and all consonants to uppercase
-- Inputs: String, the word to process
-- Outputs: String, the case-processed word
transformWord :: String -> String
transformWord [] = []
transformWord (char:chars)
    | isVowel char     = toLower char : transformWord chars
    | isConsonant char = toUpper char : transformWord chars
    | otherwise        = char : transformWord chars

-- This function takes a list of words, then changes all vowels to lowercase
--     and all consonants to uppercase in each word of the list
-- Inputs: [String], the words to process
-- Outputs: [String], the case-processed words
caseWorker :: [String] -> [String]
caseWorker [] = []
caseWorker str = map transformWord str