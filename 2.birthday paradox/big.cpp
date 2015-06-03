#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fill(int birthday[], int size)
{

	for (int i=0; i<size; i++)
	{
	 birthday[i] = rand() % 365+1;
	}
      return 0;
}

int main()
{
    int birthday[50];
	int trials = 100;
	int flag;
	double total;
	int same[50];
	// number of people from 2 to 50
	#pragma omp parallel for
	for (int i = 2; i < 50; i++)
{
  same[i] = 0;
 // do 100 trials:
for (int t = 0; t < trials; t++)
  {
   fill(birthday, i);
   flag = 0;
   // std::cout<<birthday[i];
   // compare all pairs (j,k):
   for (int j = 0; j < i - 1 && flag == 0; j++)
   {
     for (int k = j + 1; k < i && flag == 0; k++ )
    {
     if (birthday[k] == birthday[j])
      {
         same[i]++;
         flag = 1;
      }
    }
    }
   }
   
   total = same[i]/100.0;
   std::cout<<"Probability for "<<i<<"is"<<total<<std::endl;
}

}
	