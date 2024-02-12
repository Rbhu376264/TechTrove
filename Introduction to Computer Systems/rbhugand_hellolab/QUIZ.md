# USC CS356 Spring 2023: Hello Lab (v1.0)


**Q1.** If you run `./hello > out.txt` the messages "Hello ... !" are
redirected to `out.txt` but the instructions are not. Why?

Your Answer:
```
The reason for the above is that '>' redirects the output of one command to another command as standard input and since that only happens for few lines of code so 
it only redirects the those commands rather than entire code snippets.

(Suggestion: Look at the `printf` statements in `hello.c`)

```


**Q2.** How can you redirect both `stdout` and `stderr` to `out.txt`?

Your Answer:
```
To simply do that we can use 2&>1 after the filename to which we want to redirect.

For instance: echo "linuxconfig.org" 2> new-file.txt

(Suggestion: The answer is in README.md)

```


**Q3.** The file `in.txt` contains the input for `hello`. How can you make
`hello` read from `in.txt` instead of `stdin`?

Your Answer:
```
This can simply be done by `./hello < in.txt`

(Suggestion: With `./hello ? in.txt` -- replace the question mark)

```


**Q4.** If you remove the parentheses from the macro `ONE_PLUS_TWICE` in
`hello.c` the output line `Macro example: 26` changes. Why are the parentheses
important?

Your Answer:
```
It changes because arithmetic operatos in C follow the precedence order of BODMAS or PEMDAS.

(Suggestion: Think about the precedence of operators `+` and `*`.)

```


**Q5.** You can compile with `gcc hello.c list.c -o hello`. Why don't you
need to pass `list.h` to GCC?

Your Answer:
```
It is because in C all the .h files are included using #include for a given programming code.

(Suggestion: Think about how #include works in .c files.)

```

**Q6.** Should `make` recompile `hello` when `list.h` changes? How is this
ensured in the `Makefile`?

Your Answer:
```
Yes, and it can be ensured from -MMD -MP options of GCC as -MMD -MP generate .d files so that we know which .h are included in each .c .

(Suggestion:  Look into the -MMD -MP options of GCC and how they are used in Makefile.)

```
