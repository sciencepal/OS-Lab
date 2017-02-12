#include <bits/stdc++.h>
using namespace std;

int main()
{
    int i, x, y, n;
    bool done[1000], inqueue[1000];
    //while(true)
    {
        pair < int, pair <int, int> > proc2[1000], proc[1000], proc1[1000];
        int wt[10000], ft[10000];
        puts("Enter Data : ");
        puts("");
        puts("Enter the number of processes : ");
        scanf("%d",&n);
        puts("Enter arrival time and CPU burst times of the processes : ");
        for (i = 0; i<n; i++)
        {
            scanf("%d %d",&x,&y);
            proc2[i].first = x;
            proc2[i].second.first = i;
            proc2[i].second.second = y;
            proc[i].first = x;
            proc[i].second.first = -i;
            proc[i].second.second = -y;
        }
        sort(proc, proc + n);
        for (i = 0; i<n; i++)
        {
            proc1[i].first = proc[i].second.second; // process time
            proc1[i].second.first = proc[i].second.first;  // pid
            proc1[i].second.second = proc[i].first; // arrival time
            done[i] = false;
            inqueue[i] = false;
        }
        priority_queue < pair < int, pair <int, int> > > pq;
        int k = 0, tim = 0, d;
        while (true)
        {
            d = 0;
            if (!pq.empty())
            {
                pair <int, pair < int, int > > job = pq.top();
                pq.pop();
                job.first++;
                int jobid = -job.second.first;
                cout<<"Time : "<<tim<<" Process : "<<jobid+1<<endl;
                if (job.first == 0)
                {
                    cout<<"Job with PID "<<jobid+1<<" has been completed"<<endl;
                    done[jobid] = true;
                    ft[jobid] = tim;
                    wt[jobid] = ft[jobid] - proc2[jobid].second.second - proc2[jobid].first;
                }
                else
                    pq.push(job);
            }
            tim++;
            for (i = 0; i< n; i++)
            {
                if (done[i])
                    d++;
                if (!inqueue[i] && proc1[i].second.second < tim)
                {
                    pq.push(proc1[i]);
                    inqueue[i] = true;
                }
            }
            if (d == n)
                break;
        }
        cout<<endl;
        cout<<"PID\tAT\tBT\tFT\tWT\t"<<endl<<endl;
        for (i =0 ; i < n; i++)
            cout<<proc2[i].second.first + 1<<"\t"<<proc2[i].first<<"\t"<<proc2[i].second.second<<"\t"<<ft[i]<<"\t"<<wt[i]<<endl;
    }
    return 0;
}
