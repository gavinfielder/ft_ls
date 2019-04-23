# ft\_ls

A recode of the UNIX shell command `ls`. Part of 42 Curriculum.

## Mandatory Options Implemented

 - `-l` long form
 - `-R` recursive directory listing
 - `-a` show hidden files
 - `-t` sort by time
 - `-r` reverse sort order

## Bonuses Implemented

 - ACL
 - Multi-column output
 - Code optimization (mine is typically ~50% faster than system ls)
 - `-C` force multi-column output (default)
 - `-G` colorized output
 - `-S` sort by file size
 - `-U` use file creation time for sorting and output
 - `-c` use file status change time for sorting and output
 - `-d` list directories as normal files (no expanded search)
 - `-e` print access control list
 - `-f` unsorted output (unlike system ls, mine doesn't turn on `-a` with this)
 - `-g` POSIX compatibility group name (owner name is suppressed)
 - `-m` Print as comma separated values
 - `-n` display user and group ids numerically
 - `-u` use time of last access for sorting and output
 - `-1` force single-column output
 - `-@` print extended attributes
 - `-[2-9]` (not a feature of standard ls) limit recursion depth when used with `-R`

## Credits

All code is written by me