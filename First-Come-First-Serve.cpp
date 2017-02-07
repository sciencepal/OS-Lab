#include <bits/stdc++.h>

using namespace std;

class Process
{
public:
    double arrivalTime,burstTime;
    Process()
    {
        arrivalTime=burstTime=0;
    }
    void set(double a,double b)
    {
        arrivalTime = a;
        burstTime = b;
    }
};

void FCFS(Process *p,int n)
{
    //*P is pointer to array of process objects and n is the number of processes
    //First come First Serve
    double totalWaitTime=0,currWaitTime=0,avgTurnAround=0;
    double totalTime=0;
    cout<<"Process\tArrival\tBurst\tWait\tTurn";
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            totalWaitTime = p[i].arrivalTime;
            totalTime = p[i].arrivalTime;
            totalTime += p[i].burstTime;
            avgTurnAround += p[i].burstTime;
            cout<<"\nP"<<i+1<<"\t"<<p[i].arrivalTime<<"\t"<<p[i].burstTime<<"\t"<<totalWaitTime<<"\t"<<p[i].burstTime<<endl;
        }
        else
        {
            if(totalTime-p[i].arrivalTime > 0)
            {
                totalWaitTime += totalTime - p[i].arrivalTime;
                currWaitTime = totalTime - p[i].arrivalTime;
            }
            else
            {
                currWaitTime = 0;
            }
            totalTime += p[i].burstTime;
            avgTurnAround += p[i].burstTime;
            cout<<"P"<<i+1<<"\t"<<p[i].arrivalTime<<"\t"<<p[i].burstTime<<"\t"<<currWaitTime<<"\t"<<p[i].burstTime<<endl;
        }
    }
    cout<<"\nAverage Wait Time: "<<totalWaitTime/n<<"\nAverage Turn Around Time: "<<avgTurnAround/n<<endl;
}

int main()
{
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    double a,b;
    Process *p = new Process[n];
    for(int i=0;i<n;i++)
    {
        cin>>a>>b;
        p[i].set(a,b);
    }
    FCFS(p,n);
}
