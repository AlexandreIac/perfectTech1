#ifndef LUKSFUNCTION_H_
# define LUKSFUNCTION_H_

void		openContainer(const char *user, const char *pass, int create);
int		createContainer(const char *user, const char *pass);
void		changePassword(const char *pass, const char *newPass, const char *user);
void		closeContainer(const char *user);

#endif /*  !LUKSFUNCTION_H_ */
