/*
** pam_sm_authenticate.c for Pamela in /home/alex/lib
** 
** Made by alex
** Login   <alexandre.iacona@epitech.eu>
** 
** Started on  Wed Nov 22 01:42:24 2017 alex
** Last update Wed Nov 22 09:13:48 2017 alex
*/

#include <stdio.h>
#include <unistd.h>
#include <security/pam_appl.h>

int pam_sm_acct_mgmt(pam_handle_t *pahm, int flags,
			 int argc, char **argv)
{
  printf("cela marche\n" );
  return (PAM_IGNORE);
}

int pam_sm_setcred(pam_handle_t *pahm, int flags,
			 int argc, char **argv)
{
  printf("cela marche\n" );
  return (PAM_IGNORE);
}

int pam_sm_authenticate(pam_handle_t *pahm, int flags,
			 int argc, char **argv)
{
  printf("cela marche\n" );
  return (PAM_IGNORE);
}

int pam_sm_open_session(pam_handle_t *pahm, int flags,
			 int argc, char **argv)
{
  printf("cela marche\n" );
  return (PAM_IGNORE);
}

int pam_sm_close_session(pam_handle_t *pahm, int flags,
			 int argc, char **argv)
{
  printf("cela marche\n" );
  return (PAM_IGNORE);
}

int pam_sm_chauthok(pam_handle_t *pahm, int flags,
			 int argc, char **argv)
{
  printf("cela marche\n" );
  return (PAM_IGNORE);
}
