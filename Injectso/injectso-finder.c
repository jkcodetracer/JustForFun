/**
 * \file injectso.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月27日星期一21:49:40
 */
/*
* injectso-finder v0.0.1 (2004/12/21)
* written by grip2 <gript2@hotmail.com>
*/
#include <stdlib.h>
#include <stdio.h>
#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "gelf.h"
#include "gptrace.h"

extern void *memmem (const void *haystack, size_t haystacklen,
					 const void *needle, size_t needlelen);
static void usage (void);
static char *get_file_by_pid (pid_t pid);

int
main (int argc, char *argv[])
{
  pid_t pid;
  char *pchar;
  char *filename;

  printf ("injectso finder v0.0.1 written by grip2 <gript2@hotmail.com>\n");

  if (argc != 2)
	usage ();

  pid = strtol (argv[1], &pchar, 10);
  if (*pchar != '\0')
	usage ();

/* Runtime process */
  ptrace_attach (pid);
  print_sharelib_runtime (pid);
  ptrace_detach (pid);

/* Binary file */
  if ((filename = get_file_by_pid (pid)) != NULL)
	{
	  print_sharelib (filename);
	}
  else
	{
	  fprintf (stderr, "[** ALERT] Can't locate binary file\n");
	}
  free (filename);

  return 0;
}

void
usage (void)
{
  fprintf (stderr, "Usage: ./injectso-finder pid\n");
  exit (1);
}

char *
get_file_by_pid (pid_t pid)
{
  int fd = -1;
  char file[256];
  char *path;
  char environ[32], cmdline[32];
  char buff[4096];
  char *filename;
  int ret;

  snprintf (environ, sizeof (environ), "/proc/%d/environ", pid);
  snprintf (cmdline, sizeof (cmdline), "/proc/%d/cmdline", pid);

/* Get file */
  fd = open (cmdline, O_RDONLY);
  if (fd == -1)
	{
	  perror (cmdline);
	  goto err;
	}

  ret = read (fd, file, sizeof (file) - 1);
  if (ret == -1)
	{
	  perror (cmdline);
	  goto err;
	}
  file[ret] = '\0';
  close (fd);

/* Get path */
  fd = open (environ, O_RDONLY);
  if (fd == -1)
	{
	  perror (environ);
	  goto err;
	}

  ret = read (fd, buff, sizeof (buff) - 1);
  if (ret == -1)
	{
	  perror (environ);
	  goto err;
	}
  buff[ret] = '\0';
  close (fd);

  path = (char *) memmem (buff, ret, "PWD=", 4);
  if (path == NULL)
	{
	  goto err;
	}
  path += 4;

  filename = (char *) malloc (strlen (path) + strlen (file) + 2);
  if (!filename)
	goto err;

  sprintf (filename, "%s/%s", path, file);
  return filename;
err:
  if (fd != -1)
	close (fd);
  return NULL;
}
