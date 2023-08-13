//c++ program to implement fcfs
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<stdlib.h>

using namespace std;
struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct,wt,tat,rt,start_time;
}ps[100];

bool comparatorAT(struct process_struct a, struct process_struct b)
{
    int x = a.at;
    int y = b.at;
    return x < y;
}
bool comparatorPID(struct process_struct a, struct process_struct b)
{
    int x = a.pid;
    int y = b.pid;
    return x<y;
}
int main()
{
    int n;
    int length_cycle,total_idle_time =0;
    float sum_tat = 0, sum_wt = 0,sum_rt = 0;
    float cpu_utilization;
    system("cls");
    cout<<"Enter total number of processes (fcfs) :  ";
    cin>>n;
    cout<<endl;
    cout<< fixed << setprecision(3);
    for (int i = 0; i < n; i++)
    {
        cout<<"Enter Process "<<i<<" Arrival Time : ";
        cin>>ps[i].at;
        ps[i].pid = i;
    }
    cout<<endl;

    for (int i = 0; i < n; i++)
    {
        cout<<"Enter Process "<<i<<" Burst Time : ";
        cin>>ps[i].bt;
    }

    sort(ps,ps+n,comparatorAT);

    for(int i=0; i<n; i++)
    {
        ps[i].start_time = (i==0)?ps[i].at : max(ps[i].at,ps[i-1].ct);
        ps[i].ct = ps[i].start_time + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].wt;

        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        sum_rt += ps[i].rt;
        total_idle_time += (i==0) ? 0 : (ps[i].start_time - ps[i-1].ct);
    }
    length_cycle = ps[n-1].ct - ps[0].start_time;
    //sort(ps,ps+n,comparatorPID);

    //OUTPUT
    cout<<"\n Process No. \t AT\tCPU Burst Time\t CT\tTAT\tWT\n";

    for (int i = 0; i < n; i++)
    {
        cout<<" "<<ps[i].pid<<"\t\t "<<ps[i].at<<"\t"<<ps[i].bt<<"\t\t "<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<endl;
    }
    cout<<endl;

    cpu_utilization = (float)(length_cycle - total_idle_time)/length_cycle;

    cout<<"\nAverage Turn Around Time = "<<sum_tat/n;
    cout<<"\nAverage Waiting Time = "<<sum_wt/n;
    //cout<<"\nAverage Response Time = "<<sum_rt/n;
    cout<<"\nThroughput = "<<n/(float)length_cycle;
    cout<<"\nCPU Utilization(Percentage) = "<<cpu_utilization*100;
    return 0;
}