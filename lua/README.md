# Compiling Lua Script

For compiling lua script:
```
g++ -std=c++17 -o test test_lua_script.cpp -I/usr/local/include -L/usr/local/lib -llua -lm
```