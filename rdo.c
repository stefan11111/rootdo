#include "rdo.h"

static int run_program(char **program) {
    if (geteuid() != 0) {
        printf("The rdo binary needs to be installed as SUID. \n");
        return 1;
    }
    if (setgid(0) < 0) {
        printf("Could not setuid.\n");
        return -1;
    }
    if (setuid(0) < 0) {
        printf("Could not setgid.\n");
        return -1;
    }
    putenv("HOME=/root");
    if (execvp(*program, program) == -1) {
        printf("%s: command not found\n", *program);
        return -1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: rdo [command]\n");
        return 0;
    }

    if (!strcmp(argv[1], "-e")) {
        if(argc == 2) {
            printf("Usage: rdo -e [files]\n");
            return 0;
        }
        *(argv + 1) = "rdoedit";
        execvp("rdoedit", argv + 1);
        return 0;
    }

    int ruid = getuid();

    if (!ruid && ALLOW_ROOT) {
	putenv("HOME=/root");
	execvp(argv[1], argv + 1);
	return 0;
    }

    struct passwd *user = getpwuid(ruid);

    if (strcmp(user->pw_name, ALLOWED_USER)) {
	printf("You are not the allowed user.\n");
	return 1;
    }

    if (!REQUIRE_PASSWORD) {
	return run_program(argv + 1);
    }

    char pass[PWD_MAX + 1];
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(1, 0, &term);
    term.c_lflag |= ECHO;
    if (write(1, "Enter the password: ", 20) < 0) {
	tcsetattr(1, 0, &term);
    }
    if (scanf("%200s", pass) != 1) {
	printf("Error reading password.\n");
	tcsetattr(1, 0, &term);
	return 0;
    }
    tcsetattr(1, 0, &term);
    printf("\n");

    struct spwd* shadow = getspnam(user->pw_name);

    if (!shadow || !shadow->sp_pwdp) {
        printf("Could not get shadow entry.\n");
	return 1;
    }

    char *hashed = NULL;
    hashed = crypt(pass, shadow->sp_pwdp);
    if (!hashed) {
	printf("Could not hash password, does your user have a password?");
	return 1;
    }

    if (strcmp(hashed, shadow->sp_pwdp)) {
	printf("Wrong password.\n");
	return 1;
    }

    return run_program(argv + 1);
}
