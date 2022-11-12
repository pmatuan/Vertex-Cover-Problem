#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *cases[] = {
  "gcc algo2.c -o algo2 -I cgen",
  "valgrind ./algo2 ../Data/demo.txt Data/demo.vc",
  "valgrind ./algo2 ../Data/CA-GrQc.txt Data/CA-GrQc.vc"
};

char *real_command(const char *cmd) {
  static char buff[1024];
  strcpy(buff, "/usr/bin/time -f \"\\tTime: %E real,\\tMemory: %M Kb\" ");
  strcat(buff, cmd);
  return buff;
}

int main() {
  int n = sizeof(cases)/sizeof(cases[0]);
  system(cases[0]);
  for (int i = 1; i < n; ++i) {
    const char *command = real_command(cases[i]);
    printf("case %d: %s\n", i , cases[i]);
    system(command);
    printf("\n\n");
  }
  return 0;
}