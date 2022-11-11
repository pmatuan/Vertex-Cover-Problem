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
  "./algo2 roadNet-TX.txt roadNet-TX.vc",

  "./algo1 CA-AstroPh.txt CA-AstroPh.vc",
  "./algo2 CA-AstroPh.txt CA-AstroPh.vc",
  "./algo1 CA-CondMat.txt CA-CondMat.vc",
  "./algo2 CA-CondMat.txt CA-CondMat.vc",
  "./algo1 CA-GrQc.txt CA-GrQc.vc",
  "./algo2 CA-GrQc.txt CA-GrQc.vc",
  "./algo1 CA-HepPh.txt CA-HepPh.vc",
  "./algo2 CA-HepPh.txt CA-HepPh.vc",
  "./algo1 CA-HepTh.txt CA-HepTh.vc",
  "./algo2 CA-HepTh.txt CA-HepTh.vc",
  "./algo1 Email-Enron.txt Email-Enron.vc",
  "./algo2 Email-Enron.txt Email-Enron.vc",
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