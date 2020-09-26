#Commands for run

```
bison -d calc.y
flex lex.l
g++ calc.tab.c lex.yy.c -o calc -lm
./calc
```

Commands for compiling files