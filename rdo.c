#include "rdo.h"

static int run_program(char **program, struct passwd *user) {
    uid_t uid = 0;
    gid_t gid = 0;
    if (user) {
        uid = user->pw_uid;
        gid = user->pw_gid;
    }
    if (geteuid() != 0) {
        printf("The rdo binary needs to be installed as SUID. \n");
        return 1;
    }
    if (setgid(gid) < 0) {
        printf("Could not setgid.\n");
        return -1;
    }
    if (setuid(uid) < 0) {
        printf("Could not setuid.\n");
        return -1;
    }
    putenv("HOME=/root");
    if (execvp(*program, program) == -1) {
        printf("%s: command not found\n", *program);
        return -1;
    }
    return 0;
}

static void* erase_from_memory(void *s, size_t n)
{
    volatile unsigned char *p = s;
    while(n--) {
        *p++ = 0;
    }
    return s;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: %s [command]\n", argv[0]);
        return 0;
    }
#ifdef RDOEDIT
    if (!strcmp(argv[1], "-e")) {
        if(argc == 2) {
            printf("Usage: %s -e [files]\n", argv[0]);
            return 0;
        }
        *(argv + 1) = "rdoedit";
        if (setgid(getgid()) < 0) {
            printf("Could not setgid.\n");
            return -1;
        }
        if (setuid(getuid()) < 0) {
            printf("Could not setuid.\n");
            return -1;
        }
        if (execvp("rdoedit", argv + 1) == -1) {
            printf("rdoedit is not installed\n");
        }
        return 0;
    }
#endif
    int ruid = getuid();
    if (!ruid) {
#ifndef ALLOW_ROOT
        printf("You are not the allowed user.\n");
        return 1;
#else
        putenv("HOME=/root");
        execvp(argv[1], argv + 1);
        return 0;
#endif
    }
    struct passwd *user = getpwuid(ruid);

    if (!user) {
        printf("could not get UID\n");
        return 0;
    }
#ifdef ALLOWED_GROUP
    struct group *grp = getgrnam(ALLOWED_GROUP);
    if (!grp) {
        if (strcmp(user->pw_name, ALLOWED_USER)) {
	    printf("You are not the allowed user.\n");
	    return 1;
        }
    }
    else {
        char **ptr = grp->gr_mem;
        char ok = 0;
        while(*ptr) {
            if (!strcmp(*(ptr++), user->pw_name)) {
                ok = 1;
                break;
            }
        }
        if (strcmp(user->pw_name, ALLOWED_USER) && !ok) {
            printf("You are not the allowed user.\n");
            return 1;
        }
    }
#else
    if (strcmp(user->pw_name, ALLOWED_USER)) {
        printf("You are not the allowed user.\n");
        return 1;
    }
#endif
#ifdef REQUIRE_PASSWORD
    char pass[PWD_MAX + 1];
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(1, 0, &term);
    term.c_lflag |= ECHO;
    if (write(1, "Enter the password: ", 20) < 0) {
        tcsetattr(1, 0, &term);
    }
    int n = read(0, pass, PWD_MAX);
    if (n <= 0) {
#ifdef HARDENED
        erase_from_memory(pass, sizeof(pass));
#endif
        printf("Error reading password.\n");
        tcsetattr(1, 0, &term);
        return 0;
    }
    tcsetattr(1, 0, &term);
    printf("\n");
    pass[n - 1] = '\0';
    struct spwd* shadow = getspnam(user->pw_name);

    if (!shadow || !shadow->sp_pwdp) {
        printf("Could not get shadow entry.\n");
        return 1;
    }

    char *hashed = crypt(pass, shadow->sp_pwdp);
#ifdef HARDENED
    erase_from_memory(pass, sizeof(pass));
#endif
    if (!hashed) {
        printf("Could not hash password, does your user have a password?");
        return 1;
    }
    if (strcmp(hashed, shadow->sp_pwdp)) {
        printf("Wrong password.\n");
        return 1;
    }
#endif
    if (!strcmp(argv[1], "-u")) {
        if (argc < 4) {
            printf("Usage: %s [-u] [user] [command]\n", argv[0]);
            return 0;
        }
        run_program(argv + 3, getpwnam(argv[2]));
        return 0;
    }
    return run_program(argv + 1, NULL);
}
