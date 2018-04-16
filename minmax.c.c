#include<stdio.h>
int a[20];
int count = 0;
int minmax(int i,int j,int *min,int *max)
{
	int mid,min1 = 100,max1 = 0;
	if(i == j)
	{
		count++;
		*min = *max = a[i];	
	}
	else if(i == (j - 1))
	{
		count++;
		if(a[i] < a[j])
		{	
			*max = a[j];
			*min = a[i];
		}
		else
		{
			*max = a[i];
			*min = a[j];
		}
	}
	else
	{
		
		mid = (i + j)/2;
		minmax(i,mid,min,max);
		minmax(mid+1,j,&min1,&max1);
		count++;
		count++;
		if(*max < max1)
		{
			*max = max1;
		}
		if(*min > min1)
		{
			*min = min1;
		}
	}
}
int main()
{
	int i,n;
	int min = 100;
	int max = 0;
	printf("Enter count\n");
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		printf("Enter element \n");
		scanf("%d",&a[i]);
	}
	minmax(0,n-1,&min,&max);
	printf("Min value is %d and Max value is %d\n",min,max);
	printf("Frequency count is %d\n",count);
}


