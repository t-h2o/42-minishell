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

```plain
envp[0] = "HOME=/home/user"
envp[1] = "PWD=/path/actual"
envp[2] = "PATH=/path/bin"
envp[3] = "" // malloc (0)
envp[4] = 0
...
envp[n] = 0
```

## unset

Unset PWD

```
envp[0] = "HOME=/home/user"
envp[1] = "\0"
envp[2] = "PATH=/path/bin"
envp[3] = ""
```

export \0=3
