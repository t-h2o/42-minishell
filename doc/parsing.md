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

here an input example

```
$ echo 'My $HOME/Doc' is "-->  $HOME/Doc   <--"   $PWD':'
line: echo 'My $HOME' is "-->  /home/user/Doc   <--"   $PWD':'
```

1. change all environment variable

The environment variable begin with a '$' and
ends once it reaches to another character of this:
* lowercase letter
* upercase letter
* underscore
```
examples:
$V-e   --> V
$V_e-a --> V_e
$Ve a  --> Ve
$Ve/a  --> Ve
$Ve1a  --> Ve
$Ve"a" --> Ve
$Ve'a' --> Ve
\$Ve   --> not a variable
```

Line example:
```
$ echo 'My $HOME' is "-->  $HOME   <--" $PWD':'
0. line: echo 'My $HOME' is "-->  $HOME   <--" $PWD':'
1. line: echo 'My $HOME' is "-->  /home/user   <--" /c/w/d':'
```
