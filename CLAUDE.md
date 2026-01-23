# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

```bash
make          # Build minishell executable
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Full rebuild
make norm     # Run norminette style checker (42 school standard)
```

**Run:** `./minishell`

## Compilation

- Compiler: `cc` with flags `-Wall -Wextra -Werror -g3`
- Links against: libft (custom static library) and readline
- All code must pass `norminette` (42 school style checker)

## Architecture

### Data Flow
User input → Tokenizer → Parser → Command structures → Executor

### Core Data Structures (inc/minishell.h)

- **t_env**: Linked list for environment variables (name/value pairs)
- **t_token**: Linked list of lexical tokens with type, value, and index
- **t_cmd**: Command structure with args array, redirections, file descriptors, and pipe linkage
- **t_redir**: Linked list for redirections (type, file, heredoc_fd)

### Token Types (e_token_type)
`WORD`, `PIPE`, `REDIR_IN`, `REDIR_OUT`, `HEREDOC`, `APPEND`, `CMD`, `ARG`, `FILE_IN`, `FILE_OUT`, `LIMITER`, `FILE_APPEND`

### Source Organization

- `src/main.c` - Entry point, REPL loop, tokenizer
- `src/env.c` - Environment variable initialization and linked list management
- `src/token.c` - Token memory management
- `src/built-in/` - Built-in command implementations (echo, cd)
- `inc/42-libft/` - Custom standard library (63 functions including get_next_line)

### Global State
- `extern int g_sig` - Signal handling flag

## Dependencies

- **libft**: Custom 42 library at `inc/42-libft/` (auto-built by main Makefile)
- **readline**: GNU readline library for input handling
