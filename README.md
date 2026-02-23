*This project has been created as part of the 42 curriculum by wchatoui, gderamch.*

# minishell

## Description

Minishell is a simplified shell implementation written in C, inspired by **bash**. The goal of the project is to understand how a Unix shell works under the hood — from parsing user input and expanding environment variables to executing commands with pipes and redirections. It provides an interactive command-line interface where users can run programs, chain commands with pipes, redirect I/O, and use built-in shell commands.

### Features

- Interactive prompt with command history (GNU Readline)
- Pipes (`|`) for chaining multiple commands
- Redirections: input (`<`), output (`>`), append (`>>`), and heredoc (`<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- 7 built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Instructions

### Requirements

- A C compiler (`cc`)
- GNU Readline library (`libreadline-dev` on Debian/Ubuntu)
- `make`

### Compilation

```bash
make        # Build the executable
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Full rebuild
```

### Execution

```bash
./minishell
```

Once launched, the shell displays a `minishell >` prompt. You can then type commands as you would in bash:

```
minishell > echo hello world
hello world
minishell > ls -la | grep src
minishell > cat < infile > outfile
minishell > export FOO=bar
minishell > echo $FOO
bar
minishell > exit
```

## Resources

- [The Open Group Base Specifications — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Bash Reference Manual (GNU)](https://www.gnu.org/software/bash/manual/bash.html)
- [Writing Your Own Shell (Brennan)](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [GNU Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [minishell — 42 Docs](https://harm-smits.github.io/42docs/projects/minishell)

### AI Usage

No AI tools were used during the development of this project.
