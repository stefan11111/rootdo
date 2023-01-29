#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: %s [command]\n", argv[0]);
        return 0;
    }

    if (geteuid() != 0){
        printf("The rdo binary needs to be installed as SUID. \n");
	return 1;
    }

    if (setgid(0) < 0){
        printf("Could not setuid\n");
	return 1;
    }
    if (setuid(0) < 0){
        printf("Could not setgid\n");
	return 1;
    }

    putenv("HOME=/root");
    if(execvp(argv[1], argv + 1) == -1){
        printf("%s: command not found", argv[1]);
        return 1;
    }
    return 0;
}
