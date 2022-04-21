# creating environmental variable

environmnent pointer (envp)

envp[0] = "HOME=/home/user"
envp[1] = "PWD=/path/actual"
envp[2] = "PATH=/path/bin"
envp[3] = "" // malloc (0)
envp[4] = 0

## unset

unset PWD

```
envp[0] = "HOME=/home/user"
envp[1] = "\0"
envp[1] = "PATH=/path/bin"
envp[0] = 0
```

export \0=3
