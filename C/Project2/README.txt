Author: John Stockton
Class: CS-231, Section 1
Instructor: Dr. Vineyard
Term: Winter 2022

The two C programs validParentheses.c and evalPostfix.c depend on the stack ADT
    as headed by stackADT.h and implemented in stack.C

To run validParentheses.c:
    1. In stackADT.h: ensure line #13 is UNCOMMENTED and line #14 is COMMENTED OUT
    2. run `gcc stackADT.h stack.c validParentheses.c`
    3. run `./a.out <exampleInputFile.txt> <exampleOutputfile.txt>`
    4. profit

To run evalPostfix.c:
    1. In stackADT.h: ensure line #13 is COMMENTED OUT and line #14 is UNCOMMENTED
    2. run `gcc stackADT.h stack.c evalPostfix.c`
    3. run `./a.out <exampleInputFile.txt> <exampleOutputfile.txt>`
    4. profit