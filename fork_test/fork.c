#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main() {
    printf("test_2020_09_09 \n");
    pid_t pid;
     
    int x;
    int idx = 0;
    x = 0;
    int* p_int=(int*)malloc(sizeof(int));
    *p_int=1024;
    int key=0;
    for(idx=0; idx<5; idx++) {
        pid = fork();
    }
     // 2^n process created
    if(pid > 0) {  // 부모 코드
        x = 1;
        key = 1;
        printf("parent PID : %ld,  x : %d , pid : %d\n",(long)getpid(), x, pid);
    }
    else if(pid == 0){  // 자식 코드
        x = 2;
        key = 1;
        printf("child PID : %ld,  x : %d, p_int : %d \n",(long)getpid(), x, *p_int);
    }
    else {  // fork 실패
        printf("fork Fail! \n");
        return -1;
    }
     
    return 0;
 
}
