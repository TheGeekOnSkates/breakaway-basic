# New direction

Breakaway BASIC has kinda plateaued recently; all the things I wanted to add were these massive undertakings I just didn't want to waste time on.  So instead, I decided I would contribute to the awesome [CBM BASIC](https://github.com/mist64/cbmbasic) project instead.  Well, in the discussion of one of their issues, someone going by the nickname of "ratboy666" (and I thought the Geek on Skates was a funny nickname lol) shared a project he did 20 years ago called [fbasic](https://github.com/ratboy666/fbasic).  I forked it, played with it, and realized it was already nearly everything I wanted Breakaway BASIC to be.  I would have liked for it to have some of the features of my BASIC (auto-run files, aliases etc.) but it's a solid, robust, compact little BASIC.  It also taught me a lot about how to parse random code entered by users.  In previous attempts at building my own BASIC, I had experimented with the whole "tokenizing" thing, but found it much harder than it had to be.  But it would have helped if I had actually seen a working BASIC as an example.  And that's what I've got now.

But the thing is, fbasic was (by the original programmer's own admission) a "quick and dirty hack", and it shows.  It depended on some kind of crazy garbage collection library that looks like a bear to build, and it also uses (what I think is) the original "curses" library (not the same thing as ncurses).  The guy did include plenty of comments, and I know C well enough to where I can figure out most of what he is doing... but trying to hack his code into something that compiles today has been kinda tricky.  Not to mention, the compiler complains "{something he did that I don't understand} is DANGEROUS.  Use {something else} instead."  lol yikes!  My current fork of fbasic leaks memory (despite a friend's attempt at re-adding the GC) and I'm kinda thinking a fresh start is the way to go.  I'm not going to copy/paste fbasic's code, but rather study it line-by-line to see how he did it, and try to reproduce the good parts without the bad.  What I'm trying to build is gonna be written in standard C, to make it as portable as possible.  I'm targeting DOS for now, cuz all my devices have a DOSBox-like app on them, but of course I also plan to build for Linux (x86, Termux and the Raspberry Pi) and keep it portable with other OSes.  Maybe even get it working on "Mobile C" on iOS lol...

I'm also changing licenses, cuz I've heard there's a sneaky-twist in the UNLICENSE that makes it not as freed as I'd like.  MIT license, based on my not-a-legal-beagle perspective, just translates to "keep the license in the source and don't sue me if it doesn't work or breaks something" which I can live with.  Also, fbasic is MIT licensed, and since my code will be _heavily_ inspired by ratboy's (lol) I figure better to keep it consistent with what he wanted.

## To-Do's

I'm sure they'll get A LOT lower-level than this, but for now the general game plan is:

* Finish the Tokenize and UnTokenize functions
		- Get UnTokenize to print string literals
		- Get UnTokenize to print numbers (including decimal points, but watch out for trailing ones, like "3.0.")
		- For UNKNOWN, have UnTokenize just print the unknown character
* Look at how fbasic actually _interprets_ those tokens and do what makes sense. :)
* Figure out how fbasic does variables and arrays.  To truly finish UnTokenize, I'll need to print the variables' names (not values)
* Go through the list of instructions, documenting each one and writing examples when they're done.  Those examples will play an important part in both my docs and my pre-release testing.
* Figure out another way to handle errors; right now just printing "SYNTAX ERROR" or whatever gets the job done... but fbasic did something different
* Once all commands work correctly in isolation, get program mode working.
* At that point, try and add some more of the other nice features I had before (ALIAS, BG, FG, auto-run files, ITALIC, UNDERLINE etc.)
* If (and Lord willing, _when_) I get to this point, set up a wiki, port it like crazy, and call it done!  :)
