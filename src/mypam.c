#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include "luksFunction.h"

void  cleanup(pam_handle_t *pamh, void *src, int err)
{
  int i;

  if (src == NULL)
    return;

  i = 0;
  while (((char *)src)[i] != '\0')
  {
    ((char *)src)[i] = '\0';
    i += 1;
  }

  free(src);
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags,int argc, const char **argv )
{
  int ret;
  const char *user;
  char *password;

  printf("################ GNA GNA ###############\n");
  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);

  printf("Hello %s\n", user);

  if ((ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) != PAM_SUCCESS)
    return (ret);

  pam_set_data(pamh, "password_storage", strdup(password), &cleanup);

  printf("################ GNA GNA ###############\n");
  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t * pamh, int flags, int argc, const char **argv)
{
  const char *user;
  char *password;
  int ret;

  printf("################ GNA GNA ###############\n");
  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);

  printf("Hi %s", user);

  if ((ret = pam_get_data(pamh, "password_storage", (const void**)&password)) != PAM_SUCCESS)
    return (ret);

  if (password == NULL)
    return (ret);

  createContainer(user, password);
  openContainer(user, password);

  printf("################ GNA GNA ###############\n");
  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t * pamh, int flags, int argc, const char **argv)
{
  const char *user;
  char *password;
  int ret;

  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);

  printf("Bye %s", user);

  if ((ret = pam_get_data(pamh, "password_storage", (const void**)&password)) != PAM_SUCCESS)
    return (ret);

  closeContainer(user, password);

  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_chauhtok(pam_handle_t * pamh, int flags, int argc, const char **argv)
{
  int ret;
  char *user;
  char *password;

	if ((ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) != PAM_SUCCESS)
		return (ret);
	if ((password == NULL) || ((ret = pam_get_user(pamh, (const char **)&user, "Username: ")) != PAM_SUCCESS))
    return (ret);


  //
  //                      ! ! !
  //
  // add a key to a container with cryptSetUp luksAddKey
  //

  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv )
{
	return (PAM_SUCCESS);
}
