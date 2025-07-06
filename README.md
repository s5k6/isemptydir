Test in shell whether directory is empty
========================================

Summary
-------

This provides command `isemptydir [PATH]`, which returns successfully
if, and only if, `PATH` (defaulting to `.`) is an empty directory.


Need
----

The need to test a directory for emptiness obviously [arises
occasionally][1], and the proposed solutions vary in quality, and tend
to invoke [discussion][2].

IMHO the number of tools invoked to implement such a simple test
should be 1, but proposed solutions typically involve an invocation of
`ls` or `find` and subsequent output processing by `test` or `wc`.
These solutions tend to accumulate a degree of complexity that I
personally find unsatisfying for the task at hand.

Some solutions are more compact, and use only shell builtins, e.g.,

    $ if ! (shopt -s failglob dotglob; : *) 2>/dev/null; then
          echo is empty
      fi

but this may not port nicely to other shells.


Approach
--------

Investigating the solution above

    $ strace -otrace -f \
      sh -c '(shopt -s failglob dotglob; : *) 2>/dev/null'

hints at `getdents64(2)`, the man page of which does provide some
example code.  I've reduced that to the rather small tool in front of
you.


Build
-----

    $ make              # compile isemptydir
    $ make test         # the above, then run tests
    $ make clean        # remove intermdiate files
    $ make distclean    # remove generated files


Use
---

    $ ./isemptydir -h    # print help

See the [builtin help][3].


[1]: https://www.startpage.com/sp/search?query=linux+shell+test+directory+is+empty&cat=web&pl=opensearch&language=english
[2]: https://superuser.com/questions/352289/bash-scripting-test-for-empty-directory
[3]: ./isemptydir.txt
