# Marvin Game

## Usage

Params:
```
-c	specify the number of generated files (minimun is 2, default is 50)
-p	change active directory (default is Desktop)
```

### Overview
Run `make gen` to compile and start the program. You can use params using the argument `GVAR`.

Example: 
```sh
make gen GVAR="-c 200 -p /Users/maxencegama/Documents"
```

### Details

Compile the project using `make all` then compile the executables "poison" and "healer" with `make execs`. Once done start the program as follow `./marvin_game`.