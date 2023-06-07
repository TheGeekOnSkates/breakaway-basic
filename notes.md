# TO-DO

* Maybe add aliases.  Why reinvent PRINT when printf is so darn close? :)
* Maybe add INCLUDE - not sure how that would be different from LOAD, but I remember it was a feature some people suggested. :D
* Maybe add an auto-run file.
* Maybe add a way to customize the prompt.  As a sometimes screen-reader user and a Commodore fanatic, "READY.\n" works for me.  But some people might prefer "Ok" like on the TRS-80 Model 100, or "]" like on the Apple ][, or > like in Bash or whatever.
* Maybe finish my weird twist on IF; it's not great, but it's better than nothing
* Maybe play with "popen" and see if using it fixes the CTRL-C bug
* Finish the manual





Old README - use what works, delete what doesn't
===========================================================================

# Known issues

If you code an infinite loop, it can be very hard to exit.  For example:

```
10 printf "What the puck? "
20 goto 10
```

If you hold down CTRL-C long enough, it will eventually exit the loop.  The problem has to do with the fact that it's running external programs, and those are receiving the CTRL-C signals... not sure what else I can do...


# Wish list for a version 2.0

I've nearly finished 1.0, and next time I have a chance to update my "app password" on GitHub I'll push these changes; I'd kinda like to add the rest of my "maybe to-do's" above before pushing to the master branch, but still... after that I'll probably put this project down again for awhile.  Maybe move on to my next game, or back to Pa'lante or something for awhile... but even so, I would eventually like to turn this into a full-fledged BASIC with all the bells and whistles that would make it an even *better* shell.  But since idk if I'll get into that anytime soon, I'm calling this a "wish list" and not a "road map", lol...

* A way to get a single key (might require ncurses, though I'd kinda like to just use Linux APIs (cuz ncurses doesn't have a Windows port, and if portability is ever a thing I'd like, then ncurses is out.  Plus it would be a huge rewrite)).
* Variables, math, string functions and INPUT.
* In the auto-run file, add aliases to make ASCII art easier (set colors, move the cursor, etc.)
	**NOTE:** Some of these are easy; the ones that take parameters (like moving the cursor etc.) will have to wait till variables are done.
* Make my IF like IF in "real" BASICs.  This would be a huge step towards version 2.0...
* As many common commands as possible - CHR$ and ASC and LEFT$ and all that, commands for file I/O, etc.
* And at that point I'll probably be thinking portability too (version 1.0 will just be for Linux)
* If I do go the ncurses route, maybe commands for setting the "window" - i.e. 40 columns centered, 80 columns starting at the top left, etc... not sure if I'll even do that but I kinda like the idea of a Linux terminal that looks like a C64 or a VIC-20 or something. :D
* Of course I'll want to update the manual too
