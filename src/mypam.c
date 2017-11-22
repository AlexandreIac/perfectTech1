#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

void		changePassword(const char *pass, const char *newPass,
			       const char *user)
{
  char *buffer = NULL;
   
  asprintf(&buffer, "echo '%s\n%s\n' | sudo cryptsetup luksAddKey -q /home/%s/.container", pass, newPass, user);
  system(buffer);
  free(buffer);
  asprintf(&buffer, " echo '%s' | sudo cryptsetup luksRemoveKey /home/%s/.container", pass, user);
  system(buffer);
  free(buffer);
}

int		createContainer(const char *user, const char *pass)
{
  char *buffer = NULL;
  char *path = NULL;

  // look if the container already exist
  asprintf(&path, "/home/%s/.container", user);
  if (access(path, F_OK) != -1)
    return (1);
  // if not, create it
  asprintf(&buffer, "dd if=/dev/zero bs=1M count=10 of=%s; chown %s %s ;chmod u+rw,g-rwx,o-rwx %s", path, user, path, path);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "echo 'YES' | echo '%s' | echo '%s' | sudo cryptsetup luksFormat %s", pass, pass, path);
  system(buffer);
  free(buffer);
  free(path);
  return (0);
}

void		openContainer(const char *user, const char *pass, const int isCreate)
{
  // open the cipher container
  char *buffer = NULL;
  char *path = NULL;

  asprintf(&path, "/home/%s/.container", user);
  asprintf(&buffer, "echo \"%s\" | sudo cryptsetup luksOpen %s %s-data", pass, path, user);
  system(buffer);
  free(buffer);
  if (isCreate == 0)
    {
      asprintf(&buffer, "sudo mkfs.ext4 /dev/mapper/%s-data", user);
      system(buffer);
      free(buffer);
    }
  asprintf(&buffer, "mkdir /home/%s/secure_data-rw; sudo mount /dev/mapper/%s-data /home/%s/secure_data-rw; sudo chown -R %s /home/%s/secure_data-rw; sudo chmod u+rw,g-rwx,o-rwx /home/%s/secure_data-rw", user, user, user, user, user, user);
  system(buffer);
  free(buffer);
  free(path);
}


void		closeContainer(const char *user, const char *pass)
{
  // close the cipher container
  char *buffer = NULL;
    
  asprintf(&buffer, "sudo umount /home/%s/secure_data-rw; sudo cryptsetup luksClose %s-data; rm -rf /home/%s/secure_data-rw", user, user, user);
  system(buffer);
  free(buffer);
}

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

  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);

  printf("Hello %s\n", user);

  if ((ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) != PAM_SUCCESS)
    return (ret);

  pam_set_data(pamh, "password_storage", strdup(password), &cleanup);

  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t * pamh, int flags, int argc, const char **argv)
{
  const char *user;
  char *password;
  int ret;
  int isCreate = 0;

  if ((ret = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
    return (ret);

  printf("Hi %s", user);

  if ((ret = pam_get_data(pamh, "password_storage", (const void**)&password)) != PAM_SUCCESS)
    return (ret);

  if (password == NULL)
    return (ret);

  isCreate = createContainer(user, password);
  openContainer(user, password, isCreate);

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
  char *oldpassword;

  if ((ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) != PAM_SUCCESS)
    return (ret);
  if ((ret = pam_get_item(pamh, PAM_OLDAUTHTOK, (const void **)&oldpassword)) != PAM_SUCCESS)
    return (ret);
  if ((password == NULL) || ((ret = pam_get_user(pamh, (const char **)&user, "Username: ")) != PAM_SUCCESS))
    return (ret);


  changePassword(oldpassword, password, user);

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
