# 42-minishell
Create a shell with a team of two

## Documentations

### GNU

* [bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/index.html)


### our

* [parsing](./doc/parsing.md)
* [environmental variable](./doc/envp.md)


## TODO

- [ ] Protect mallocs
	- [x] export_no_arg.c
	- [x] line_exitval.c
	- [x] unset.c
	- [x] utils_table.c
- [x] Fix line_env.c
- [ ] Norminette proof

## Library

```sh
export PKG_CONFIG_PATH=$HOME/.brew/Cellar/readline/8.1.2/lib/pkgconfig
```
