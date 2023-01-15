#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <shadow.h>

#define PWD_MAX 200

char *allowed_user = "stefan";		/*the allowed user*/
int require_password = 1;		/*require password for the allowed user*/
					/*1 is true, 0 is false*/
