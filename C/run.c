#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *cases[] = {
  "gcc algo1.c -o algo1 -I cgen && gcc algo2.c -o algo2 -I cgen",
  "./algo1 ../Data/demo.txt ../Data/demo.vc",
  "./algo2 ../Data/demo.txt ../Data/demo.vc",
  

  "./algo1 ../Data/CA-AstroPh.txt ../Data/CA-AstroPh.vc",
  "./algo2 ../Data/CA-AstroPh.txt ../Data/CA-AstroPh.vc",
  "./algo1 ../Data/CA-CondMat.txt ../Data/CA-CondMat.vc",
  "./algo2 ../Data/CA-CondMat.txt ../Data/CA-CondMat.vc",
  "./algo1 ../Data/CA-GrQc.txt ../Data/CA-GrQc.vc",
  "./algo2 ../Data/CA-GrQc.txt ../Data/CA-GrQc.vc",
  "./algo1 ../Data/CA-HepPh.txt ../Data/CA-HepPh.vc",
  "./algo2 ../Data/CA-HepPh.txt ../Data/CA-HepPh.vc",
  "./algo1 ../Data/CA-HepTh.txt ../Data/CA-HepTh.vc",
  "./algo2 ../Data/CA-HepTh.txt ../Data/CA-HepTh.vc",
  "./algo1 ../Data/Email-Enron.txt ../Data/Email-Enron.vc",
  "./algo2 ../Data/Email-Enron.txt ../Data/Email-Enron.vc",


  "./algo1 ../Data/roadNet-CA.txt ../Data/roadNet-CA.vc",
  "./algo2 ../Data/roadNet-CA.txt ../Data/roadNet-CA.vc",
  "./algo1 ../Data/roadNet-PA.txt ../Data/roadNet-PA.vc",
  "./algo2 ../Data/roadNet-PA.txt ../Data/roadNet-PA.vc",
  "./algo1 ../Data/roadNet-TX.txt ../Data/roadNet-TX.vc",
  "./algo2 ../Data/roadNet-TX.txt ../Data/roadNet-TX.vc"
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