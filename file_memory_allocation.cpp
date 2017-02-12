#include <bits/stdc++.h>
using namespace std;

struct file
{
    int sz;
    string name;
    string type;
    bool arr[];
    int start;
    int finish;
    int allocstart;
    vector <struct file> joined;
};

/// srand (time(NULL));
///  int iSecret = rand() % 10 + 1;

vector <struct file> files;

int main()
{
    int totalfiles = 0;
    string s;
    bool blocks[500];
    bool allocated[500];
    memset(allocated, false, sizeof(allocated));
    vector <string> fname;
    files.clear();
    int pos = 0, k, fsz = 0, ch;
    while (true)
    {
        cout<<"MENU"<<endl;
        cout<<"1. Create File"<<endl;
        cout<<"2. Delete File"<<endl;
        cout<<"3. Join Files"<<endl;
        cout<<"4. Rename File"<<endl;
        cout<<"5. Show Stats"<<endl;
        cin>>ch;
        if (ch == 1)
        {
            cout<<"Enter required size in bytes"<<endl;
            cin>>k;
            int coun = 0;
            while(coun < 5)
            {

                srand(time(NULL));
                int r = rand()%500;
                if (k>=300)
                    r = 179+coun;
                cout<<r<<endl;
                if (r + k >= 500)
                {
                    cout<<"Could not allocate Trying again"<<endl;
                    coun++;
                    continue;
                }
                bool all = false;
                for (int i = r; i< r+k; i++)
                {
                    if (allocated[i] == true)
                    {
                        all = true;
                        break;
                    }
                }
                coun++;
                if (coun == 5)
                {
                    coun = 10000;
                    break;
                }
                if (all)
                {
                    cout<<"Could not allocate Trying again"<<endl;
                    continue;
                }
                else
                {
                    struct file f1;
                    files.push_back(f1);
                    cout<<"Enter file name"<<endl;
                    vector <string>:: iterator it;
                    it = fname.begin();
                    cin>>s;
                    while (count(fname.begin(), fname.end(), s)>0)
                    {
                        cout<<"File already exists - Enter file name again"<<endl;
                        cin>>s;
                    }
                    files[pos].name = s;
                    fname.push_back(s);
                    cout<<"Enter file type"<<endl;
                    cin>>s;
                    files[pos].type = s;
                    files[pos].sz = k;
                    //files[pos].arr = (bool*)malloc(k*sizeof(bool));
                    files[pos].start = r;
                    files[pos].finish = r+k-1;
                    cout<<"BLOCKS ALLOCATED"<<endl;
                    for (int i = r; i< r+k; i++)
                    {
                        cout<<i<<" ";
                        allocated[i] = true;
                    }
                    cout<<endl;
                    fsz+=k;
                    pos++;
                    totalfiles++;
                    break;
                }
            }
            if (coun == 10000)
            {
                cout<<"Could not allocate file sorry"<<endl;
                    continue;
            }

        }






        else if (ch == 2)
        {
            cout<<"Enter filename to delete"<<endl;
            cin>>s;
            if (files.empty())
            {
                cout<<"No file allocated in memory"<<endl;
                continue;
            }
            while (count(fname.begin(), fname.end(), s)==0)
            {
                cout<<"File does not exist - Enter file name again"<<endl;
                cin>>s;
            }
            vector <string> :: iterator it1;
            it1 = find(fname.begin(), fname.end(), s);
            int d = distance(fname.begin(), it1);
            int r = files[d].start;
            int rend1 = files[d].finish;
            cout<<r<<" "<<rend1<<endl;
            cout<<"BLOCKS DELETED"<<endl;
            for (int i = r; i<= rend1; i++)
            {
                cout<<i<<" ";
                allocated[i] = false;
            }
            cout<<endl;
            delete(&files[d]);
            delete(&fname[d]);
            pos--;
            fsz-=rend1-r+1;
        }





        /**else if (ch == 3)
        {
            string s1;
            if (files.empty() || files.size() == 1)
            {
                cout<<"File Join not possible"<<endl;
                continue;
            }
            cout<<"Enter filename 1 to join"<<endl;
            cin>>s;
           while (count(fname.begin(), fname.end(), s)==0)
            {
                cout<<"File does not exist - Enter file name again"<<endl;
                cin>>s;
            }
            cout<<"Enter filename 2 to join"<<endl;
            cin>>s1;
            while (count(fname.begin(), fname.end(), s)==0 || s1 == s)
            {
                cout<<"File does not exist or same files cannot be joined - Enter file name again"<<endl;
                cin>>s1;
            }

            vector <string> :: iterator it1;
            it1 = find(fname.begin(), fname.end(), s);
            int d = distance(fname.begin(), it1) - 1;
            int r = files[d].start;
            int rend1 = files[d].finish;
            for (int i = r; i<= rend1; i++)
                allocated[i] = false;
            pos--;
            delete(&files[d]);
            delete(&fname[d]);
        }*/




        else if (ch == 4)
        {
            string s1;
            if (files.empty())
            {
                cout<<"File Rename not possible"<<endl;
                continue;
            }
            cout<<"Enter filename to rename"<<endl;
            cin>>s;
            while (count(fname.begin(), fname.end(), s)==0)
            {
                cout<<"File does not exist - Enter file name again"<<endl;
                cin>>s;
            }
            cout<<"Enter new Filename"<<endl;
            cin>>s1;
            vector <string> :: iterator it1;
            it1 = find(fname.begin(), fname.end(), s);
            int d = distance(fname.begin(), it1);
            files[d].name = s1;
            fname[d] = s1;
            cout<<"Filename has been changed"<<endl;
        }


        else if (ch == 5)
        {
            cout<<"Total Blocks = 500"<<endl;
            cout<<"Blocks Allocated = "<<fsz<<endl;
            cout<<"Blocks Unallocated = "<<(500 - fsz)<<endl;
            cout<<"Total number of files = "<<files.size()<<endl;
            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 25; j++)
                {
                    if (allocated[i*25 + j])
                        cout<<"A"<<" ";
                    else
                        cout<<"U"<<" ";
                }
                cout<<endl;
            }
        }

    }
    return 0;
}
