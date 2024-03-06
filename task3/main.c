/***************************************************************/
/*         PROGRAM NAME:         PRODUCER_CONSUMER             */
/*    This program simulates two processes, producer which     */
/* continues  to produce message and  put it into a buffer     */
/* [implemented by PIPE], and consumer which continues to get  */
/* message from the buffer and use it.                         */
/*    The program also demonstrates the synchronism between    */
/* processes and uses of PIPE.                                 */
/***************************************************************/
#include  <stdio.h>
#include  <stdlib.h>
#define PIPESIZE 8
#define PRODUCER 0
#define CONSUMER 1
#define RUN      0    /* statu of process */
#define WAIT     1    /* statu of process */
#define READY    2    /* statu of process */
#define NORMAL   0
#define SLEEP    1
#define AWAKE    2
#define QUEUE_SIZE 100
struct pcb
{
    char *name;
    int statu;//在process[2]中表示状态，在队列中表示进程ID
    int time;/* times of execution */
};
struct pipetype
{
    char type;
    int  writeptr;
    int  readptr;
    struct pcb *pointp;     /* write wait point */
    struct pcb *pointc;
};
typedef struct
{
    struct pcb *base;
    int front;
    int rear;
}Queue;//添加等待队列

int pipe[PIPESIZE];
struct pipetype pipetb;
struct pcb process[2];

//添加对队列的三个操作
void Queue_Init(Queue *Q)//初始化队列
{
    Q->base=malloc(QUEUE_SIZE*sizeof(struct pcb));
    if(!Q->base) printf("创建队列失败\n");
    Q->front=Q->rear=0;
}

void Queue_En(Queue *Q,struct pcb e)//若队列未满，向队列尾部添加元素
{
    if((Q->rear+1)%QUEUE_SIZE==Q->front) printf("队列已满\n");
    *(Q->base+Q->rear)=e;
    Q->rear=(Q->rear+1)%QUEUE_SIZE;
}

struct pcb Queue_De(Queue *Q)//若队列不为空，把队列头元素删除，并返回其值
{
    struct pcb e;
    if(Q->rear==Q->front) printf("队列空\n");
    e=*(Q->base+Q->front);
    Q->front=(Q->front+1)%QUEUE_SIZE;
    return(e);
}


// 队列的实现
int waitpre[1000],waitcon[1000];
int waitpref=0,waitconf=0;
int waitpret=0,waitcont=0;

int inwait(int n,int wait[1000]){
    wait[waitpret]=n;
    waitpret = (waitpret+1)%1000;
    return 0;
}
int outwait(int wait[1000]){
    int n;
    n = waitpre[waitconf];
    waitconf = (waitconf+1)%1000;
    return n;
}
int statuspre(){
    if(waitpret==waitpref) return 0;
    else return (waitpret-waitpref)%1000;
}
int statuscon(){
    if(waitcont==waitconf) return 0;
    else return (waitcont-waitconf)%1000;
}
int full = 0;    //full信号量
int empty = PIPESIZE;    //empty信号量
int pn=0;   //生产者总数
int cn=0;    //消费者总数




