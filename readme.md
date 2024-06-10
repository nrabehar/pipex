# PIPEX

This project is the discovery in detail and by programming  a ___UNIX___ mecanism that you already know.

## Purpose

This repository serves as a reference for the ___Pipex___ project from ___42 School___. The code and documentation provided here are intended to help you understand the concepts and implementation details of the project.

## Important Notice

Please do not copy and paste the code directly. The purpose of this repository is to help you learn and gain ideas on how to approach the project. To get the most out of this resource, try to understand the code and then implement it in your own way.

## Usage

Feel free to explore the code, read through the comments, and use it as a learning tool. Remember, the goal is to develop your own understanding and problem-solving skills.

### Pipex progam

The goal of _pipex_ is to develop a program that simulates the pipes in the shell, this program has to reproduce exactly the following shell command.

```sh
< file1 cmd1 | cmd2 > file2
```
you can execute the pipex program like this
```sh
./pipex infile cmd1 cmd2 outfile
```

### What this command does ?
```sh
< infile grep ok | wc -w > outfile
```
-   __`<` symbole__ : ___input redirection___ symbole.

    The `<` symbole redirects the content of `infile` to the `stantard input` so that when `grep` is reading from the `standard input`, it gets the content of `inflie`.
    The same command in a more easy to undersand syntaxe :
    ```sh
    grep ok < infile | wc -c > outfile
    ```
-   __`|` symbole__ : ___pipe___ symbole.

    The `|`_(pipe)_ symbole redirects the `output` of the command on the left to the `input` of the command on the right. In this case the `|` symbole redirects the `output` of the `grep` command to the `input` of the `wc` command.
    
    > [!NOTE]
    > Without the pipe symbole,  the output of the `grep` command is written directly to the `standard output`.
-   __`>` symbole__ : ___output redirection___ symbole.

    In our case, the `>` symbole writes the `output` of the `wc` command into the `outfile`.

### Install

```sh
git clone git@github.com:nrabehar/pipex.git
```
just `make` to compile the project and test
```sh
make
```
