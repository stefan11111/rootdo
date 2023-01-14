#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>

#include "rdo.h"

#define PWD_MAX 200

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: %s [command]\n", argv[0]);
        return 0;
    }

    int ruid = getuid();

    if (setuid(0) < 0){
        printf("Could not setuid.\n");
	return -1;
    }
    if (setgid(0) < 0){
        printf("Could not setgid.\n");
	return -1;
    }

    struct passwd *user = getpwuid(ruid);

    if(strcmp(user->pw_name, allowed_user)){
	printf("You are not allowed user.\n");
	return 1;
    }

    if(require_password){
	char pass[PWD_MAX];
	printf("Enter the password: ");
	if(scanf("%s", pass) != 1){
	    printf("Failed to read password.\n");
	    return 0;
	}
	if(strcmp(pass, password)){
	    printf("Wrong password.\n");
	    return 1;
	}
    }

    putenv("HOME=/root");
    execvp(argv[1], argv + 1);
    return 0;
}
