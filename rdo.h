#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <shadow.h>
#include <termios.h>

#define PWD_MAX 200
#define ALLOWED_USER "stefan"		/*the allowed user*/
#define REQUIRE_PASSWORD 0		/*require password for the allowed user*/
					/*1 is true, 0 is false*/
#define ALLOW_ROOT 1			/*allow the root user to use rdo*/
					/*1 is true, 0 is false*/
