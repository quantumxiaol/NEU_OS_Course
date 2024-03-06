// 进程的管道通信
// 编程实现进程的管道通信程序

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
    int i,r,p1,p2,p3,fd[2];
    //fp[2]是供进程使用的文件描述符数组，fp[1]用于写，fp[0]用于读

    char buf[50],s[50];
    pipe(fd);
    while((p1=fork())==-1);
    if(p1==0){
        lockf(fd[1],1,0);//对管道的锁定实现互斥
        sprintf(buf,"hello world from child p1!\n");
        printf("child process p1!\n");
        write(fd[1],buf,50);
        sleep(5);
        lockf(fd[1],0,0);
        exit(0);
        }
    else{
        while((p2=fork())==-1);
        if(p2==0){
            lockf(fd[1],1,0);
            sprintf(buf,"hello world from child p2!\n");
            printf("child process p2!\n");
            write(fd[1],buf,50);
            sleep(5);
            lockf(fd[1],0,0);
            exit(0);
            }
        else{
            while((p3=fork())==-1)
            if(p3==0){
                lockf(fd[1],1,0);
                sprintf(buf,"hello world from child p2!\n");
                printf("child process p2!\n");
                write(fd[1],buf,50);
                sleep(5);
                lockf(fd[1],0,0);
                exit(0);
            }
            else{
                wait(0);//控制父进程与子进程的同步
                if(r=read(fd[0],s,50)==-1)
                    printf("pipe read failed!\n");
                else
                    printf("%s\n",s);
                return 0;
            }
            wait(0);
            if(r=read(fd[0],s,50)==-1)
                printf("pipe read failed!\n");
            else
                printf("%s\n",s);
            return 0;
        }
        wait(0);
        if(r=read(fd[0],s,50)==-1)
            printf("pipe read failed!\n");
        else
            printf("%s\n",s);
        return 0;
   }
}


