#include "popen-noshell.h"

static pinfo *plist = NULL;


FILE* popen_noshell(char * const command[], const char *mode)
{
    int fd[2];
    pinfo *cur, *old;

    if (mode[0] != 'r' && mode[0] != 'w') {
        errno = EINVAL;
        return NULL;
    }

    if (mode[1] != 0) {
        errno = EINVAL;
        return NULL;
    }

    if (pipe(fd)) {
        return NULL;
    }

    cur = (pinfo *) malloc(sizeof(pinfo));
    if (! cur) {
        errno = ENOMEM;
        return NULL;
    }

    cur->pid = fork();
    switch (cur->pid) {
        
    case -1:                    /* fork() failed */
        close(fd[0]);
        close(fd[1]);
        free(cur);
        return NULL;
        
    case 0:                     /* child */
        for (old = plist; old; old = old->next) {
            close(fileno(old->file));
        }
        
        if (mode[0] == 'r') {
            dup2(fd[1], STDOUT_FILENO);
        } else {
            dup2(fd[0], STDIN_FILENO);
        }
        close(fd[0]);   /* close other pipe fds */
        close(fd[1]);
        
        execvp(*command, command);
        _exit(1);

    default:                    /* parent */
        if (mode[0] == 'r') {
            close(fd[1]);
            if (!(cur->file = fdopen(fd[0], mode))) {
                close(fd[0]);
            }
        } else {
            close(fd[0]);
            if (!(cur->file = fdopen(fd[1], mode))) {
                close(fd[1]);
            }
        }
        cur->next = plist;
        plist = cur;
    }

    return cur->file;
}

int pclose_noshell(FILE *file)
{
    pinfo *last, *cur;
    int status;
    pid_t pid;

    /* search for an entry in the list of open pipes */

    for (last = NULL, cur = plist; cur; last = cur, cur = cur->next) {
        if (cur->file == file) break;
    }
    if (! cur) {
        errno = EINVAL;
        return -1;
    }

    /* remove entry from the list */

    if (last) {
        last->next = cur->next;
    } else {
        plist = cur->next;
    }

    /* close stream and wait for process termination */
    
    fclose(file);
    do {
        pid = waitpid(cur->pid, &status, 0);
    } while (pid == -1 && errno == EINTR);

    /* release the entry for the now closed pipe */

    free(cur);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    errno = ECHILD;
    return -1;
}
