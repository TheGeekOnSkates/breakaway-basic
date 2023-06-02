# Breakaway BASIC

## Overview

A year or two ago, I wanted something more human-readable and easy-to-follow than Bash.  Then I discovered that a shell is just the program that runs in your terminal, and that pretty much any interactive command-line program can be a shell.  So REPLs like Gforth, Python, PHP, Node etc. are fair game, which is awesome.  And people have invented other Bash-like ones, fish and lish and zish (but no "wish"?  What's wrong with these people who name shells? lol) and my favorite of the "Bashy Bunch", NuShell.  But I wanted something simpler.  I lenjoy programming in 8-bit BASICs, so I wanted a shell like that (and had all kinds of fun learning how _not_ to build one).  So looking at the available options:

* [cbmbasic](https://github.com/mist64/cbmbasic), the one that started me down this rabbit-hole, is amazing.  It's Commodore BASIC, somehow decompiled to C (I'd like to use that trick on some NES games, lol), then recompiled for Linux.  But to use it as a shell, you first had to type SYS 1 and then SYSTEM "your command here".  Not case-insensitive, lots of CHR$(34) for quotes... just not great as a shell.
* [fbasic](https://github.com/ratboy666/fbasic) was quite a bit better; It used a weird attempt at a garbage collector (GC) for C, which made it hard to compile on some systems; I had contributed to this one, adding some features and stuff, but fbasic was a college kid's assignment or something so it kinda went nowhere.  Then I discovered Forth and dropped BASIC like a puck! :D
* [BBC BASIC for the Linux Console](https://www.bbcbasic.co.uk/console/) is a solid BASIC too, and one I'm still playing with (though mostly for a little "Stanley Cup of BASICs" article series I'm writing for the Lunduke Journal of Technology).  It solves this problem by allowing users to type shell commands by prefixing them with an asterisk (i.e. `*ls -la`).  But that feature only works in direct mode.  So for shell scripting, it's kinda useless.
* QB64 (a basic _compiler_) has an [interactive interpreter](https://github.com/FellippeHeitor/QB64-interpreter) that I have not tried but kinda want to.  But QB64 (which is also a contender in my Stanley Cup contest) is less like 8-bit BASICs and more like the modern "visual" brand of BASICs (which wasn't what I was looking for, cuz line numbers are actually important if you're gonna be typing stuff in a shell).

Bottom line, there isn't really a BASIC that is well-suited to shell scripting.  All 4 of the above, and also NuShell and language REPLs and stuff are all awesome - and I've used them all as my default shell (still using Gforth) but I would still kinda like a BASIC that is made specifically with that purpose in mind.  So here we are, a year or two later, and I'm picking up _Breakaway BASIC_ one more time.

# Roadmap

## To version 1.0

I'm not going to both with implementing PRINT and INPUT and all those other things 8-bit BASICs have.  For now I'm just focusing on:

* Program mode vs. direct mode
* Branching words (GOTO, GOSUB, RETURN etc.)
* Comments (REM)
* A subset of IF ... THEN ... ELSE; every command has a return value (see the standard C "system" function).  This will be used for conditional branching.  For example:

```
10 some-command-that-fails --crash
20 if 0 then 100 else 200
```

Note that there's no actual condition there - the return value of the last command is that condition.

And all other code will run system commands.  This would make it possible to do things like:

```
10 gcc ./someFile.c -otest || exit 1
20 rem Or run a Makefile if line 10 would exit BASIC :D
30 if not 0 then 70
40 clear
50 echo "It worked."
60 end
70 echo "It failed."
80 aplay "./angry-beep.wav"
```

Is it ideal?  Puck no!  Is it a fully functional shell that I could use as a drop-in replacement for Bash?  Yup.

## To future 1.x releases

* Add GNU Readline - maybe make it an optional thing for portability
* Aliases.  Why reinvent PRINT when "echo" is so darn close? :)
* Commands to make ASCII art easier (set colors, move the cursor, etc.)
	Idea: These can be aliases; i.e. ALIAS RED_TEXT = printf "\e[31m"
* Maybe a way to get a single key (might require ncurses, might not).
* Commands like LOAD, SAVE and INCLUDE
* For-loops
* Variables, math and INPUT.
* IF I can get variables working, make my IF like IF in "real" BASICs.  This would be a huge step towards version 2.0...

## To version 2.0

If (Lord willing, HWEN) I make it this far, then it'll be time to turn Breakaway BASIC into a full-fledged 8-bit-style BASIC:

* As many common commands as possible - CHR$ and ASC and LEFT$ and all that
* Commands for file I/O
* And at that point I'll probably be thinking portability too (version 1.0 will just be for Linux)
