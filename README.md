# TO-DO's (in no particular order)

* As I create/change BASIC commands, keep updating the docs.
* Keep working on multiple GOSUBs, nested GOSUBs etc - almost there!
* Fix REVERSE
* Add i.e. MOVE x y to move the cursor, PUT x y character, COLOR x y color...

# KNOWN ISSUES

* GOSUB/RETURN - nested GOSUBs seem to work now, but not two GOSUBs back-to-back (see latest test)
* REVERSE isn't working - not sure why (probably an ID10T error :D)


# FEATURES TO BE ADDED

* IF
* Playing with the idea of aliases.  For example:

	ALIAS CD SYS cd
	REM THIS IS LIKE A FIND-&-REPLACE, SO...
	CD /path/to/whatever
	REM IT WOULD REPLACE "CD " WITH "SYS cd "
	REM NOTE THE SPACES ABOVE

If I really wanted to get fancy, I could have an auto-run file to set these aliases up automagically - but that's *waaaay* down the road...

* Variables & arrays
* GET and INPUT
* Looping (FOR, _maybe_ WHILE)
* All the math stuff from my old calculator program
* With the math stuff done, PRINT (have it eval math, combine strings, and call the echo command which already works kinda like PRINT)
* Advanced file I/O: OPEN and CLOSE, GET# and INPUT#, PRINT#, CLEAR# etc.
* __MAYBE__ an auto-run file (kinda like a config file, but not really... think autoexec.bat in DOS :D)

And by the time I get here, idk what else I could possibley need/want.  I can write aliases for things like speech (i.e. `ALIAS SAY SYS easpeak `), sound, and things like listing files.  And if I'm using this with a screen reader, the screen reader will automatically speak stuff as I PRINT it anyway... now 3D sound is a bit tricky, but IMO that's a different project entirely.  And if I write that program, I can make aliases for that in Breakaway BASIC too :)

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
