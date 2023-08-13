//preemptive priority Scheduling

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include<climits>
using namespace std;

struct process {
    int pid;
    int at;
    int bt;
    int priority;
    int start_time;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main()
{

    int n;
    struct process p[100];
    float avg_tat;
    float avg_wt;
    float avg_rt;
    float cpu_utilisation;
    int total_tat = 0;
    int total_wt = 0;
    int total_rt = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(3) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i<<": ";
        cin>>p[i].at;
        cout<<"Enter burst time of process "<<i<<": ";
        cin>>p[i].bt;
        cout<<"Enter priority of the process "<<i<<": ";
        cin>>p[i].priority;
        p[i].pid = i;
        burst_remaining[i] = p[i].bt;
        cout<<endl;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].at < p[idx].at) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].bt) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;

            if(burst_remaining[idx] == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].rt = p[idx].start_time - p[idx].at;

                total_tat += p[idx].tat;
                total_wt += p[idx].wt;
                total_rt += p[idx].rt;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
    }

    int min_at = 10000000;
    int max_ct = -1;
    for(int i = 0; i < n; i++) {
        min_at = min(min_at,p[i].at);
        max_ct = max(max_ct,p[i].ct);
    }

    avg_tat = (float) total_tat / n;
    avg_wt = (float) total_wt / n;
    avg_rt = (float) total_rt / n;
    cpu_utilisation = ((max_ct - total_idle_time) / (float) max_ct )*100;
    throughput = float(n) / (max_ct - min_at);

    cout<<endl;

    cout<<"\nP No.\tAT\tCPU Burst Time\tPriority\tStart Time\tCT\tTAT\tWT\tRT\n";
    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t\t"<<p[i].bt<<"\t"<<p[i].priority<<"\t\t"<<p[i].start_time<<"\t\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\t"<<p[i].rt<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_tat<<endl;
    cout<<"Average Waiting Time = "<<avg_wt<<endl;
    cout<<"Average Response Time = "<<avg_rt<<endl;
    cout<<"CPU Utilization = "<<cpu_utilisation<<"%"<<endl;
    cout<<"Throughput = "<<throughput<<" process/unit time"<<endl;


}