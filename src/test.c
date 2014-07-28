#include <stdio.h>
#include <popen-noshell.h>

#define LSIZE 2048

int main(int argc, char* argv[]) {
    
    char *p[] = {"echo", "pokemon", NULL};
    char buffer[LSIZE] = {0};
    FILE *fp = popen_noshell(p, "r");

    while (fgets(buffer, LSIZE, fp)) {
        printf("%s", buffer);
    }

    if (ferror(fp)) {
       printf("omg error");
    }

    pclose_noshell(fp);

    return 0;
}
