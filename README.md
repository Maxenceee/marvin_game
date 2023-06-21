# Marvin Game

## Usage

Params:
```
>	-c	specify file_count
>	-p	change active directory (default is Desktop)
```

### Overview
Run `make gen` to start and launch the program. You can use params with make gen using the argument `GVAR`.

Example: 
```sh
make gen GVAR="-c 200 -p /Users/maxencegama/Doduments"
```

### 

Compile the project using `make all` then compile the executable poison and healer with `make execs`. Once done start the program as follow `./marvin_game`.