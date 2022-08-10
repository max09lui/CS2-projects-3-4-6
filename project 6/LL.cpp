#include <iostream>
#include <string>
using namespace std;

typedef string ItemType;

struct Node 
{
    ItemType value;
    Node* next;
};

class LinkedList {
    
private:
    Node* head;
    
public:
    LinkedList()
        :head(nullptr)
    {
        
    }
    ~LinkedList()
    {
        Node* p = head;

        while(head!= nullptr)
        {
            p= head;
            head=head->next;
            
            delete p; 
        }

    }
    LinkedList(const LinkedList& rhs)
    {
        if(rhs.head == nullptr)
        {
            return; //list is empty, no need to copy
        }

        head= new Node;

        Node* p1= head;
        Node* p2= rhs.head; 

        head= new Node; 
        Node* temp; 

        while(p2!= nullptr)
        {
            cout<<p2->value<<endl;
            p1->value= p2->value; 
            temp= new Node; 

            p1=p1->next;
            p2=p2->next;

            p1=temp;
        }
        p1=nullptr;
        

    }
    void swap(LinkedList& rhs)
    {

        Node* temp= this->head; 

        this->head= rhs.head; 
        rhs.head= temp; 
        //rhs.head=nullptr; 
        
    }
    const LinkedList& operator=(const LinkedList& rhs)
    {
        if(this == &rhs)
        {
            return *this; // the same so no need to change
        }

        LinkedList temp(rhs);
        this->swap(temp);

        return *this;   
    }

    void insertToFront(ItemType	val)
    {
        
        Node* temp = new Node;
        
        temp->value = val;
        temp->next= head;
        head= temp;
        
    }
    void insertToRear(ItemType val)
    {
        Node* p= head;
        Node* temp= new Node;
        temp->value= val;
        temp->next=nullptr;

        while(p->next != nullptr)
        {
            p=p->next;
        }

        p->next= temp;
        
    }
    void print()
    {
        Node* p = head;
        
        while(p!= nullptr)
        {
            
            cout<<p->value<<endl;
            p=p->next; 
        }

    }
    Node* findLast()
    {
        Node* p= head;
        
        while(p->next!= nullptr)
        {
            p=p->next;
        }

        cout<<"last is "<<p->value<<endl;
        return p; 

    }
    Node* findSecondLast()
    {
        Node* p= head;
        
        while(p->next->next!= nullptr)
        {
            p=p->next;
        }

        cout<<"2nd last is "<<p->value<<endl;
        return p; 
    }
    void deleteItem(ItemType val)
    {
        if(this->head== nullptr)
        {
            return; //list is empty, nothing to delete
        }
        Node* p= head;
        Node* p2= head;

        if(p->value== val)
        {
            return; //item is in front 
        }
        
        p=p->next;

        while(p != nullptr)
        {
            if(p->value== val)
            {
                break; 
            }

            p2=p2->next;
            p=p->next;
        }

        if(p== nullptr)
        {
            cout<<"item not found"<<endl; 
            return;
        }

        //p2=p->next;
        p2->next=p->next;

        //delete p; 

    }
    void insertNItemsAtEnd(ItemType val, int n)
    {
        for(int i=1; i<=n; i++)
        {
            insertToRear(val);
        }
        
    }
    void insertNItemsAtFront(ItemType val, int n)
    {
        for(int i=1; i<=n; i++)
        {
            insertToFront(val);
        }
        
    }

};

int main()
{
    LinkedList list;
    list.insertToFront("1");
    list.insertToFront("2");
    list.insertToFront("3");
    
    LinkedList list2;
    list2.insertToFront("A");
    list2.insertToFront("B");
    list2.insertToFront("C");
    list2.insertToFront("D");
    
    
    list2.insertNItemsAtFront("AAA", 4);
    
    list2.print();


    return 0;
}