#include<iostream>

using namespace std;
int main()
{
    int a[10],b[10],x[10],pr[10]={0};
    int waiting[10],turnaround[10],completion[10];
    int i,j,smallest,count=0,time,n;
    double avg=0,tt=0,end;
    cout<<"\nEnter the number of Processes: ";
    cin>>n;
    cout<<endl;
    for(i=0;i<n;i++)
    {
      cout<<"Enter arrival time of process: ";
      cin>>a[i];
    }
    cout<<endl;
    for(i=0;i<n;i++)
    {
      cout<<"Enter burst time of process: ";
      cin>>b[i];
    }
    cout<<endl;
    for(i=0;i<n;i++)
    {
      cout<<"Enter priority of process: ";
      cin>>pr[i];
    }
    cout<<endl;
    for(i=0;i<n;i++)
        x[i]=b[i];

    pr[9]=-1;
    for(time=0;count!=n;time++)
    {
        smallest=9;
        for(i=0;i<n;i++)
        {
            if(a[i]<=time && pr[i]>pr[smallest] && b[i]>0 )
                smallest=i;
        }
        time+=b[smallest]-1;
        b[smallest]=-1;
        count++;
        end=time+1;
        completion[smallest] = end;
        waiting[smallest] = end - a[smallest] - x[smallest];
        turnaround[smallest] = end - a[smallest];
    }
    cout<<"Process"<<"\t"<< "   Burst-time"<<"\t"<<"   arrival-time"<<"\t\t"<<"Priority" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"p"<<i+1<<"\t\t"<<x[i]<<"\t\t"<<a[i]<<"\t\t"<<pr[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
    cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"\nAverage Turnaround time ="<<tt/n<<endl;
}