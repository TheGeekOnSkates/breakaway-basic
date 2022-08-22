# Thoughts / plans for version 0.2

* Use GNU readline for Linux (If I ever build for DOS or something else that doesn't have readline, that system can use fgets like I am now).
* Add support for parens again (already started); for people like me, who are not Algebrainiacs, parens help.  3 * 4 / 2 is not as clear to me as 3 * (4 / 2).
* Add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Maybe add some stuff I haven't yet - like  ROWS(), COLUMNS(), and anything else that's easy

# If I make it to version 1.0

* Aliases - that was really cool on the old version
* Variables with names longer than 1 character (unnecessary, but useful).
* Variables ending in $ being strings
* Set up LET so I can just do i.e. X = 7 (debating about this, cuz what if users want to run a command like ./my-script name="some file"?  The quotes make it hard to use `SYS`, and the = means it would be treated like a `LET`... maybe this should wait till after I have string-expressions and CHR$ and all that. :)
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* Variables with parens being arrays
* Sound (technically possible with SYS "play somesound.wav" but a built-in API would be nice).

## How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
