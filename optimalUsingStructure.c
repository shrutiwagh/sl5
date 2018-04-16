/*
	Name : Ayush Tripathi
	Roll : 3913
	Asg. : 2 (Jobs on tapes using structures with asc. dsc. check)
*/
#include <stdio.h>
#include <string.h>
#define MAX 100

void split(int, int);
void merge(int, int, int);
int checkSequence(int);

struct job
{
	int sizeOfJob;
	char nameOfJob[10];
}jo[100], tape[10][100];

int main()
{
	int jobs, tapes, check;
	int i, j, next_tape=0, tape_siz[10];
	printf("Enter number of tapes : ");
	scanf("%d", &tapes);
	printf("Enter number of jobs : ");
	scanf("%d", &jobs);
	for(i=0; i<jobs; i++)
	{
		printf("Enter name of job : ");
		scanf("%s", jo[i].nameOfJob);
		printf("Enter size of job %s : ", jo[i].nameOfJob);
		scanf("%d", &(jo[i].sizeOfJob));
	}
	check = checkSequence(jobs);
	if(check==0) {
		split(0, jobs-1);
		check=1;
	}
	printf("OUTPUT ARRAY : ");
	for(i=0 ; i<jobs ; i++)
		printf("{%s : %d}   ", jo[i].nameOfJob, jo[i].sizeOfJob);
	printf("\n");
	for(i=0; i<tapes; i++)
	{
		tape[i][0].sizeOfJob=0;
		tape_siz[i]=0;
	}
	if(check==1)	// => ascending
	{
		for(i=1; i<=jobs; i++)
		{	
			//j=0;
			//while(j < tapes)
			{
				if(tape_siz[next_tape]+jo[i-1].sizeOfJob <= MAX)
				{
					tape[next_tape][0].sizeOfJob+=1;	// storing number of jobs on that tape..used when jobs on tapes are displayed
					tape[next_tape][(i-1)/tapes+1].sizeOfJob=jo[i-1].sizeOfJob;
					strcpy(tape[next_tape][(i-1)/tapes+1].nameOfJob, jo[i-1].nameOfJob);
					tape_siz[next_tape]+=jo[i-1].sizeOfJob;
					next_tape=(next_tape+1) % tapes;
					//break;
				}
				else
					printf("Job {%s : %d} could not be added.\n", jo[i-1].nameOfJob, jo[i-1].sizeOfJob);
				//next_tape=(next_tape+1) % tapes;
				//j++;
			}
		}
	}
	else	// => check == 2 ,i.e. descending
	{
		for(i=jobs, j=1; i>=1; i--, j++)
		{	
			//j=1;
			//while(j < tapes)
			{
				if(tape_siz[next_tape]+jo[i-1].sizeOfJob <= MAX)
				{
					tape[next_tape][0].sizeOfJob+=1;
					tape[next_tape][(j-1)/tapes+1].sizeOfJob=jo[i-1].sizeOfJob;
					strcpy(tape[next_tape][(j-1)/tapes+1].nameOfJob, jo[i-1].nameOfJob);
					tape_siz[next_tape]+=jo[i-1].sizeOfJob;
					next_tape=(next_tape+1) % tapes;
					//break;
				}
				else
					printf("Job {%s : %d} could not be added.\n", jo[i-1].nameOfJob, jo[i-1].sizeOfJob);
				//next_tape=(next_tape+1) % tapes;
				//j++;
			}
		}
	}
	next_tape=0;
	while(next_tape<tapes)
	{
		i=1;
		j=tape[next_tape][0].sizeOfJob;
		printf("Tape %d (size : %d) :", next_tape, tape_siz[next_tape]);
		while(i<=j)
		{
			printf("{%d : %s}\t", tape[next_tape][i].sizeOfJob, tape[next_tape][i].nameOfJob);
			i++;
		}
		printf("\n");
		next_tape++;
	}
	return 0;
}

void split(int start, int end)
{
	int split_point = (start+end)/2, i;
	//printf("%d  %d  %d\n", start, split_point, end);
	if(start == split_point && start == end)
		return;//merge(arr, start, split_point, end); ---->> Don't do this..
	split(start, split_point);
	split(split_point+1, end);
	/*printf("The array now is: ");
	for(i=start ; i<=end ; i++)
		printf("%d  ", arr[i]);
	printf("\n");*/
	merge(start, split_point, end);
}

void merge(int start, int split_point, int end)
{
	int i, j, k, boundary1, boundary2, cnt=0;
	struct job temp[100];
	i = start; j = split_point+1;
	boundary1=jo[split_point].sizeOfJob; boundary2=jo[end].sizeOfJob;
	do
	{
		if(jo[i].sizeOfJob<=jo[j].sizeOfJob)
		{
			i++;
			if(i==j || jo[i].sizeOfJob>boundary1)
				break;
			continue;
		}
		while(j<=end && jo[i].sizeOfJob>jo[j].sizeOfJob)
		{
			temp[cnt++].sizeOfJob=jo[j].sizeOfJob;
			strcpy(temp[cnt-1].nameOfJob, jo[j].nameOfJob);
			j++;
		}
		k=1;
		while(k<=(j-i-cnt))
		{
			jo[j-k].sizeOfJob=jo[j-k-cnt].sizeOfJob;
			strcpy(jo[j-k].nameOfJob, jo[j-k-cnt].nameOfJob);
			k++;
		}
		k=0;
		while(cnt!=0)
		{
			jo[i++].sizeOfJob = temp[k].sizeOfJob;
			strcpy(jo[i-1].nameOfJob, temp[k].nameOfJob);
			k++; cnt--;
		}
	}while(i!=end && i!=j && j<=end);
}

int checkSequence(int jobs)
{
	int i;
	if(jobs==2)
	{
		if(jo[1].sizeOfJob >= jo[0].sizeOfJob)	// ascending
			return 1;
		else
			return 2;	// descending
	}
	for(i=0 ; i<jobs-1 ; i++) {
		if(jo[i].sizeOfJob > jo[i+1].sizeOfJob) break;	// => ascending
	}
	if(i==jobs-1)
		return 1;
	for(i=0 ; i<jobs-1 ; i++) {
		if(jo[i].sizeOfJob < jo[i+1].sizeOfJob) break;	// => descending
	}
	if(i==jobs-1)
		return 2;
	return 0;
}