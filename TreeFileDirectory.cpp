#include <iostream>
#include <vector>

using namespace std;

struct Directory;

struct File
{
    string name;
    string size;
    Directory *root;
};
struct Directory
{
    string name;
    vector<File*> files;
    vector<Directory*> subdirectories;
    Directory *root;
    int numberOfFiles;
    int numberOfSubdirectores;
};

void createNewDirectory(string name,Directory *r);
void listAllFiles(Directory *r);
void createNewFile(string name,Directory *r);
Directory *nd;
File *nf;
int main()
{
    Directory *pwdp = new Directory();
    Directory *nullDirectory = new Directory();
    File *nullFile = new File();
    nd=nullDirectory;
    nf=nullFile;
    pwdp->name = "root";
    pwdp->files.push_back(nullFile);
    pwdp->subdirectories.push_back(nullDirectory);
    pwdp->numberOfFiles = 0;
    pwdp->numberOfSubdirectores = 0;
    pwdp->root = NULL;
    string command;
    string input;
    string pwd="root";
    while(true)
    {
        cout<<pwd<<">";
        cin>>command;
        if(command=="exit") break;
        if(command=="mkdir")
        {
            cin>>input;
            createNewDirectory(input,pwdp);
        }
        else if(command=="ls")
        {
            listAllFiles(pwdp);
        }
        else if(command == "nf")
        {
            cin>>input;
            createNewFile(input,pwdp);
        }
        else if(command == "cd")
        {
            cin>>input;
            if(input=="..")
            {
                pwdp = pwdp->root;
                int l = pwd.length();
                for(int i=l-1;i>=0;i--)
                {
                    if(pwd[i]=='/')
                    {
                        l = i;
                        break;
                    }
                }
                pwd = pwd.substr(0,l);
            }
            for(int i=0;i<pwdp->subdirectories.size();i++)
            {
                if(input==pwdp->subdirectories[i]->name)
                {
                    pwdp = pwdp->subdirectories[i];
                    pwd = pwd.append("/"+input);
                }
            }
        }
        else if(command == "rm")
        {
            cin>>input;
            for(int i=0;i<pwdp->subdirectories.size();i++)
            {
                if(input==pwdp->subdirectories[i]->name)
                {
                    pwdp->subdirectories[i]->name = "";
                }
            }
            for(int i=0;i<pwdp->files.size();i++)
            {
                if(input==pwdp->files[i]->name)
                {
                    pwdp->files[i]->name = "";
                }
            }
        }
        else if(command == "mv")
        {
            string n;
            cin>>input>>n;
            for(int i=0;i<pwdp->subdirectories.size();i++)
            {
                if(input==pwdp->subdirectories[i]->name)
                {
                    pwdp->subdirectories[i]->name = n;
                }
            }
            for(int i=0;i<pwdp->files.size();i++)
            {
                if(input==pwdp->files[i]->name)
                {
                    pwdp->files[i]->name = n;
                }
            }
        }
    }
    return 0;
}

void createNewDirectory(string n,Directory *r)
{
    Directory *temp = new Directory();
    temp->name = n;
    temp->files.push_back(nf);
    temp->numberOfFiles=temp->numberOfSubdirectores=0;
    temp->root = r;
    r->subdirectories.push_back(temp);
    r->numberOfSubdirectores++;
}

void listAllFiles(Directory *r)
{
    for(int i=0;i<r->subdirectories.size();i++)
    {
        Directory *temp = r->subdirectories[i];
        if(temp->name.length()>0)
            cout<<temp->name<<"\n";
    }
    for(int i=0;i<r->files.size();i++)
    {
        File *temp = r->files[i];
        if(temp->name.length()>0)
            cout<<temp->name<<" "<<temp->size<<" bytes"<<endl;
    }
}

void createNewFile(string n,Directory *r)
{
    File *f = new File();
    f->name = n;
    f->root = r->root;
    f->size = "0";
    r->numberOfFiles++;
    r->files.push_back(f);
}
