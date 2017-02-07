void sched::computeRR(){

    readData();
    Init();
    int time,j,q,i,dec=0;
    cout<<"Enter the time quantum:\n";
    cin>>q;
    cout<<"Gantt Chart\n ";
    for(time=0;time<total;)
    {
        for(i=0;i<n;i++)
        {
            if(at[i]<=time && finish[i]==0)
            {

                cout<<"("<<time<<")|==P"<<(i+1)<<"==|";
                if(rt[i]<q)  {
                    dec=rt[i];
                }
                else {dec=q;}

                rt[i]=rt[i]-dec;
                if(rt[i]==0) finish[i]=1;
                for(j=0;j<n;j++)
                    if(j!=i && finish[j]==0 && at[j]<=time)
                        wt[j]+=dec;
                 time=time+dec;

            }

        }

    }

    cout<<"("<<total<<")"<<endl;
    dispTime();

}
