#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <shadow.h>
#include <termios.h>

#define PWD_MAX 200			/*max password length*/
#define ALLOWED_USER "stefan"		/*the allowed user, must always be a valid string*/
/*#define ALLOWED_GROUP ""*/		/*the allowed group, doesn't need to include ALLOWED_USER*/
					/*can be commented to build without support for groups*/
#define REQUIRE_PASSWORD		/*comment to not require password for the allowed user*/
#define ALLOW_ROOT			/*comment to not allow the root user to use rdo*/
#define HARDENED			/*clear the password in memory, with a performance hit*/
#define RDOEDIT				/*comment to build without support for rdoedit*/
