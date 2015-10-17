#include <stdio.h>

int tixing(void)
{
     int i , j;
     for (i = 1; i <= 9; i++)
     {
	  for (j = 1; j <= i; j++)
	       printf ("  ");
	  for (j = 1; j <= 9; j++)
	       printf ("*");
	  printf ("\n");
     }
     return 0;
}
/** 
 * 
 * @file   jinzita.c
 * @author B.Qnyd <bb.qnyd@gmail.com>
 * @date   Tue Dec 14 20:00:45 2010
 *
 */
int jinzita(void)
{
     int i , j;
     for (i = 1; i <= 9; i++)
     {
	  for (j = 9; j >= 1; j--){
	       if (i>=j)printf ("*");
	       printf (" ");
	  }
	  printf("\n");
     }
     return 0;
}
/** 
 * @return char
 */
int char_jz(void){
     char let = 'F';
     char start,end;
     for (end = let; end >= 'A'; end--)
     {
	  for (start = let; start >= end; start--)
	       printf ("%c",start);
	  printf ("\n");
     }
}


int af_char(void){
     char let = 'A';
     char start,end;
     for (end = let; end < 'F'; end++)
     {
	  for (start = 'F'; start > let; start--){
	       if (end>=start)printf ("%c",start);
	       printf (" ");
	  }
	  printf ("\n");
     }
}

int square_cube(void){
     int lower, upper, index;
     int square, cube;
     printf("Enter starting integer: ");
     scanf("%d", &lower);
     printf("Enter ending integer: ");
     scanf("%d", &upper);
     printf("%5s %10s %15s\n", "num", "square", "cube");
     for (index = lower; index <= upper; index++)
     {
	  square = index * index;
	  cube = index * square;
	  printf("%5d %10d %15d\n", index, square, cube);
     }
}






#define SIZE 8
int m_size( void )
{
     int twopows[SIZE];
     int i;
     int value = 1;
/* 2 to the 0 */
     for (i = 0; i < SIZE; i++)
     {
	  twopows[i] = value;
	  value *= 2;
	  printf ("%d\n",twopows[i]);
     }
     i = 0;
     do
     {
	  printf ("%d ", twopows[i]);
	  i++;
     }
     while (i < SIZE);
     printf("\n");
     return 0;
}



int d_size(void)
{
     double arr[SIZE];
     double arr_cumul[SIZE];
     int i;
     printf("Enter %d numbers:\n", SIZE);
     for (i = 0; i < SIZE; i++)
     {
	  printf("value #%d: ", i + 1);
	  scanf("%lf", &arr[i]);
/* or scanf("%lf", arr + i);
 */
     }
     arr_cumul[0] = arr[0];
/* set first element */
     for (i = 1; i < SIZE; i++)
	  arr_cumul[i] = arr_cumul[i-1] + arr[i];
     for (i = 0; i <SIZE; i++)
	  printf("%8g", arr[i]);
     printf("\n");
     for (i = 0; i <SIZE; i++)
	  printf("%8g", arr_cumul[i]);
     printf("\n");
	  
return 0;
}

#define RATE_SIMP 0.10
#define RATE_COMP 0.05
#define INIT_AMT 100.0

int jisuan(void){
     double daphne = INIT_AMT;
     double deidre = INIT_AMT;
     int years = 0;
     while (deidre <= daphne)
     {
	  daphne += RATE_SIMP *INIT_AMT;
	  deidre += RATE_COMP *deidre;
	  ++years;
     }
     printf("Investment values after %d years:\n", years);
     printf("Daphne: $%.2f\n",daphne);
     printf("Deidre: $%.2f\n",deidre);
     return 0;

}

int main(int argc, char *argv[])
{
     // char_jz();
     //jinzita();
     //af_char();
     //square_cube();
     //m_size();
     //d_size();
     jisuan();
     return 0;
}

