#define _GNU_SOURCE

#include <dirent.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>



/* This is largely copied from the example given in getdents64(2). */

struct linux_dirent64 {
    ino64_t d_ino;
    off64_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[];
};



#define BUF_SIZE 1024



int main(int argc, char **argv) {

    const char *path = NULL;
    int oflags = 0;

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-h") == 0 ) {
            printf(
                "\n"
#include "isemptydir.help"
                "\n"
            );
            return 0;
        }

        if (strcmp(argv[i], "-n") == 0 ) {
            oflags |= O_NOFOLLOW;
            continue;
        }

        if (argv[i][0] == '-')
            errx(2, "Unknown `%s`, try `%s -h`.", argv[i], argv[0]);

        if (! path)
            path = argv[i];
        else
            errx(2, "At most one path argument, try `%s -h`.", argv[0]);
    }

    int fd = open(path ? path : ".", O_RDONLY | O_DIRECTORY | oflags);
    if (fd < 0)
        err(2, "open %s", path);

    char buf[BUF_SIZE];

    ssize_t n;
    do {
        //n = syscall(SYS_getdents, fd, buf, sizeof(buf));
        n = getdents64(fd, buf, sizeof(buf));
        if (n < 0)
            err(2, "getdents");

        for (ssize_t i = 0; i < n;) {
            struct linux_dirent64 *d = (struct linux_dirent64 *)(buf + i);

            i += d->d_reclen;

            if (strcmp(d->d_name, ".") == 0)
                continue;

            if (strcmp(d->d_name, "..") == 0)
                continue;

            return 1; // found "real" entry, dirempty not empty.
        }

    } while (n > 0);

    return 0;
}
