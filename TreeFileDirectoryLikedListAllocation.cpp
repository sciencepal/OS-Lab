#include <iostream>

using namespace std;

template <class T> class LinkedList
{
public:
    struct Node
    {
        T n;
        Node *next,*prev;
    };
    Node *start,*present;
    int sizer;

    Node* createNewNode(T x)
    {
        Node *t = new Node();
        t->n = x;
        t->next=NULL;
        t->prev=NULL;
        return t;
    }
    LinkedList()
    {
        start = NULL;
        present = NULL;
        sizer = 0;
    }
    int size()
    {
        return sizer;
    }
    void push_back(T x)
    {
        if(start==NULL)
        {
            Node *t = createNewNode(x);
            start = t;
            present = t;
            sizer++;
        }
        else
        {
            Node *t = createNewNode(x);
            present->next = t;
            t->prev = present;
            present = t;
            sizer++;
        }
    }
    T operator[](int n)
    {
        if(n<sizer)
        {
            Node *t = start;
            while(n--)
                t=t->next;
            return t->n;
        }
        else
            cout<<"Error: index out of range!"<<endl;
    }
    Node* getPresent()
    {
        return present;
    }
    void remove(int n)
    {
        if(n<sizer-1 && n > 0)
        {
            Node *t = start;
            while(n--)
                t=t->next;
            t->prev->next=t->next;
            t->next->prev = t->prev;
            delete t;
            sizer--;
        }
        else if(n==0)
        {
            Node *t = start;
            start = start->next;
            start->prev = NULL;
            delete t;
        }
        else if(n==sizer-1)
        {
            pop_back();
        }
    }
    void remove(LinkedList<int>* n,int size)
    {
        Node *t = (Node*)n;
        Node *t1 = t->prev;
        while(size>0 && t->next!=NULL)
        {
            t = t->next;
            delete t->prev;
            size--;
        }
        if(t!=NULL)
        t1->next = t;
    }
    Node* getStart()
    {
        return start;
    }
    void pop_back()
    {
        Node *t = present;
        present = present->prev;
        present->next = NULL;
        delete t;
        sizer--;
    }
};

struct FAT
{
    FAT *next,*prev;
}*begin,*curr;

struct Directory;

struct File
{
    string name;
    int size;
    FAT* blockNumber;
    Directory *root;
};
struct Directory
{
    string name;
    LinkedList<File*> files;
    LinkedList<Directory*> subdirectories;
    Directory *root;
    int numberOfFiles;
    int numberOfSubdirectores;
};

void createNewDirectory(string name,Directory *r);
void listAllFiles(Directory *r);
void createNewFile(string name,Directory *r,int size);
FAT* allocateBlock(int size);
void deallocateBlock(FAT* f,int size);
void displayFAT(int s,bool f);
Directory *nd;
File *nf;

int main()
{
    begin = NULL;
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
            int size;
            cin>>input>>size;
            createNewFile(input,pwdp,size);
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
                    pwdp->subdirectories.remove(i);
                }
            }
            for(int i=0;i<pwdp->files.size();i++)
            {
                if(input==pwdp->files[i]->name)
                {
                    //deallocateBlock(pwdp->files[i]->blockNumber,pwdp->files[i]->size);
                    //pwdp->files[i]->name = "";
                    pwdp->files.remove(i);
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
        if(temp->name.length()>0){
            cout<<temp->name<<"\n";
        }
    }
    for(int i=0;i<r->files.size();i++)
    {
        File *temp = r->files[i];
        if(temp->name.length()>0){
            cout<<temp->name<<" "<<temp->size<<" bytes"<<endl;
            displayFAT(temp->size,false);
        }
    }
}

void createNewFile(string n,Directory *r,int size)
{
    File *f = new File();
    f->name = n;
    f->root = r->root;
    f->size = size;
    f->blockNumber = allocateBlock(size);
    if(f->blockNumber==NULL)
    {
        cout<<"Error: File creation failed! Not enough disk space!"<<endl;
        delete f;
        return;
    }
    r->numberOfFiles++;
    r->files.push_back(f);
}

FAT* allocateBlock(int size)
{
    if(begin==NULL)
    {
        begin = new FAT();
        begin->next = NULL;
        begin->prev = NULL;
        curr = begin;
    }
    FAT * ret;
    int res = size;
    while(size--)
    {
        FAT* t = new FAT();
        if(res-size == 0)
            ret = t;
        t->next = NULL;
        t->prev = curr;
        curr->next = t;
        curr = t;
    }
    return ret;
}

void deallocateBlock(FAT* n,int size)
{
    FAT *t = n;
    FAT *t1 = NULL;
    if(n->prev != NULL)
        t1 = n->prev;
    while(size--){
        t = t->next;
        delete t->prev;
    }
    if(t1 != NULL)
        t1->next = t;
}

void displayFAT(int size,bool flag)
{
    for(int i=0;i<size;i++)
    {
        cout<<"()<=>";
        if(i!=0 && i%10==0)
            cout<<endl;
    }
    if(flag)
        cout<<"!!"<<endl;
}
