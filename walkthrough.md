# Minishell Execution Implementation Walkthrough

## Changes Made

### Execution Module
- **[NEW] `src/execution/executor.c`**: Implemented the main execution loop (`execute_cmds`) handling pipes, forks, and child process execution.
- **[NEW] `src/execution/exec_utils.c`**: Added `find_path` to locate executables and `free_cmds` for cleanup.
- **[NEW] `src/execution/redirections.c`**: Implemented `handle_redirections` for input/output redirection and heredoc support.
- **[NEW] `src/execution/signals.c`**: Added signal handling for child and parent processes during execution.

### Parsing Module
- **[NEW] `src/parsing/parser.c`**: Implemented `parse_tokens` to convert flat token list into structured `t_cmd` list with arguments and redirections.
- **[NEW] `src/parsing/expander.c`**: Implemented `expand_token_value` to handle environment variable expansion (`$VAR`) and quote removal.

### Built-ins
- **[NEW/MODIFIED] `src/built-in/cd.c`**: Implemented `ft_cd` with environment updates (`PWD`, `OLDPWD`).
- **[NEW/MODIFIED] `src/built-in/echo.c`**: Implemented `ft_echo` (with `-n`) and `ft_pwd`.
- **[NEW] `src/built-in/env_utils.c`**: Utilities to manage environment variables (`t_env` list).
- **[NEW] `src/built-in/builtins_extra.c`**: Implemented `ft_env`, `ft_export`, `ft_unset`, `ft_exit`.

### Core Integration
- **[MODIFIED] `src/main.c`**: Updated `miniloop` to integrate tokenization -> parsing -> execution -> cleanup cycle. Added environment initialization.
- **[MODIFIED] `inc/minishell.h`**: Added necessary prototypes and structure definitions.
- **[MODIFIED] `Makefile`**: Updated source file list to include all new modules.

## Validation Results

### Manual Verification
The implementation was verified by running `minishell` and piping commands to it.

#### 1. Simple Commands
**Command:** `echo hello world`
**Output:**
```
hello world
```
✅ Success

#### 2. Environment Variables & Expansion
**Command:**
```bash
export TESTVAR=123
echo $TESTVAR
```
**Output:**
```
123
```
✅ Success

#### 3. Pipes
**Command:** `ls | wc -l`
**Output:**
```
       6
```
(Matches file count in directory)
✅ Success

#### 4. Built-ins (cd & pwd)
**Command:**
```bash
pwd
cd ..
pwd
```
**Output:**
```
/Users/guillaume_deramchi/Documents/minishell
/Users/guillaume_deramchi/Documents
```
✅ Success
