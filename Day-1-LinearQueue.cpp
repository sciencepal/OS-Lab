#include <iostream>

using namespace std;

class CircularQueue
{
    struct Node
    {
        int n;
        Node *next,*prev;
    };
    Node *front,*end;
    Node* createNewNode(int x)
    {
        Node *t = new Node();
        t->n = x;
        t->next = t->prev =NULL;
    }

    void insertNewNode(Node* t)
    {
        if(front==end && end==NULL)
        {
            front = t;
            end = t;
        }
        else
        {
            t->next = end;
            end->prev = t;
            end = t;
            front->next=end;
        }
    }

    void deleteNode()
    {
        Node *temp = front;
        front = front->prev;
        delete temp;
    }
public:
    CircularQueue()
    {
        front = NULL;
        end = NULL;
    }
    void enqueue(int x)
    {
        insertNewNode(createNewNode(x));
    }
    void dequeue()
    {
        deleteNode();
    }
    void displayQueue()
    {
        Node *t = end;
        while(true)
        {
            cout<<t->n<<"->";
            if(t!=front)
            {
                t=t->next;
            }
            else
            {
                cout<<"!!!"<<endl;
                break;
            }
        }
    }
};

int main()
{
    CircularQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.displayQueue();
    q.dequeue();
    q.displayQueue();
    q.enqueue(5);
    q.displayQueue();
    q.dequeue();
    q.displayQueue();
    return 0;
}
