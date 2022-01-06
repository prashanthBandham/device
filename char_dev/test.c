#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
	int fd;
	char option;

	printf("Welcome to demo of charecter driver ,,\n");

	fd = open("/dev/my_dev",O_RDWR);
	if(fd<0)
	{
		printf("cannot open device file \n");
		return 0;
	}
	while(1)
	{
		printf("****please enter your option****\n");
		printf("      1.write         \n");
		printf("      2.read          \n");
		printf("      3.exit          \n");
		scanf(" %c", &option);
		printf(" your oprtion = %c\n", option);

		switch(option)
		{
			case 1 :
				printf("enter the string into the driver:\n");
				scanf(" %[^\t\n]s",write_buf);
				printf("data written...\n");
				write,write_buf,strlen(write_buf)+1);
				printf("done  \n");
				break;
				

			case2 2 :
				printf("data is reading  ");
			        read(fd,read_buf,1024);
				printf("done = %s\n\n",read_buf);
				break;
			case 3 :
				close(fd);
				exit(1);
				break;
			default:
				printf("enter valid option = %c\n",option);
				break;
		}
	}
	close(fd);
}



