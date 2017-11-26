
#ifndef LUKSFUNCTION_H_
# define LUKSFUNCTION_H_

void		openContainer(const char *user, const char *pass);
void		createContainer(const char *user, const char *pass);
void		changePassword(const char *pass, const char *newPass, const char *user);

#endif /*  !LUKSFUNCTION_H_ */
