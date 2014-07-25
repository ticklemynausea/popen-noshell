#ifndef _POPEN_NOSHELL_H_
#define _POPEN_NOSHELL_H_

/*
 * popen-noshell --
 *
 *      Implementation of popen(3) and pclose(3) functions. This
 *      version keeps information about forked processes, but it is
 *      not thread safe. This function also skips usage of sh to launch
 *      the given process.
 *
 *      Based on
 *          http://cnds.eecs.jacobs-university.de/courses/os-2011/src/popen/popen.c
 *
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct pinfo {
    FILE         *file;
    pid_t         pid;
    struct pinfo *next;
} pinfo;

FILE *
my_popen (char * const command[]);

FILE*
popen_noshell(char * const command[], const char *mode);

int
pclose_noshell(FILE *file);

#ifdef __cplusplus
}
#endif


#endif /* _POPEN_NOSHELL_H_ */