int main()
{
    int output,ret,i;
    char in[2];
    struct pcb x;
    Queue p,c;
    Queue_Init(&p);//p等待队列
    Queue_Init(&c);//c等待队列
    int runp(),runc(),prn();
    pipetb.type = 'c';
    pipetb.writeptr = 0;
    pipetb.readptr = 0;
    pipetb.pointp=pipetb.pointc=NULL;
    process[PRODUCER].name = "Producer\0";
    process[CONSUMER].name = "Consumer\0";
    process[PRODUCER].statu = process[CONSUMER].statu = READY;
    process[PRODUCER].time = process[CONSUMER].time = 0;
    output = 0;
    printf("Now starting the program!\n");
    printf("Press 'p' to run PRODUCER, press 'c' to run CONSUMER.\n");
    printf("Press 'e' to exit from the program.\n");
    for(i=0;i<1000;i++)
    {
        in[0]='N';
        while(in[0]=='N')
        {
           scanf("%s",in);
           if(in[0]!='e'&&in[0]!='p'&&in[0]!='c')
                in[0]='N';
        }
        if(in[0]=='p')
        {
            output = (output+1)%100;
            if((ret=runp(output,process,pipe,&pipetb,PRODUCER,&c))==SLEEP)//p.sleep的处理结果修改
            {
                process[PRODUCER].statu=output;//
                Queue_En(&p,process[PRODUCER]);//把此进程插入队列中
                process[PRODUCER].statu=WAIT;
                pipetb.pointp=&process[PRODUCER];
            }
            if(ret==AWAKE)//p.awake处理结果
            {
                Queue_De(&c);//删除等待队列中首元素，即删除等待的c的数量
                process[CONSUMER].statu=READY;
                pipetb.pointc=NULL;
                runc(process,pipe,&pipetb,CONSUMER,&p);
            }
        }
        if(in[0]=='c')
        {
            if((ret=runc(process,pipe,&pipetb,CONSUMER,&p))==SLEEP)//c.sleep的处理结果修改
            {
                Queue_En(&c,process[CONSUMER]);//向c队列中添加一个元素，即增加等待的c的次数
                pipetb.pointc = &process[CONSUMER];//
            }
            if(ret==AWAKE)//c.awake的处理结果修改
            {
                x=Queue_De(&p);//把p队尾元素取出来赋予x
                process[PRODUCER].statu=READY;
                pipetb.pointp=&x;
                runp(x.statu,process,pipe,&pipetb,PRODUCER,&c);
            }
        }
        if(in[0]=='p'&&process[PRODUCER].statu==WAIT)
        {
            printf("PRODUCER is waiting, can't be scheduled.\n");
        }
        if(in[0]=='c'&&process[CONSUMER].statu==WAIT)
        {
            printf("CONSUMER is waiting, can't be scheduled.\n");
        }
        if(in[0]=='e') exit(1);
        prn(process,pipe,pipetb); in[0]='N';
    }
    return 0;
}
int runp(out,p,pipe,tb,t,Q)  /* run producer */
 int out,pipe[],t;
 struct pcb p[];
 struct pipetype *tb;
 Queue *Q;
 {
     p[t].statu=RUN;
     printf("run PRODUCER. product %d     ",out);
     if(process[PRODUCER].time==(process[CONSUMER].time+8))//p.sleep条件修改
        {
            p[t].statu=WAIT;
            return(SLEEP);
        }
        pipe[tb->writeptr]=out; tb->writeptr++;
        p[t].time++;
        p[t].statu=READY;
        if(tb->writeptr>=8) tb->writeptr=0;//写指针循环的条件修改
        if(p[t].time==process[CONSUMER].time) tb->writeptr=tb->readptr=0;
        if(Q->rear!=Q->front)
            return(AWAKE);//p.awake条件修改为只要c队列不为空
        return(NORMAL);
 }

 int runc(p,pipe,tb,t,Q)      /* run consumer */
 int pipe[],t;
 struct pcb p[];
 struct pipetype *tb;
 Queue *Q;
 {
     int c;
     p[t].statu = RUN;
     printf("run CONSUMER. ");
     if(process[CONSUMER].time==process[PRODUCER].time)//c.sleep条件修改
        {
            p[t].statu=WAIT;
            return(SLEEP);
        }
        c = pipe[tb->readptr];
        tb->readptr++;
        printf(" use %d      ",c);
        p[t].time++;
        p[t].statu=READY;
         if(tb->readptr>=8) tb->readptr=0;//读指针循环的条件修改
        if(p[t].time==process[PRODUCER].time) tb->writeptr=tb->readptr=0;
        if(Q->rear!=Q->front)
            return(AWAKE);//c.awake条件修改，只要p队列不为空
        return(NORMAL);
 }

 int prn(p,pipe,tb)
 int pipe[];
 struct pipetype tb;
 struct pcb p[];
 {
     int i;
     printf("\n         ");
     for(i=0;i<PIPESIZE;i++)
        printf("------ ");
     printf("\n        |");
     for(i=0;i<PIPESIZE;i++)
        if(((i>=tb.readptr)&&(i<tb.writeptr))||((process[PRODUCER].time>process[CONSUMER].time)&&(((i<tb.writeptr)&&(tb.readptr>=tb.writeptr))||((i>=tb.readptr)&&(tb.readptr>=tb.writeptr)))))//判断缓冲区是否为空的条件修改
        printf("  %2d  |",pipe[i]);
        else
        printf("      |");
     printf("\n         ");
     for(i=0;i<PIPESIZE;i++)
        printf("------ ");
     printf("\nwriteptr = %d, readptr = %d,  ",tb.writeptr,tb.readptr);
     if(p[PRODUCER].statu==WAIT)
        printf("PRODUCER wait ");
     else
        printf("PRODUCER ready ");
     if(p[CONSUMER].statu==WAIT)
        printf("CONSUMER wait ");
     else
        printf("CONSUMER ready ");
     printf("\n");
     return 0;
 }