#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include "luksFunction.h"

void  cleanup(pam_handle_t *pamh, void *src, int err)
{
  if (src == NULL)
    return;
  free(src);
}


/**
 * Store user login password for later use
 */
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags,int argc, const char **argv )
{
  int ret = -1;
  const char *user;
  char *password = NULL;

  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);
  if ((ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) != PAM_SUCCESS)
    return (ret);
  pam_set_data(pamh, "password_storage", strdup(password), &cleanup);
  return (PAM_SUCCESS);
}

/**
 * Open the container when session start
 */
PAM_EXTERN int pam_sm_open_session(pam_handle_t * pamh, int flags, int argc, const char **argv)
{
  const char *user;
  char *password = NULL;
  int ret = -1;
  int isCreate = 0;

  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);
  if ((ret = pam_get_data(pamh, "password_storage", (const void**)&password)) != PAM_SUCCESS)
    return (ret);
  if (password == NULL)
    return (ret);
  isCreate = createContainer(user, password);
  openContainer(user, password, isCreate);
  return (PAM_SUCCESS);
}

/**
 * Close the container on session close
 */
PAM_EXTERN int pam_sm_close_session(pam_handle_t * pamh, int flags, int argc, const char **argv)
{
  const char *user;
  int ret = -1;

  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);
  closeContainer(user);
  return (PAM_SUCCESS);
}

/**
 * Change the container encryptio key when user change password
 */
PAM_EXTERN int pam_sm_chauthtok(pam_handle_t * pamh, int flags, int argc, const char **argv)
{
  int ret= -1;
  char *user = NULL;
  char *password = NULL;
  char *oldpassword = NULL;

  if ((ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) != PAM_SUCCESS)
    return (ret);
  if ((ret = pam_get_item(pamh, PAM_OLDAUTHTOK, (const void **)&oldpassword)) != PAM_SUCCESS)
    return (ret);
  if ((password == NULL) || (oldpassword == NULL) || ((ret = pam_get_user(pamh, (const char **)&user, "Username: ")) != PAM_SUCCESS))
    return (ret);
  changePassword(oldpassword, password, user);
  pam_set_data(pamh, "password_storage", strdup(password), &cleanup);
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
