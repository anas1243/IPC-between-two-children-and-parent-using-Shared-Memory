#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>


int main()

{
	const int SIZE = 4096;
	const char *name = "cyber sec";
	
	
	int shm_fd;
	
	pid_t pid,pid1,pid2;

	int status;
	int  n, size, i = 0; 
	int ray[n];
	float *data,*ptr,*ptr2;
	int max = ray[0];

	printf("Enter size of your Arrays : ");
	scanf("%d", &n);
int t;
	for(i = 0; i < n; i++)
		{
			printf("Enter Your Data : ");
			
			scanf("%d", &t);
			ray[i]=t;
			
		}
	//Create  Shared Memeory
    shm_fd = shm_open(name, O_RDWR | O_CREAT, 0666 );
	
//specify a certain length of your memory 			
    ftruncate(shm_fd, SIZE);
	
	//point to the first segment in your memory space 
    data =(float *) mmap(NULL, 2*sizeof(float), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, shm_fd, 0);

	
	


	pid1 = fork();

	if(pid1 < 0)
	{
		fprintf(stderr, "Fork Failed" );
		return 1; 
	}
	else if (pid1 == 0)//child process
	{
		printf("In Child Process # 1 \n");
		
		
		for(i=1;i<n;i++)
		{
			if(ray[i] > max)
				max = ray[i];
		}
//why we need this ptr instead of data ! Segmentation fault !!!!!!!!!
	ptr = data;
	*ptr = (float)max;
	}
	else
	{
		//sleep(2);
		pid2 = fork();
		if(pid2 < 0){
			fprintf(stderr, "Fork Failed" );
		}
		else if(pid2 == 0){
			int sum=0;
			float average;
			printf("In Child Process # 2 \n");

			for(i=0;i<n;i++){
				
				sum+=ray[i];}
			average = (float)sum/n;
			data++;
			*data = average;
			
		}
		else{
			int n =2;
			while(n>0){

			pid = wait(&status);
		printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
		n--;
				}
		printf("The max of the array is %.0f \n",*data);
		data++;
		printf("The average of the array is %.2f \n",*data);
		}
		
	}
	return 0;
}
