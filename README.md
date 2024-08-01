# Lexer and Symbol Table for Simple Programming Language

## Overview

This project implements a lexer and a symbol table for a basic programming language using C++. The lexer performs lexical analysis by tokenizing input code, while the symbol table manages the variables and their attributes within the code. The code provides a foundation for understanding and implementing language processing tasks.

## Features

- **Lexer**: Analyzes lines of code and splits them into tokens, validating each token according to language rules.
- **Symbol Table**: Manages symbol information including data types, identifiers, values, and line numbers.
- **Semantic Analysis**: Performs checks on the structure of instructions to validate declarations, definitions, and statements.

## Code Breakdown

### Includes
- `<iostream>`: Provides input/output functionality (e.g., `cout`, `cin`).
- `<sstream>`: Used for string manipulation (not used in the provided code).
- `<fstream>`: Used for file operations (reading and writing).
- `<stack>`: Used for data structures (not used in the provided code).
- `<vector>`: Used for storing collections of elements.
- `<string>`: Used for string manipulation.

### Global Variables
- `s_check`, `switch_check`, etc.: Flags used for tracking the parsing state (not fully explained).
- `ASSIGNMENT`: Represents the assignment operator ("<->").
- `tilt`: Special character ("~") used in the grammar.
- `res`: String variable (purpose not clear).
- `j`: Integer variable for goto statement handling (not implemented).

### Functions
- `RemoveComments(string s)`: Removes comments from a line of code.
- `removeSpace(string line)`: Removes leading and trailing whitespace from a line.
- `writeFile(string f_Name, string data)`: Writes data to a file.
- `readFile(string f_Name)`: Reads lines from a file, cleans comments and whitespace, and returns them as a vector.
- `isDigit(char st)`: Checks if a character is a digit.
- `isDigit1(string st)`: Checks if a string consists only of digits.
- `isAlpha(char st)`: Checks if a character is an alphabet.
- `isAlpha1(string st)`: Checks if a string consists only of alphabets.
- `isOperator(char op)`: Checks if a character is an operator.
- `isOperator1(string st)`: Checks if a string is a valid operator.
- `isSpecial(string st)`: Checks if a string is a special character.
- `isDataType(string st)`: Checks if a string is a data type.
- `isKeyWord(string st)`: Checks if a string is a keyword in the language.
- `isDot(string st)`: Checks if a string is a dot (.).
- `isIdentifier(string id)`: Checks if a string is a valid identifier.

### Classes

#### Node
- Represents a symbol table entry.
- Stores data type, identifier, value, line number, and reference.
- Provides functions to access and print its information.

#### Token
- Represents a token in the language.
- Stores the token string and a validity flag.
- Provides functions to access and modify its information.

#### Lexer
- Takes a list of instructions (lines of code).
- Performs lexical analysis by splitting instructions into tokens and validating them.
- Uses functions like `isIdentifier` and `isOperator1` for validation.
- Returns a list of valid instructions.

#### ST (Symbol Table)
- Manages the symbol table.
- Provides functions to insert, search, update, and show the symbol table.
- Uses `Node` objects to represent entries.

#### Semantic
- Takes a list of instructions (lines of code).
- Performs semantic analysis by checking the structure of instructions.
- Defines functions to identify different types of statements:
  - `isDeclaration`: Checks if a line declares a variable (e.g., `int a;`).
  - `isDeclaration_Definition`: Checks if a line declares and defines a variable (e.g., `int a = 10;`).
  - `isDefinition`: Checks if a line defines a variable (e.g., `a = 20;`).
  - `isManupulation`: Checks if a line manipulates an existing variable (e.g., `a = b + 5;`).
  - `isConditionalStatement`: Checks if a line is a conditional statement (`if`, `else if`, `else`).
  - `DoWhile`: Checks if a line is a `do-while` loop.
  - `while_`: Checks if a line is a `while` loop (implementation incomplete).
- Uses flags like `if_check` and `do_check` to track parsing state within these functions.

## Usage

1. **Compile the Code**: Use a C++ compiler to compile the source code (e.g., `g++ main.cpp -o lexer_symbol_table`).
2. **Run the Program**: Execute the compiled program (e.g., `./lexer_symbol_table`).
3. **Input Code**: Provide lines of code for lexical and semantic analysis.
4. **Review Output**: Check the output for tokens, symbol table entries, and analysis results.

## Note

This code provides a basic framework for lexical and semantic analysis of a simple programming language. It is intended for educational purposes and can be further extended to handle more complex language features and code analysis tasks.

## Future Enhancements

- **Error Handling**: Implement more robust error handling and reporting.
- **Extended Language Features**: Add support for additional language constructs and syntax.
- **GUI Interface**: Develop a graphical user interface for easier interaction and visualization.
- **Code Generation**: Integrate with a code generation module for producing executable code.

## Authors

- **Umair Munir**
- **Qirab Hassan**
- **Omar Ikram**

---

**💻 Keep coding, keep improving—every line you write brings you closer to mastering the craft. 🚀**
