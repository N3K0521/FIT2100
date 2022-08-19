#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ThreadNum 20       // 进程数量，可以自定义，我设置了20个进行比较

typedef enum{
    READY = -2, RUNNING = -1, OVER = 0, EXIT = 1
} ProcessState;

//线程的虚拟PCB信息,PCB进程控制块
typedef struct VirPCB
{
    int process_id;
    int arrival_time;
    int service_time;
    int deadline;
    int remaining_time;
    int wait_time;
    int turnaround_time;
    ProcessState state;
} VirPCB;

VirPCB PCBs[ThreadNum];

//PCB初始化函数：随机生成一组进程
void initPCB()
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < ThreadNum; i++)
    {
        PCBs[i].process_id = i;

        if (i > 0) PCBs[i].arrival_time = PCBs[i-1].arrival_time +  rand() % ThreadNum;
        else PCBs[i].arrival_time = 0;

        PCBs[i].remaining_time = PCBs[i].service_time = 1 + rand() % ThreadNum;

        PCBs[i].deadline = PCBs[i].arrival_time + PCBs[i].service_time + rand() % ThreadNum;

        PCBs[i].state = READY;
        PCBs[i].wait_time = 0;
        PCBs[i].turnaround_time = 0;
    }
}

// 打印进程信息
void showPCB(){
    printf("Process_name    Arrival_time    Service_time    Deadline    Wait_time    Turnaround_time    Deadline_Met\n");
    for (int i = 0; i < ThreadNum; i++)
    {
        printf(" P%-12d    %-12d    %-12d    %-8d    %-8d    %-15d    %d\n",
               PCBs[i].process_id, PCBs[i].arrival_time, PCBs[i].service_time, PCBs[i].deadline, PCBs[i].wait_time, PCBs[i].turnaround_time, PCBs[i].state);
    }
}

//FCFS函数（先到先服务）
void FCFSdisp()
{
    //初始化各线程
    for (int i = 0; i < ThreadNum; i++){
        PCBs[i].wait_time = 0;
        PCBs[i].turnaround_time = 0;
        PCBs[i].remaining_time = PCBs[i].service_time;
        PCBs[i].state = READY;
    }

    int clock = 0;      //初始化时钟
    int i = 0;
    while (i < ThreadNum)
    {
        if (clock >= PCBs[i].arrival_time && PCBs[i].state == READY)
        {
            // 这一部分的作用是判断一个任务是否能在截止日期前完成，若不能则丢弃，在FCFS中不使用，因为其要求所有进程都要完成
//            if (PCBs[i].deadline - clock < PCBs[i].remaining_time){
//                PCBs[i].state = OVER;
//            }else
            {
                // 挨个任务按照先来后到的顺序去执行，时钟（计时器）跟着增长即可，同时修改进程状态
                PCBs[i].wait_time = clock - PCBs[i].arrival_time;
                PCBs[i].turnaround_time = PCBs[i].wait_time + PCBs[i].remaining_time;
                PCBs[i].remaining_time = 0;
                PCBs[i].state = EXIT;
                clock = clock + PCBs[i].service_time;
            }
            i++;
        }
        else clock++;
    }
}

//SPN函数（Shortest process next）
void SPNdisp()
{
    //初始化各线程
    for (int i = 0; i < ThreadNum; i++){
        PCBs[i].remaining_time = PCBs[i].service_time;
        PCBs[i].state = READY;
        PCBs[i].wait_time = 0;
        PCBs[i].turnaround_time = 0;
    }

    int clock = 0;      //初始化时钟
    int i = 0;
    while (i < ThreadNum)
    {
        int min_time = ThreadNum * ThreadNum;
        int pos = -1;
        int isempty = 1;     //当前队列是否空
        for (int j = 0; j < ThreadNum; j++)
        {
            if (clock >= PCBs[j].arrival_time && PCBs[j].state == READY)
            {
                // 这一部分的作用是判断一个任务是否能在截止日期前完成，若不能则丢弃，在SPN中不使用，因为其要求所有进程都要完成
//                if (clock + PCBs[j].service_time > PCBs[j].deadline) {
//                    PCBs[j].state = OVER;
//                    i++;
//                }else
                {
                    // 使用一个循环去寻找最短的作业，将其优先执行
                    if (PCBs[j].service_time < min_time) {
                        min_time = PCBs[j].service_time;
                        pos = j;
                        isempty = 0;
                    }
                }
            }
        }
        if (isempty == 1) clock++;
        else {
            // 同理修改时钟和进程状态即可
            PCBs[pos].wait_time = clock - PCBs[pos].arrival_time;
            PCBs[pos].turnaround_time = PCBs[pos].wait_time + PCBs[pos].service_time;
            PCBs[pos].remaining_time = 0;
            PCBs[pos].state = EXIT;
            i++;
            clock += PCBs[pos].service_time;
        }
    }
}

