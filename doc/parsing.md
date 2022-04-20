# parsing

every lines are a group of arguments

## example

simple example.

```
$ echo hello world
arg[0] = "echo"
arg[1] = "hello"
arg[2] = "world"
arg[3] = 0
```

few spaces between words, the result is the same.

```
$ echo      hello  world
arg[0] = "echo"
arg[1] = "hello"
arg[2] = "world"
arg[3] = 0
```

variable environment.

```
$ echo $HOME
arg[0] = "echo"
arg[1] = "/home/user"
arg[2] = 0
```

simple quote. 

```
$ echo 'hello    world'
arg[0] = "echo"
arg[1] = "hello    world"
arg[2] = 0
```

simple quote, will not replace environment variable

```
$ echo 'my     home is  : $HOME'
arg[0] = "echo"
arg[1] = "my     home is  : $HOME"
arg[2] = 0
```

many simple quote will concatenate the arguments

```
$ echo 'abc''''def'
arg[0] = "echo"
arg[1] = "abcdef"
arg[0] = 0
```

example 

```
[ 1 arguments]
$ echo ''a
a

[ 1 arguments]
$ echo ''''a
a

[ 2 arguments]
$ echo '''' a
 a

[ 3 arguments]
$ echo ''     '' a
  a
```

double quote will replace environment variable

```
$ echo "my     home is  : $HOME"
arg[0] = "echo"
arg[1] = "my     home is  : /home/user"
arg[2] = 0
```

## Method

1. replace the environment variable by the value
2. separate elements of the line

0. input
```
$ echo 'My $HOME' is "-->  $HOME   <--"
line:  echo 'My $HOME' is "-->  $HOME   <--"
```

1. change environment variable 
```
line: echo 'My $HOME' is "-->  /home/user   <--"

```
3. echo "My $HOME" is "-->  /home/user   <--"

```
