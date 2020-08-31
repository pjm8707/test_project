#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signo);

static int stop_flag=0;

int main(int argc, char **argv)
{
  int i = 0;
signal(SIGTERM, (void *)sig_handler);
  while(1)
  {
    printf("%d\n", i);
    i++;
	sleep(1);
	if(stop_flag == 1) {
		printf("stop flag enabled \n");
		break;
	}
  }
}

void sig_handler(int signo)
{
 printf("Received PROCESS_STOP : %d \n", signo);
stop_flag=1;
}
