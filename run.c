#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *cases[] = {
  "g++ algo1.cpp -o algo1 && g++ algo2.cpp -o algo2",
  "./algo1 demo.txt demo.vc",
  "./algo2 demo.txt demo.vc",
  "./algo1 roadNet-CA.txt roadNet-CA.vc",
  "./algo2 roadNet-CA.txt roadNet-CA.vc",
  "./algo1 roadNet-PA.txt roadNet-PA.vc",
  "./algo2 roadNet-PA.txt roadNet-PA.vc",
  "./algo1 roadNet-TX.txt roadNet-TX.vc",
  "./algo2 roadNet-TX.txt roadNet-TX.vc"
};

char *real_command(const char *cmd) {
  static char buff[1024];
  strcpy(buff, "/usr/bin/time -f \"\\tTime: %E real,\\tMemory: %M Kb\" ");
  strcat(buff, cmd);
  return buff;
}

int main() {
  int n = sizeof(cases)/sizeof(cases[0]);
  real_command(cases[0]);
  for (int i = 1; i < n; ++i) {
    const char *command = real_command(cases[i]);
    printf("case %d: %s\n", i , cases[i]);
    system(command);
    printf("\n\n");
  }
  return 0;
}