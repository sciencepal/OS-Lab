#include <bits/stdc++.h>
using namespace std;

int cd = 0, ch;

struct folder
{
    int own;
    string name;
    int parent;
    int numfiles;
    vector <string> files;
    folder()
    {
        own = -1;
        name = "";
        parent = -1;
        numfiles = 0;
    }
}folders[10000];


void create_directory(string nam)
{
    if (folders[2*cd+1].own > -1 && folders[2*cd+2].own > -1)
    {
        printf("Directory is full\n");
        return;
    }
    if (folders[2*cd+1].own == -1)
    {
        folders[2*cd + 1].own = 2*cd + 1;
        folders[2*cd + 1].name = nam;
        folders[2*cd + 1].parent  = cd;
        printf("Directory Created\n");
        return;
    }
    else
    {
        folders[2*cd + 2].own = 2*cd + 2;
        folders[2*cd + 2].name = nam;
        folders[2*cd + 2].parent  = cd;
        printf("Directory Created\n");
        return;
    }
}


void move_to_directory(string filename, string directory)
{
    bool x = false;
    int idx = 0;
    for (int i = 0; i < folders[cd].numfiles; i++)
    {
        if (folders[cd].files[i] == filename)
        {
            idx = i;
            x= true;
            break;
        }
    }
    if (x == false)
    {
        printf("File not present.\n");
        return;
    }
    int temp1 = cd;
    int temp2 = cd;
    temp1 = 2*temp1 + 1;
    temp2 = 2*temp2 + 2;
    if (folders[temp1].name !=  directory && folders[temp2].name !=  directory)
    {
        printf("Folder not present.\n");
        return;
    }
    folders[cd].files.erase(folders[cd].files.begin()+idx);
    folders[cd].numfiles--;
    if (folders[temp1].name ==  directory)
    {
        folders[temp1].files.push_back(filename);
        folders[temp1].numfiles++;
        printf("File Moved.\n");
        return;
    }
    if (folders[temp2].name ==  directory)
    {
        folders[temp2].files.push_back(filename);
        folders[temp2].numfiles++;
        printf("File Moved.\n");
        return;
    }
}

void create_file(string filename)
{
    bool x = true;
    for (int i = 0; i < folders[cd].numfiles; i++)
    {
        if (folders[cd].files[i] == filename)
        {
            x= false;
            break;
        }
    }
    if (x == false)
    {
        printf("File already present.\n");
        return;
    }
    folders[cd].files.push_back(filename);
    folders[cd].numfiles++;
    printf("File Created.\n");
    return;
}

void go_to_directory(string directory)
{
    int temp1 = cd;
    int temp2 = cd;
    temp1 = 2*temp1 + 1;
    temp2 = 2*temp2 + 2;
    if (folders[temp1].name !=  directory && folders[temp2].name !=  directory)
    {
        printf("Folder not present.\n");
        return;
    }
    if (folders[temp1].name ==  directory)
    {
        cd = temp1;
        return;
    }
    if (folders[temp2].name ==  directory)
    {
        cd = temp2;
        return;
    }
}

void up()
{
    if (cd == 0)
    {
        printf("You are in root directory. Cannot go up!!!\n");
        return;
    }
    cd = (cd-1)/2;
}

void path()
{
    int temp = cd;
    stack <string> st;
    while (temp > 0)
    {
        st.push(folders[temp].name);
        temp = (temp - 1)/2;
    }
    st.push(folders[0].name);
    while (!st.empty())
    {
        string s = st.top();
        cout<<s;
        st.pop();
        if (!st.empty())
            cout<<" > ";
    }
    cout<<endl;
    return;
}

void show_files()
{
    for (int i = 0; i < folders[cd].numfiles; i++)
        cout<<folders[cd].files[i]<<endl;
    return;
}

void show_folders()
{
    if (folders[2*cd + 1].own != -1)
        cout<<folders[2*cd + 1].name<<" ";
    if (folders[2*cd + 2].own != -1)
        cout<<folders[2*cd + 2].name<<" ";
    if (folders[2*cd + 1].own == -1 && folders[2*cd + 2].own == -1)
        cout<<"No Sub Directories Present";
    cout<<endl;
    return;
}

int main()
{
    string s;
    puts("Enter the name of the root directory");
    cin>>s;
    folders[0].name = s;
    folders[0].own = 0;
    folders[0].parent = 0;
    cd = 0;
    while (true)
    {
        puts("");
        string fil, dir;
        puts("---------------- MENU ---------------");
        puts("1. Create Directory");
        puts("2. Move To Directory");
        puts("3. Go To Directory");
        puts("4. Create File");
        puts("5. Move One Directory Up");
        puts("6. Show Path To Root");
        puts("7. Show Files In Current Directory");
        puts("8. Show Folders In Current Directory");
        puts(" ------------------------------------ ");
        puts("");
        path();
        scanf("%d", &ch);
        if (ch == 1)
        {
            puts("Enter New Directory Name");
            cin>>dir;
            create_directory(dir);
        }
        else if (ch == 2)
        {
            puts("Enter File To Move");
            cin>>fil;
            puts("Enter Directory To Move To");
            cin>>dir;
            move_to_directory(fil, dir);
        }
        else if (ch == 3)
        {
            puts("Enter Directory Name");
            cin>>dir;
            go_to_directory(dir);
        }
        else if (ch == 4)
        {
            puts("Enter File Name");
            cin>>fil;
            create_file(fil);
        }
        else if (ch == 5)
        {
            up();
        }
        else if (ch == 6)
        {
            path();
        }
        else if (ch == 7)
        {
            show_files();
        }
        else
        {
            show_folders();
        }
    }
    return 0;
}
