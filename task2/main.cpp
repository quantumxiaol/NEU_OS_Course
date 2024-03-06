#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

enum state {created, ready, running, blocked, terminated};

using namespace std;

struct PCB{
    int time;//所需时间片
    int Pid;//进程ID
    int Ppri;//进程优先级
};

vector<PCB> Created;//创建队列
vector<PCB> Ready;//就绪队列
vector<PCB> Blocked;//等待队列
vector<PCB> Terminated;//结束队列
PCB Run;//running进程
//用vector实现队列，用sort函数实现优先级排序
//vector和queue的区别：vector可以随机访问，queue只能从头部删除，尾部添加
//vector的push_back()和pop_back()函数实现队列的入队和出队
//vector的insert()和erase()函数实现队列的入队和出队



int p=10000;

//比较优先级
bool greaterPCB(const PCB& s1,const PCB s2){
    return s1.Ppri > s2.Ppri;
}

//阻塞态->就绪态
int Occurs(){
    if(Ready.size()<=5){
        if(!Blocked.empty()){
            Ready.push_back(Blocked.front());
            Blocked.erase(Blocked.begin());//
            //ready队列排序
            sort((Ready.begin()),Ready.end(),greaterPCB);
            return 0;
        }
        else{
            cout<<"blocked queue is empty.";
            return -1;
        }

        }
}

//手动新建进程
int Create(){
    if(Ready.size()<=5){
        PCB process;
        cout<<"please input time:";
        cin>>process.time;
        cout<<"please input priority:";
        cin>>process.Ppri;
        process.Pid=p;
        Ready.push_back(process);
        sort((Ready.begin()),Ready.end(),greaterPCB);
        p++;
        return 0;
    }
    else{
        cout<<"ready queue is full.";
        return -1;
    }

}

//运行态空时往运行态添加一个进程
//就绪态->运行态
int Dispatch(){
    PCB temp;
    //running状态为空
    if(Run.Pid==114514){
        if(!Ready.empty()&&(*Ready.begin()).Ppri>Run.Ppri){
            Run=Ready.front();
            Ready.erase(Ready.begin());
            return 0;
        }
    }
    //running状态不为空，而且ready队列有process优先级高于running状态process优先级
    else if(Ready.front().Ppri>Run.Ppri){
        temp=Run;
        Run=Ready.front();
        Ready.erase(Ready.begin());
        Ready.push_back(temp);
        sort((Ready.begin()),Ready.end(),greaterPCB);
        return 0;
    }
    else{
        cout<<"there is a process already runing";
        return -1;        
    }
}

//进程结束并释放
int Realse(){
    if(!Ready.empty()){
        Run=Ready.front();
        Terminated.push_back(Run);
        Ready.erase(Ready.begin());

        return 0;
    }
    else{
        Run.Pid=114514;
        Run.time=-1;
        Run.Ppri=-1;
        cout<<"there is no process in the cache.";
        return -1;
    }
}

//时间片用完
//运行态->就绪态
int Timeout(){
    if(!Run.Pid==114514){
        Run.time--;
        //进程结束
        if(Run.time==0){
            Realse();
        }
        //进程未结束，进入ready状态
        else{
            Ready.push_back(Run);
            sort((Ready.begin()),Ready.end(),greaterPCB);
            Run=Ready.front();
            Ready.erase(Ready.begin());
        }
    }
    //running状态为空
    else{
        Dispatch();
        return -1;
    }

    return 0;

}
//阻塞
//运行态->阻塞态
int Wait(){
    if(Run.Pid!=114514){
        Blocked.push_back(Run);
        Run.Pid=114514;
        Run.Ppri=-1;
        Run.time=-1;
        Dispatch();
        return -1;
    }
}

//输出队列
int Output(){
    vector<PCB> ::iterator Iter;
    cout<<"running:|";
    cout<<Run.Pid<<" "<<Run.time<<" "<<Run.Ppri<<"|";
    cout<<endl;

    cout<<"blocked:|";
    for(Iter = Blocked.begin(); Iter!=Blocked.end(); Iter++ )
        cout<<(*Iter).Pid<<" "<<(*Iter).time<<" "<<(*Iter).Ppri<<"|";
    cout<<endl;

    cout<<"ready:|";
    for(Iter = Ready.begin(); Iter!=Ready.end(); Iter++ )
        cout<<(*Iter).Pid<<" "<<(*Iter).time<<" "<<(*Iter).Ppri<<"|";
    cout<<endl;

    cout<<"terminated:|";
    for(Iter = Terminated.begin(); Iter!=Terminated.end(); Iter++ )
        cout<<(*Iter).Pid<<" "<<(*Iter).time<<" "<<(*Iter).Ppri<<"|";
    cout<<endl;

    return 0;
}

int main(){
    char in='a';
    while(in!='e'){
        std::cout<<" 'P' to create a process"<<std::endl;
        std::cout<<" 'T' to timeout"<<std::endl;
        std::cout<<" 'D' to process end"<<std::endl;
        std::cout<<" 'W' to blocked,"<<std::endl;
        std::cout<<" 'O' to blocked to ready"<<std::endl;
        std::cout<<" 'R' to run process"<<std::endl;
        std::cout<<" 'e' to exit,"<<std::endl;
        std::cin>>in;

        switch (in){

        case 'T':
            Timeout();
            Output();
            break;

        case 'D':
            Dispatch();
            Output();
            break;

        case 'W':
            Wait();
            Output();
            break;

        case 'P':
            Create();
            Output();
            break;

        case 'O':
            Occurs();
            Output();
            break;

        case 'R':
            Realse();
            Output();
            break;
            break;
        }
    }

    return 0;
}
