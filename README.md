# Breakaway BASIC
A retro-inspired shell scripting environment for Linux

## Overview

This is a project I've been messing with on and off for over a year.  I wanted something simpler, more human-readable than Bash.  I enjoy coding in 8-bit BASICs, and find them a lot easier to follow, so I went with that.  Now, there are lots of projects that come close - and as BASICs go they're a lot better than mine.  So I just feel like I need to list them here:

* [cbmbasic](https://github.com/mist64/cbmbasic), the one that started me down this rabbit-hole, is amazing.  It's Commodore BASIC, somehow decompiled to C (I'd like to use that trick on some NES games, lol), then recompiled for Linux.  But to use it as a shell, you first had to type SYS 1 and then SYSTEM "your command here".  Not case-insensitive, lots of CHR$(34) for quotes... just not great as a shell.
* [fbasic](https://github.com/ratboy666/fbasic) was quite a bit better; It used a weird attempt at a garbage collector (GC) for C, which made it hard to compile on some systems; I had contributed to this one, adding some features and stuff, but fbasic was a college kid's assignment or something so it kinda went nowhere.  Then I discovered Forth and dropped BASIC like a puck! :D
* [BBC BASIC for the Linux Console](https://www.bbcbasic.co.uk/console/) is a solid BASIC too, and one I'm still playing with (though mostly for a little "Stanley Cup of BASICs" article series I'm writing for the Lunduke Journal of Technology).  It solves this problem by allowing users to type shell commands by prefixing them with an asterisk (i.e. `*ls -la`).  But that feature only works in direct mode.  So for shell scripting, it's kinda useless.
* QB64 (a basic _compiler_) has an [interactive interpreter](https://github.com/FellippeHeitor/QB64-interpreter) that I have not tried but kinda want to.  But QB64 (which is also a contender in my Stanley Cup contest) is less like 8-bit BASICs and more like the modern "visual" brand of BASICs (which wasn't what I was looking for, cuz line numbers are actually important if you're gonna be typing stuff in a shell).

Bottom line, there isn't really a BASIC that is well-suited to shell scripting.  All 4 of the above, and also NuShell and language REPLs and stuff are all awesome - and I've used them all as my default shell - but I would still kinda like a BASIC that is made specifically with that purpose in mind.  So here we are, a year or two later, and I'm picking up _Breakaway BASIC_ one more time.


## User's Manual

## Known Issues

## Change Log

## Wish List

