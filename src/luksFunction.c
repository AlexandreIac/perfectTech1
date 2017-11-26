/*
** luksFunction.c for pamela in /home/alex/pamela/src
** 
** Made by alex
** Login   <alexandre.iacona@epitech.eu>
** 
** Started on  Wed Nov 22 13:37:53 2017 alex
** Last update Wed Nov 22 18:51:04 2017 alex
*/

#include <stdio.h>
#include <unistd.h>

void		changePassword(const char *pass, const char *newPass,
			       const char *user)
{
  char *buffer = null;
  
  asprintf(buffer, "echo '%s\n%s\n' | sudo cryptsetup luksAddKey -q /home/%s/.container", pass, newPass, user);
  system(buffer);
  free(buffer);
  asprintf(buffer, " echo '%s' | sudo cryptsetup luksRemoveKey /home/%s/.container", pass, user);
  system(buffer);
  free(buffer);
}

void		createContainer(const char *user, const char *pass))
{
  char *buffer = NULL;
  char *path = NULL;

  // look if the container already exist
  asprintf(path, "/home/%s/.container", user);
  if (acces(path, F_OK) != -1)
    return;
  // if not, create it
  asprintf(buffer, "dd if=/dev/zero bs=1M count=10 of=%s; chown %s %s ;chmod u+rw,g-rwx,o-rwx %s", path, user, path, path);
  system(buffer);
  free(buffer);
  asprintf(buffer, "echo 'YES' | echo '%s' | echo '%s' | cryptsetup luksFormat %s", pass, pass, path);
  system(buffer);
  free(buffer);
  free(path);
}

void		openContainer(const char *user, const char *pass)
{
  // open the cipher container
  char *buffer = null;
  
  asprintf(buffer, "echo '%s' | sudo cryptsetup luksOpen /home/%s/.container %s-data", pass, user, user);
  system(buffer);
  free(buffer);
  asprintf(buffer, "sudo mkdir /home/%s/secure_data-rw.; sudo mount /dev/mapper/%s-data /home/%s/secure_data-rw; chown %s /home/%s/secure_data-rw; chmod u+rw,g-rwx,o-rwx /home/%s/secure_data-rw", user, user, user, user, user, user);
  system(buffer);
  free(buffer);
}


void		closeContainer(const char *user, const char *pass)
{
  // close the cipher container
  char *buffer = null;
    
  asprintf(buffer, "sudo umount /home/%s/secure_data-rw; sudo cryptsetup luksClose %s-data; rm -rf /home/%s/secure_data-rw", user, user, user);
  system(buffer);
  free(buffer);
}
