# minishell

A simple shell implementation written in C, built as part of the 42 curriculum. Minishell replicates core features of bash.

## Features

- Interactive prompt with command history (GNU Readline)
- Pipes (`|`) and multiple command chaining
- Redirections: input (`<`), output (`>`), append (`>>`), and heredoc (`<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Built-in commands:
  - `echo` (with `-n` flag)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Build

```bash
make
```

## Usage

```bash
./minishell
```

## Requirements

- `cc` compiler
- GNU Readline library (`-lreadline`)
- Linux / macOS
