#include <stdio.h>
int main() 
{
double p;
int n;
int nop;
for (nop = 3; nop < 50; nop++) 
{
p = 1;
for (n = 1; n < nop; n++) {
p *= (365.0 - n) / 365.0;
}
printf("for %d nop, probability is %.4f\n", nop, 1 - p);
}
return 0;
}