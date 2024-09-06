#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: %s [command]\n", argv[0]);
        return 0;
    }

    if (!strcmp(argv[1], "-e")) {
        if(argc == 2) {
            printf("Usage: %s -e [files]\n", argv[0]);
            return 0;
        }
        *(argv + 1) = "rdoedit";
        if (execvp("rdoedit", argv + 1) == -1) {
            fprintf(stderr, "rdoedit is not installed\n");
        }
        return 0;
    }

    if (geteuid() != 0) {
        fprintf(stderr, "The rdo binary needs to be installed as SUID. \n");
	return 1;
    }

    if (setgid(0) < 0) {
        fprintf(stderr, "Could not setuid\n");
	return 1;
    }

    if (setuid(0) < 0) {
        fprintf(stderr, "Could not setgid\n");
	return 1;
    }

    putenv("HOME=/root");
    if (execvp(argv[1], argv + 1) == -1) {
        fprintf(stderr, "%s: command not found\n", argv[1]);
        return 1;
    }
    return 0;
}
