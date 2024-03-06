#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<error.h>
#include<wait.h>
#include<unistd.h>
#include<time.h>
// 进程分配的最大内存页面数
#define frame_num 5
// 总的页面访问次数为
#define total_instruction 12

struct one_frame {
int page_no;    //页面号
int flag;
};
// 访问序列
int Access_series[total_instruction];
// 缺页次数
int diseffectF = 0;
int diseffectL = 0;
//进程分配页面使用情况
struct one_frame M_Frame[frame_num];

int FIFO(int Access_series[total_instruction]){
        int flagF = 0;
        printf("FIFO:\n");
        int framenow=0;       //现在已经分配的物理页面数
        int readframe;       //读取的页面号
        float r;
        for (int i = 0; i<total_instruction; i++){
            for (int j = 0; j<total_instruction; j++)
                printf("%d ", Access_series[j]);
            printf("\n");
            readframe = Access_series[i];	//读入访问页面号
            printf("read the frame %d\n",readframe);
            //查找该页面是否已分配
            for (int j=0; j<framenow; j++){
                if (readframe != M_Frame[j].page_no)
                    continue;
                else if(readframe == M_Frame[j].page_no){
                    printf("targeted!\n");    //命中
                    printf("The memory:\n");
                    for (int k = 0; k<framenow; k++)	//显示当前分配页面使用情况
                        printf("%d ", M_Frame[k].page_no);
                    printf("\n\n");
                    flagF = 1;
                    break;
                }
            }

            if (flagF == 0){
                diseffectF++;	//出现缺页次数加1
                //还有剩余的内存可分配
                if (framenow < frame_num){
                    M_Frame[framenow].page_no = readframe;	//为该页面分配内存空间
                    M_Frame[framenow].flag = 1;
                    framenow++;
                    printf("Diseffect %d times, caused by frame %d\n", diseffectF,readframe);
                    printf("The memory:\n");
                    for (int j = 0; j<framenow; j++)
                        printf("%d ", M_Frame[j].page_no);
                    printf("\n\n");
                }
                //分配物理页面数已满
                else{
                    printf("The memory is full, frame %d out\n", M_Frame[0].page_no);    //淘汰最早进入的页面
                    for (int j =1; j<frame_num; j++)       //后面的页面一次向前移动一位
                        M_Frame[j-1]=M_Frame[j];
                    M_Frame[frame_num-1].page_no = readframe;	//让读到的页面号分配到最后
                    printf("Diseffect %d times, caused by frame %d\n", diseffectF,readframe);
                    printf("The memory:\n");
                    for (int j = 0; j<framenow; j++)
                        printf("%d ", M_Frame[j].page_no);
                    printf("\n\n");
                }
            }
            flagF = 0;
        }
        r = diseffectF / (total_instruction +0.0);	//计算缺页率
        printf("FIFO: diseffect rate  %f\n", r);
        printf("FIFO: hit rate  %f\n\n", 1-r);
        return 0;
        
}
int LRU(int Access_series[total_instruction]){
        int framenow=0;       //现在已经分配的物理页面数
        int readframe;       //读取的页面号
        int flagL = 0;
        float r;
        printf("LRU:\n");
        for (int i=0; i<total_instruction; i++){
            for (int j=0; j<total_instruction; j++)
                printf("%d ", Access_series[j]);
            printf("\n");
            readframe = Access_series[i];	//读入访问页面号
            printf("read the frame %d\n",readframe);

            for (int j=0; j<framenow; j++){
                if (readframe!= M_Frame[j].page_no)	//查找该页面是否已分配
                    continue;
                else if(readframe == M_Frame[j].page_no){
                    printf("targeted!\n");    //命中
                    for (int k = j+1; k<framenow; k++)	//进行移位，让最新被访问的在最后面
                        M_Frame[k-1].page_no = M_Frame[k].page_no;
                    M_Frame[framenow - 1].page_no = readframe;

                    printf("The memory:\n");
                    for (int k = 0; k<framenow; k++)
                        printf("%d ", M_Frame[k].page_no);
                    printf("\n\n");
                    flagL = 1;
                    break;
                }
            }

            if (flagL == 0){
                diseffectL++;	//缺页次数加1
                //还有剩余的内存可分配
                if (framenow<frame_num){
                    //为该页面分配内存空间
                    M_Frame[framenow].page_no = readframe;	 
                    M_Frame[framenow].flag = 1;
                    framenow++;
                    printf("Diseffect %d times, caused by frame %d\n", diseffectL,readframe);
                    printf("The memory:\n");
                    for (int k = 0; k<framenow; k++)
                        printf("%d ", M_Frame[k].page_no);
                    printf("\n\n");
                }
                //分配物理页面数已满
                else{
                    //淘汰最近最久未使用的页面
                    printf("The memory is full, frame %d out\n", M_Frame[0].page_no);
                    //将页面进行移位
                    for (int j = 1; j<frame_num; j++)
                        M_Frame[j - 1].page_no = M_Frame[j].page_no;
                    //最后一项放入刚读入的页面
                    M_Frame[frame_num - 1].page_no = readframe;	
                    printf("Diseffect %d times, caused by frame %d\n", diseffectL,readframe);
                    printf("The memory:\n");
                    for (int k = 0; k<framenow; k++)
                        printf("%d ", M_Frame[k].page_no);
                    printf("\n\n");
                }
            }
            flagL = 0;
        }
        //统计
        r = diseffectL / (total_instruction + 0.0);
        printf("LRU: diseffect rate  %f\n", r);
        printf("LRU: hit rate  %f\n\n", 1-r);

    return 0;
}

int main(){
    srand((unsigned) time(NULL));
    int p1, p2;
    float r;
    //初始化进程分配页数为-1，表示没有页面占用
    for (int i = 0; i<frame_num; i++)
        M_Frame[i].page_no = -1;    

    printf("Frame: ");
    //通过随机数产生页面访问序列
    for (int i = 0; i<12; i++){
        Access_series[i] = rand() % 12 + 1;
        printf("%d ", Access_series[i]);
    }
    printf("\n\n");
    //创建子进程p1
    while ((p1 = fork()) == -1);    
    if (p1 == 0){
        FIFO(Access_series);
        exit(0);
    }
    wait(0);
    //重置进程分配页数
    for (int i = 0; i<frame_num; i++)
        M_Frame[i].page_no = -1;
    //创建子进程p2
    while ((p2 = fork()) == -1);
    if (p2 == 0){
        LRU(Access_series);
        exit(0);
    }
    wait(0);
    return 0;
}