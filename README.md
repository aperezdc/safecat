safecat
=======

From the [original README](README):

>  safecat is an implementation of D. J. Bernstein's maildir algorithm.
>  It can be used to write mail messages to a qmail-style maildir, or to
>  write data to a "spool" directory reliably. There are no lockfiles with
>  safecat, and nothing is left to chance. If safecat returns a successful
>  exit status, then you can be (practically) 100% sure your data is
>  safely committed to disk. Further, if data is written to a directory
>  using safecat (or other implementations of the maildir algorithm),
>  then every file in that directory is guaranteed to be complete. If
>  safecat fails to write all of the data, there will be no file at all
>  in the destination directory.
>
>  Of course, you know that such a thing cannot be: between UNIX and
>  the different hardware options available, a 100% guarantee is not
>  possible. However, safecat takes every precaution possible in writing
>  your data.

The website for the program is long gone, and this is my personal effort of
bringing it back to life by importing the tarballs of versions 1.11 and 1.13
(which can be found in Gentoo's `distfiles` mirrors), modernizing the code base
a bit, and in general making sure that it keeps working.

Development
-----------

**No new features will be added, only maintenance of the project is done.**
If something, code has been —and will be— removed if it is unneeded or
irrelevant for contemporary operating systems The code *might* be modernized
one bit at a time if that yields a clearly simpler implementation.

The following is a shortlist of the cleanups which have been already done:

- [Meson](http://mesonbuild.com/) is used for building. This alone has removed
  46 files (1689 LOC). In contrast, the build files for meson are ~100 LOC
  only, and it automatically enables niceties like 64-bit large file support.

- Use `stdint.h` to gain access to definitions of 64-bit types like `uint64_t`
  (shaves 20 LOC).

- Removed the version string, which was not used anywhere (10 LOC less).

- Include the needed headers to ensure function definitions are taken from the
  system headers, instead of local definitions which might not match those of
  the C library being used.

- Removed reading `$DTLINE` and `$RPLINE` from the environment. This was in
  `writefile.c` which was imported from the qmail source tree, and makes no
  sense for `safecat` (and kill 90 LOC).
