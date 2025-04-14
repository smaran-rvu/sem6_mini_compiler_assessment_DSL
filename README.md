# Mini Compiler for a Domain-Specific Language for Educational Assessments

## Overview

This project is a compiler for a custom assessment language designed for educational purposes. The compiler reads assessment definitions from a source file, constructs an Abstract Syntax Tree (AST), performs semantic analysis, and prepares for code generation.

## Requirements

> This version of the project is only supported in Linux And macOS systems. For Windows uses, use WSL  

To build and run the Assessment Compiler, you will need the following software installed on your system:

1. **Flex**: A fast lexical analyzer generator.
   - Installation:
     - On Ubuntu: `sudo apt-get install flex`
     - On macOS: `brew install flex`

2. **Bison**: A parser generator that is compatible with Yacc.
   - Installation:
     - On Ubuntu: `sudo apt-get install bison`
     - On macOS: `brew install bison`

3. **GCC (GNU Compiler Collection)**: A compiler system supporting various programming languages.
   - Installation:
     - On Ubuntu: `sudo apt-get install build-essential`
     - On macOS: `brew install gcc`

4. **C Standard Library**: Ensure you have a C compiler that supports the C standard library.

Make sure to have these tools installed and properly configured in your system's PATH to successfully compile and run the project.

## Features

- **Lexical Analysis**: Uses Flex to tokenize the input assessment file.
- **Parsing**: Utilizes Bison to parse the tokenized input and build the AST.
- **Semantic Analysis**: Validates the structure of the AST to ensure it adheres to the defined rules.
- **AST Representation**: Constructs a hierarchical representation of the assessment structure.
- **Error Reporting**: Provides detailed error messages for both lexical and semantic errors.

## Project Structure

```bash
/sem6_mini_compiler_assessment_DSL
│
├── assessment.y # Bison grammar file for parsing
├── assessment.l # Flex file for lexical analysis
├── ast.h # Header file defining the AST structure
├── ast.c # Implementation of AST operations
├── semantic.h # Header file for semantic analysis functions
├── semantic.c # Implementation of semantic analysis
├── sample.edu # Sample assessment file for testing
└── README.md # Project documentation
```

## Installation

1. Ensure you have the following tools installed:
   - Flex
   - Bison
   - GCC (GNU Compiler Collection)

2. Clone the repository:
   ```bash
   git clone https://github.com/smaran-rvu/sem6_mini_compiler_assessment_DSL.git
   cd sem6_mini_compiler_assessment_DSL
   ```

3. Compile the project:
   ```bash
   bison -dy assessment.y
   flex assessment.l
   gcc -c -Wall -g ast.c
   gcc -c -Wall -g semantic.c
   gcc -Wall -g -o assessment_compiler lex.yy.c y.tab.c ast.o semantic.o -lfl
   ```
   > If using a MacOS System, use  
   `gcc -Wall -g -o assessment_compiler lex.yy.c y.tab.c ast.o semantic.o -ll`

## Usage

To run the compiler, use the following command:

```bash
./assessment_compiler <input_file>
```

Replace `<input_file>` with the path to your assessment file (e.g., `sample.edu`).

## Example

Here is an example of a valid assessment file:

```plaintext
ASSESSMENT "Biology Quiz" {
    SECTION "Cell Structure" {
        MC_QUESTION "Which organelle is responsible for energy production?" {
            OPTION "Nucleus" INCORRECT
            OPTION "Mitochondria" CORRECT
            OPTION "Ribosome" INCORRECT
            OPTION "Golgi apparatus" INCORRECT
            FEEDBACK "Mitochondria are often called the powerhouse of the cell."
        }
        TF_QUESTION "Prokaryotic cells contain a nucleus." {
            ANSWER FALSE
            FEEDBACK "Prokaryotic cells do not have membrane-bound organelles."
        }
    }
}
```

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

## Acknowledgments

- [Flex](https://github.com/westes/flex) - Fast lexical analyzer generator
- [Bison](https://www.gnu.org/software/bison/) - Parser generator