#include "rdo.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: %s [command]\n", argv[0]);
        return 0;
    }

    int ruid = getuid();

    if(!ruid){
	putenv("HOME=/root");
	execvp(argv[1], argv + 1);
	return 0;
    }

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
	printf("You are not the allowed user.\n");
	return 1;
    }

    if(!require_password){
	putenv("HOME=/root");
	execvp(argv[1], argv + 1);
	return 0;
    }

    char pass[PWD_MAX];
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(1, 0, &term);
    term.c_lflag |= ECHO;
    if (write(1, "Enter the password: ", 20) < 0)
	tcsetattr(1, 0, &term);
    if(scanf("%s", pass) != 1){
	printf("Error reading password.\n");
	tcsetattr(1, 0, &term);
	return 0;
    }
    tcsetattr(1, 0, &term);

    struct spwd* shadow = getspnam(user->pw_name);

    if (!shadow || !shadow->sp_pwdp){
        printf("Could not get shadow entry.\n");
	return 1;
    }

    char *hashed = NULL;
    hashed = crypt(pass, shadow->sp_pwdp);
    if(!hashed){
	printf("Could not hash password, does your user have a password?");
	return 1;
    }

    if(strcmp(hashed, shadow->sp_pwdp)){
	printf("Wrong password.\n");
	return 1;
    }

    putenv("HOME=/root");
    execvp(argv[1], argv + 1);
    return 0;
}
