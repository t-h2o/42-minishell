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

<<<<<<< HEAD
here an input example

```
$ echo 'My $HOME' is "-->  /home/user   <--" $PWD':'
line: echo 'My $HOME' is "-->  /home/user   <--" $PWD':'
```

1. change all environment variable
* The name off environment variable is only 
	* lowercase letter
	* upercase letter
	* underscore
* if the environment variable does not exist, there is no character
* the name of environment variable start with a $ and finish with
	* a space
	* a simple quote
	* a double quote

Few example:
```
$PWD"<--"
/c/w/d<--

$PWD'<--'
/c/w/d<--

$PWD <--
/c/w/d <--

\$PWD
$PWD
```

Line example:
```
$ echo 'My $HOME' is "-->  /home/user   <--" $PWD':'
line: echo 'My $HOME' is "-->  /home/user   <--" /c/w/d':'
```

2. Make easier the program, change double quote by single quote

Line example:
```
$ echo 'My $HOME' is "-->  /home/user   <--" $PWD':'
line: echo 'My $HOME' is '-->  /home/user   <--'g /c/w/d':'
```

3. split by spaces line in arguments

Line example:
```
line: echo 'My $HOME' is '-->  /home/user   <--' /c/w/d':'
arg[0] = "echo"
arg[1] = "My $HOME"
arg[2] = "is"
arg[3] = "-->  /home/user   <--"
arg[4] = "c/w/d:"
arg[5] = 0
```

# Test


| command | expected |
| :-| :-|
| `echo '' '' a`	| `  a`	|
| `echo '''a''b''def'`	| `abdef`	|
| `echo  'My $HOME IS' -->$HOME<--`	| `My $HOME IS -->/home/user<--`	|
| `echo $pkeifo is unknow`	| `is unknow`	|
| `echo`	| ` `	|