//SRTN函数（Shortest remaining time next）
void SRTNdisp(){
    //初始化各线程
    for (int i = 0; i < ThreadNum; i++){
        PCBs[i].remaining_time = PCBs[i].service_time;
        PCBs[i].state = READY;
        PCBs[i].wait_time = 0;
        PCBs[i].turnaround_time = 0;
    }

    int clock = 0;      //初始化时钟
    int i = 0;
    while (i < ThreadNum)
    {
        int min_time = ThreadNum * ThreadNum;
        int pos = -1;
        int isempty = 1;     //当前队列是否空
        for (int j = 0; j < ThreadNum; j++)
        {
            if (clock >= PCBs[j].arrival_time && PCBs[j].state == READY)
            {
                // 这一部分的作用是判断一个任务是否能在截止日期前完成，若不能则丢弃，在SRTN中不使用，因为其要求所有进程都要完成
//                if (clock + PCBs[j].remaining_time > PCBs[j].deadline) {
//                    PCBs[j].state = OVER;
//                    i++;
//                }else
                {
                    // 同理使用一个循环去寻找剩余时间最短的作业，将其优先执行
                    if (PCBs[j].remaining_time < min_time) {
                        min_time = PCBs[j].remaining_time;
                        pos = j;
                        isempty = 0;
                    }
                }
            }
        }
        clock++;
        if (isempty == 0){
            // 同理修改任务状态，但值得注意的是，
            // 由于是抢占，时钟不能直接增加任务执行时间，而是一点一点的增加，相对应的任务的剩余执行时间也是一点一点的减少，然后进入下一轮的比较
            // 此外，进程的状态并不是每次都修改，只有当任务执行完毕，也就是剩余执行时间为0时才会修改进程状态
            PCBs[pos].remaining_time--;
            if (PCBs[pos].remaining_time == 0){
                PCBs[pos].turnaround_time = clock - PCBs[pos].arrival_time;
                PCBs[pos].wait_time = PCBs[pos].turnaround_time - PCBs[pos].service_time;
                PCBs[pos].state = EXIT;
                i++;
            }
        }
    }
}

//Deadlinedisp函数（思路：抢占，截止时间和剩余时间的差值越小，也就是执行越紧迫的任务优先执行，以尽可能满足在截止时间内完成调度）
void Deadlinedisp()
{
    //初始化各线程
    for (int i = 0; i < ThreadNum; i++){
        PCBs[i].remaining_time = PCBs[i].service_time;
        PCBs[i].state = READY;
        PCBs[i].wait_time = 0;
        PCBs[i].turnaround_time = 0;
    }

    int clock = 0;      //初始化时钟
    int i = 0;
    while (i < ThreadNum)
    {
        int min_time = ThreadNum * ThreadNum;
        int pos = -1;
        int isempty = 1;     //当前队列是否空
        for (int j = 0; j < ThreadNum; j++)
        {
            if (clock >= PCBs[j].arrival_time && PCBs[j].state == READY)
            {
                // 思路和SRTN类似，但是要加上判断是否能在截止时间内完成，不能完成则标记为超时状态OVER
                if (clock + PCBs[j].remaining_time > PCBs[j].deadline)
                {
                    PCBs[j].state = OVER;
                    i++;
                }else
                {
                    // 这里使用的策略是截止时间和剩余时间的差值，也就是当前任务的紧迫程度
                    if (PCBs[j].deadline - PCBs[j].remaining_time < min_time) {
                        min_time = PCBs[j].deadline - PCBs[j].remaining_time;
                        pos = j;
                        isempty = 0;
                    }
                }
            }
        }
        clock++;
        if (isempty == 0){
            // 这里的时间片增长和进程状态更新类似
            PCBs[pos].remaining_time--;
            if (PCBs[pos].remaining_time == 0){
                PCBs[pos].turnaround_time = clock - PCBs[pos].arrival_time;
                PCBs[pos].wait_time = PCBs[pos].turnaround_time - PCBs[pos].service_time;
                PCBs[pos].state = EXIT;
                i++;
            }
        }
    }
}

int main()
{
    initPCB();

    printf("\n-----------The result of FCFS dispatch-----------\n");
    FCFSdisp();
    showPCB();

    printf("\n-----------The result of SPN dispatch-----------\n");
    SPNdisp();
    showPCB();

    printf("\n-----------The result of SRTN dispatch-----------\n");
    SRTNdisp();
    showPCB();

    printf("\n-----------The result of Deadline dispatch-----------\n");
    Deadlinedisp();
    showPCB();

    return 0;
}
