#include <bits/stdc++.h>
using namespace std;

int n, temp=0, ch = 0;
int at[10000],bt[10000],p[10000],wt[10000],ft[10000], pt[10000];
bool done[10000];

void sorty()
{
    int t;
    for (int i = 0; i< n; i++)
    {
        for (int j = i+1; j<n; j++)
        {
            if (at[j] < at[i])
            {
                t = at[i];
                at[i] = at[j];
                at[j] = t;
                t = bt[i];
                bt[i] = bt[j];
                bt[j] = t;
                t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
}


void sortysorty()
{
    int t;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(pt[j]>pt[j+1])
            {
                t = pt[j+1];
                pt[j+1] = pt[j];
                pt[j] = t;
                t=bt[j+1];
                bt[j+1]=bt[j];
                bt[j]=t;
                t=p[j+1];
                p[j+1]=p[j];
                p[j]=t;
                t=at[j+1];
                at[j+1]=at[j];
                at[j]=t;
            }
            else if (pt[j] == pt[j+1])
            {
                if (p[j]>p[j+1])
                {
                    t = pt[j+1];
                    pt[j+1] = pt[j];
                    pt[j] = t;
                    t=bt[j+1];
                    bt[j+1]=bt[j];
                    bt[j]=t;
                    t=p[j+1];
                    p[j+1]=p[j];
                    p[j]=t;
                    t=at[j+1];
                    at[j+1]=at[j];
                    at[j]=t;
                }
            }
        }
    }
}


void sortysortysorty()
{
    int t;
    for (int i = 0; i< n; i++)
    {
        for (int j = i+1; j<n; j++)
        {
            if (p[j] < p[i])
            {
                t = pt[i];
                pt[i] = pt[j];
                pt[j] = t;
                t = ft[i];
                ft[i] = ft[j];
                ft[j] = t;
                t = wt[i];
                wt[i] = wt[j];
                wt[j] = t;
                t = at[i];
                at[i] = at[j];
                at[j] = t;
                t = bt[i];
                bt[i] = bt[j];
                bt[j] = t;
                t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
}


void print()
{
    puts("");
    if (ch == 1)
        puts("Matrix After FCFS Scheduling");
    else
        puts("Matrix After SJF Scheduling");
    puts("");
    puts("PID\tAT\tBT\tPT\tFT\tWT");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], pt[i], ft[i], wt[i]);
    puts("");
}



void fcfs()
{
    for(int i=0;i<n;i++)
    {
        temp = temp + bt[i];
        if(i>0)
        {
            wt[i] = wt[i-1] + at[i-1] + bt[i-1] - at[i];
            if(wt[i] < 0)
                wt[i] = 0;
        }
        else
            wt[0] = 0;
        ft[i] = wt[i] + bt[i] + at[i];
    }
    print();
}


void sjf()
{
    sortysorty();
    int c = 0, x = 0;
    while(c < n)
    {
        for(int i=0;i<n;i++)
        {
            if(!done[i])
            {
                if(at[i] <= x)
                {
                    wt[i] = x - at[i];
                    ft[i] = wt[i] + bt[i] + at[i];
                    x = x + bt[i];
                    done[i] = true;
                    break;
                }
            }
        }
        c++;
    }
    sortysortysorty();
    print();
}



int main()
{
    while (true)
    {
        puts("****MENU****");
        puts("");
        puts("1. FCFS");
        puts("2. SJF");
        puts("3. Exit");
        puts("");
        puts("************");
        scanf("%d", &ch);
        puts("");
        puts("Enter Data : ");
        puts("");
        puts("Enter the number of processes : ");
        scanf("%d",&n);
        puts("Enter arrival time and CPU burst times of the processes and priority : ");
        for (int i = 0; i<n; i++)
            scanf("%d %d %d",&at[i],&bt[i], &pt[i]);
        for(int i = 0; i < n+1; i++)
        {
            p[i] = i + 1;
            done[i] = false;
        }
        sorty();
        if (ch == 1)
            fcfs();
        else if (ch == 2)
            sjf();
        else
            break;
    }
    return 0;
}
