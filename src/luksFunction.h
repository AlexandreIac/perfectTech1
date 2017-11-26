
#ifndef LUKSFUNCTION_H_
# define LUKSFUNCTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		openContainer(const char *user, const char *pass);
void		createContainer(const char *user, const char *pass);
void		changePassword(const char *pass, const char *newPass, const char *user);
void		closeContainer(const char *user, const char *pass);

#endif /*  !LUKSFUNCTION_H_ */
