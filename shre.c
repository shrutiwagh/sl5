#include<stdio.h>
#include<stdlib.h>
#define max 100
int count=0;

int place(int k,int i,int x[])
{
  int j;
  for(j=1;j<=k-1;j++)
  {
    if((x[j]==i) || (abs(x[j]-i)==abs(j-k)))
      return 0;
  }
  return 1;
}

void nqueens(int k,int n,int x[])
{
 int i,l=0;
 for(i=1;i<=n;i++)
 {
   if(place(k,i,x))
   {
     x[k]=i;
     if(k==n)
     {
      count++;
      printf("\n\n Solution %d:- ",count);
      int m;
      for(m=1;m<=n;m++)
      {
       printf("\n");
       for(l=1; l<=n;l++)
       {
        if(l==x[m])
           printf(" q ");
        else
           printf(" 0 ");
       }
      }
     }
    else
     nqueens(k+1,n,x);
   }

  }
}

int main()
{
 int x[max];
 int n,i;
 printf("\nEnter the number of queens");
 scanf("%d",&n);
 for(i=1;i<=n;i++)
   x[i]=0;
 nqueens(1,n,x);
 
}

