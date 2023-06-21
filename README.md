# Marvin Game

## Usage

Params:
```
-c	specify the number of generated files (minimun is 2)
-p	change active directory (default is Desktop)
```

### Overview
Run `make gen` to compile and start the program. You can use params with make gen using the argument `GVAR`.

Example: 
```sh
make gen GVAR="-c 200 -p /Users/maxencegama/Doduments"
```

### Details

Compile the project using `make all` then compile the executable poison and healer with `make execs`. Once done start the program as follow `./marvin_game`.