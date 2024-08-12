# Minishell

Minishell is a simple Unix shell implementation designed for educational purposes. It allows users to execute commands, manage processes, and handle basic shell functionalities.

## Features

- Execute shell commands
- Support for input and output redirection
- Pipe support between commands
- Environment variable management
- Built-in commands (cd, exit, echo, export, unset, env, pwd)
- Signal handling

## Installation

To build and run Minishell, follow these steps:

* if want to test without reviewing the code try with docker:
	```bash
		docker run -it zelbouz/minishell
	```

1. Clone the repository:
   ```bash
   git clone https://github.com/zakariaelbouzkri/minishell.git
   cd minishell
   ```

## Building

You can build the project locally or use Docker.

### Local Build

To build the project locally, run:

```bash
make
./minishell
```

### Docker Build

To build the project using Docker:

2. Build the Docker image:

   ```bash
   docker build -t minishell .
   ```

3. Run the container:

   ```bash
   docker run -it minishell
   ```
