#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>




int main(void)
{
  DIR           *d;
  struct dirent *dir;
  d = opendir(".");
  struct stat buffer;
  int status;

  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      printf("File name : %s\n", dir->d_name);
      status = stat(dir->d_name, &buffer);

      printf("Serial no  : %ld\n", buffer.st_ino);
      printf("File size  : %ld bytes\n ", buffer.st_size);
      printf("Date  : %s \n\n ", ctime(&(buffer.st_ctime)));

    }


    closedir(d);
  }

  return(0);
}
