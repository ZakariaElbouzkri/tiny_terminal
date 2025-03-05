# Minishell
Minishell is a minimalistic shell implementation written in C. It is designed to mimic basic functionalities of a Unix shell, including command execution, environment variable handling, and basic built-in commands like `cd`, `echo`, `env`, `export`, `unset`, `pwd`, and `exit`.

## Features
- **Command Execution**: Execute external commands and binaries.
- **Built-in Commands**:
  - `cd`: Change the current directory.
  - `echo`: Print arguments to the standard output.
  - `env`: Print the current environment variables.
  - `export`: Set or update environment variables.
  - `unset`: Remove environment variables.
  - `pwd`: Print the current working directory.
  - `exit`: Exit the shell.
- **Environment Variables**: Support for environment variable expansion and manipulation.
- **Redirection and Pipes**: Support for input/output redirection and piping commands.
- **Signal Handling**: Basic signal handling for `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\).
- **Lexer and Parser**: A custom lexer and parser to handle command input and tokenization.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/minishell.git
   cd minishell
   ```
2. Build the project using `make`:
   ```bash
   make
   ```
3. Run the minishell:
   ```bash
   ./minishell
   ```

## Usage
Once the minishell is running, you can enter commands just like in a regular shell. For example:
```bash
➜  minishell$ echo "Hello, World!"
Hello, World!
➜  minishell$ cd /path/to/directory
➜  minishell$ pwd
/path/to/directory
➜  minishell$ export MY_VAR="Hello"
➜  minishell$ env | grep MY_VAR
MY_VAR=Hello
➜  minishell$ exit
```

## Project Structure
- **`Dockerfile`**: Docker configuration for building and running the project in a container.
- **`Makefile`**: Build configuration for compiling the project.
- **`src/`**: Contains the source code for the minishell.
  - **`builtins/`**: Implementation of built-in commands.
  - **`execution/`**: Code for executing commands, handling pipes, and redirections.
  - **`parsing/`**: Lexer, parser, and utilities for parsing command input.
  - **`libft/`**: Custom library with utility functions (e.g., string manipulation, memory management).
- **`main.c`**: Entry point for the minishell.
- **`minishell.h`**: Header file containing function prototypes and global definitions.

## Dependencies
- **Readline Library**: Used for command line input and history management.
- **GCC**: Compiler for building the project.

## Contributing
Contributions are welcome! If you'd like to contribute, please fork the repository and create a pull request with your changes.

## Acknowledgments
- This project was inspired by the Unix shell and various open-source shell implementations.
- Special thanks to the creators of the `readline` library for providing an excellent tool for command line input handling.

## Author
- [Zakaria El Bouzkri](https://github.com/zakariaelbouzkri)
- [Achraf Settar](https://github.com/asettar)