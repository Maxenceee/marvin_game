# Marvin Game

How's Marvin? 42!

## The Game

Create a bunch of files on the Desktop, preventing you from using your Terminal with the parrot, until you find the right file that fixes the mess. For those who does not lock their session 😈

## Usage

Params:
```
-c	specify the number of generated files (minimun is 2, default is 50)
-p	change active directory (default is Desktop)
```

### Quick start

Run `make gen` to compile and start the program. You can add params using the argument `GVAR`.

Example:
```sh
make gen GVAR="-c 200 -p /Users/maxencegama/Documents"
```

### Details

Compile the project using `make all` then compile the executables "poison" and "healer" with `make execs`. Once done start the program running `./marvin_game`.

# ## 

Made for `42 School Piscine`, MacOS/Linux