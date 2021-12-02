# Introduction
*calc* - A program that performs calculations on a series of integers. 
This program will run from the command line. It can run in two different modes:

```bash
calc <engine_name> <file_list>
calc <engine_name> <list of integers>
```
- Files will contain one or more lines of integers.
This program has two engines:
- `multiplier` - multiplies all the integers together
- `divider` - divides all the integers, one after another

A max number of arguments of this program is up to 10. A `mutliplier` engine prints result in range of `int64_t(PRId64)` to `stdout`.
A `divider` engine prints the results with a floating point expression(`double`) to the prompt.

### How to build
You need a compiler `gcc` to build the project. This project is built and tested on `Ubuntu 20.04` and `gcc 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)`. 

There is a `Makefile` so you just type `make` or `make all` to build the project. 
### Documentation
You can build documentation with a simple command `make docs`. Open `docs/html/index.html` with any web browser, then you will see this page which is
converted in html version. Brief explanation of codes, instructions, graphs from variables to functions are supplied to the documentation.

### Adding a new engine
Developers can add additional engines, such as a `stddev`(standard deviation) engine.
To add a new engine, firstly, it is neccesary to understand a structure of `calculator.c`. 

Inside the source code, there is a function `calc` 
which calls arithmetic operations based on input operator and series of data sent from `main` function in `main.c`.

`engine_state` is a function that does a conversion of *string*(engine_name) to *char*('*', '/') for switch/case statement in `calc` function.
`num_strings` is an array which contains series of numbers in a string(char*). `data_len` is a length of a input `num_strings` array.

Then the things to do for adding a new engine are:
 - defining a function, which implements logical operations, to the code `arith.c`.
 - adding a new case to the `calc` function. a single character is recommended for the case match. 
 - defining an `engine_name` with respect to the operation that a user wants, and adding a new rule to the `engine_state` function.
