# TO-DO's

* As I create/change BASIC commands, document them.
* Do some designing.  For example, SYS works, but should it be SYS or sys?  All-caps may look nice in cool-retro term, and make scripting a lot easier, but it would be nice to be able to do i.e. SYS CD /SOME/PATH without having to be hitting Caps Lock.  On the other hand, all-caps for keywords might be a good idea... we'll see.

# KNOWN ISSUES

# FEATURES TO BE ADDED

* Program vs. direct mode (line numbers)
* Branching (IF, GOTO, GOSUB)
* Support for ANSI graphics
* All the math stuff from my old calculator program

---------------------------------------------------------------------------------------------------------

# Breakaway BASIC

## The problem

Bash sucks ice.  Its syntax is a nightmare, a bizarre blend of code and... commands?  I think?  And OMGosh the darn thing has so, _SOOOO_ many config files!  /etc/.profile (I think), /etc/.bash_profile, ./.bashrc and I'm probably missing 4 or 5 more and they all vary from distro to distro and... ugh.  Just... no!  Gimme something a single coder can understand.

## The dream

And I think that's the problem that has led to my building so many "fantasy emulators".  On the C64, I know what I'm doing.  On DOS... well DOS has its own jacked-up codemandline-y thingummy ("Batch") but I can still more-or-less keep it to sane languages.  On Linux... not so much.  One-off commands.  Man it would be so awesome to do something like:

10 clear
20 if root then 30 else 40
30 sudo apt-get install whatever
40 if sudo su then 30 else 50
50 print "Sorry, gotta be an admin"

Shoot, even simpler than that, what if I wanted my terminal to just start out with a fully functional scripting language?  Sure there's Python, and Node, and even that "CBM BASIC" someone created (which is really darn close to what I want).  Simple.  No nonsense.

Up till now (when Bash drove me to bash my head against the monitor), I thought "shell" meant the same thing as "terminal".  But apparently, people are building new shells all the time (there's "zsh" and "fish" and "nushell" and probably others).  So I asked the Duck about it.  According to Wikipedia, a shell is "a computer program which exposes an operating system's services to a human user or other programs".  That's exactly what I want.  I don't need to build my own OS.  I don't have to build my own "computer" emulated in software.  What I want is a computer I can sit down at and "just know" how it all works.  No bottomless rabbit-holes of config files, weird errors and distro differences.  Shoot, maybe this shell I build could even work on Windows!  Or not. :D

## Brainstorming an actual solution

So obviously I got Commodore on the brain tonight, so I'm thinking BASIC.  This means it should have:

* All the essentials like PRINT, INPUT, variables, arrays, branching, etc.
* A file I/O system (i.e. PRINT#, GET#, LOAD, SAVE)
* An easy way to run system commands and get their output and their return code

If I can do that, I'm good to go.

But there's a problem: dependencies.  If I code it in Node, it's all about npm modules; if I code it in Python, there's v2 vs v3 (and v3 is way better but doesn't have full library support yet) and so oo.  So I think what I might do is just do it in standard C.  If OS-dependent code becomes absolutely necessary, I'll go there, but for now I think that's a solid place to start.
