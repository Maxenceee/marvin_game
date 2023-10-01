# Marvin Game

How's Marvin? 42!

## The Game

Create a bunch of files on the Desktop, preventing you from using your Terminal with the parrot, until you find the right file that fixes the mess. For those who does not lock their session 😈

⚠️ Read usage before executing any program, you don't want hundreds of programs doing crap on your machine ⚠️

## Usage

Params:
```
--file-count, -c
	specify the number of generated files (minimun is 2, default is 50, maximum is 🤷‍♂️)
--dir-path, -p
	change active directory (default is Desktop)
--lang, -l
	change `consignes.mxga.txt` lang (default is FR, fr|en)
--no-log, -n
	disable trace file generation
```

#### Linux

Nothing required

#### MacOS

You may need to remove macro statement in some files and there's missing features.

### Quick start

Run `make gen` to compile and start the program. You can add params using the argument `GVAR`.

Example:
```sh
make gen GVAR="-c 200 -p /Users/maxence/Documents"
```

Clone and start:
```sh
git clone https://github.com/Maxenceee/marvin_game.git && cd marvin_game && make gen
```

### Details

Compile the project using `make all` then compile the executables "poison" and "healer" with `make execs`. Once done start the program running `./marvin_game`, adding params if needed.

To fix averything run `make execs && ./healer`

# ## 

Made for `42 School Piscine`, MacOS/Linux