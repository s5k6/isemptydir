Test if directory is empty in bash
==================================

In bash scripts, I use:

    $ if ! (shopt -s failglob dotglob; : *) 2>/dev/null; then
          echo is empty
      else
          echo has content
      fi

What's going on?

    $ strace -otrace -f \
      sh -c '(shopt -s failglob dotglob; : *) 2>/dev/null'

This hints at `getdents64(2)`, which does provide example code.  I've
reduced that to the rather small `isemptydir.c`, thus:

    $ make
    $ if ./isemptydir; then
          echo is empty
      else
          echo has content
      fi

Try `isemptydir -h` for help.


[1]: https://superuser.com/questions/352289/bash-scripting-test-for-empty-directory