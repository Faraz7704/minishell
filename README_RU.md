#minishell
## The purpose of this project is to write your own shell that mimics the work of bash.
[subject](https://github.com/luta-wolf/minishell/blob/master/doc/en.subject.pdf)
### Introduction

There was a time when all developers agreed that communicating with a computer using a 1/0 switch was seriously annoying. It is only logical that they came up with the idea of ​​creating software for communicating with a computer using interactive command lines in a language somewhat close to human. Thanks to Minishell, you can travel back in time and go back to problems when people were faced with the fact that Windows did not exist.

### Main part
Your shell should:
- Display <b>prompt</b> when waiting for a new command.
- You have a <b>history</b> of work.
- Find and run the desired executable file (based on the `PATH` variable or using a relative or absolute path).
- Do not use more than <b>one global variable</b>. Think about it. You will have to explain its purpose.
- Do not interpret unclosed quotes or special characters that are not required by the subject, such as `\` (backslash) or `;` (semicolon).
- <b>`'`</b> (single quote), which should prevent the shell from interpreting the metacharacters in the quote sequence.
- <b>`"`</b> (double quote), which should prevent the shell from interpreting metacharacters in the quote sequence except for `$` (dollar sign).
- Implement redirects:
    - `<` should redirect input.
    - `>` should redirect the output.
    - `<<` should specify a delimiter, and then read the input until a string containing the delimiter appears. However, it should not update history!
    - `>>` should redirect output in append mode.
- Implement <b>pipes</b> (`|` symbol). The output of each instruction in the pipeline is connected to the input of the next instruction through a pipe.
- Handle <b>environment variables</b> (`$` followed by a character sequence) that should be expanded to their values.
- `$?` which should expand to the exit state of the most recently executed foreground pipeline.
- Handle the `Ctrl-C`, `Ctrl-D` and `Ctrl-\` signals, which should behave like in bash.
- In interactive mode:
    - `Ctrl-C` displays the new prompt on a new line.
    - `Ctrl-D` exits the shell.
    - `Ctrl-\` does nothing.
- Your shell must implement the following <b>built-in</b> functions:
    - `echo` with `-n` option
    - `cd` with relative or absolute path only
    - `pwd` without options
    - `export` without options
    - `unset` without options
    - `env` with no options or arguments
    - `exit` without options

The readline() function can leak memory. You don't need to fix them. But this <b>doesn't mean that your own code, yes, the code you wrote, can have memory leaks</b>.

### Bonus part
Must be implemented:
- `&&` and `||` with brackets for precedence.
- Wildcards `*` should work for the current working directory.

Testers
-------
- [first](https://github.com/alchrist42/msh_tester)
- [second](https://pypi.org/project/minishell-test/#description)
<img width="766" alt="image" src="https://user-images.githubusercontent.com/58044383/169036722-1a7d57c0-e7c6-4b50-99db-edb5e6e648d6.png">

Check list
-------
[checklist](https://github.com/luta-wolf/minishell/blob/master/doc/checklist_minishell.pdf)
<img width="1014" alt="image" src="https://user-images.githubusercontent.com/58044383/169034673-13408430-65ac-4e05-a69e-eb4c023f6262.png">

<!-- <details>
<summary>Useful materials</summary> -->

Useful materials
