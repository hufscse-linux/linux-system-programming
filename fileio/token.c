#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 5
#define STRING_SIZE 1024

int main(int argc, char** argv) {
  int in_fd, out_fd;
  int pos = 0;
  int n;
  char buffer[BUFFER_SIZE];
  char string[STRING_SIZE];
  
  char* pch;

  in_fd = open("in.txt", O_RDONLY);
  out_fd = open("out.txt", O_WRONLY | O_CREAT, 0666);
  
  while(-1 != (n = read(in_fd, buffer, BUFFER_SIZE))) {
    if(n == 0) break;
    strncpy(&string[pos], buffer, n);
    pos += n;
  }

  pch = strtok(string, "_");
  while(NULL != pch) {
    printf("%s\n", pch);
    write(out_fd, pch, strlen(pch));
    write(out_fd, "\n", 1);
    pch = strtok(NULL, "_");
  }

  close(in_fd);
  close(out_fd);
  return 0;
}
