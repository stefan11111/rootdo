#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <shadow.h>
#include <termios.h>

#define PWD_MAX 200

char *allowed_user = "stefan";		/*the allowed user*/
int require_password = 0;		/*require password for the allowed user*/
					/*1 is true, 0 is false*/
int allow_root = 1;			/*allow the root user to use rdo*/
					/*1 is true, 0 is false*/
