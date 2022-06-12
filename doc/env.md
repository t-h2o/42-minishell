# Environmnent pointer

Environmnent pointer (envp) are
the table of environment variables of the current program.

## Learn about envp

To experiment what is envp, we can play with a debugger.

Create a little program

```c
int main(int argc, char **argv, char **envp)
{
    ...
}
```

And then try to print `envp[0]`, `envp[n]`,...

`envp` is a table of string with more space, like that, you can add string
in the table without realloc a new table with +1 space for your new string.

## Creating environmental variable

Duplicate the strings table into our table.
If we need to export variables,
we will realloc a new table with the news variables.

If we need to unset variables,
we will realloc a new table without the variables.
