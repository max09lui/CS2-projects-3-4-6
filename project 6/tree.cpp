#include <iostream>
#include <string>
using namespace std;

typedef string ItemType;

struct WordNode {
    ItemType m_data;
    int freq; 
    WordNode *m_left;
    WordNode *m_right;
    // You may add additional data members and member functions in WordNode
};

class WordTree {
    
private:
    WordNode* root;
    void FindNodeBTW(WordNode* &p, ItemType v)// cases: no node and node created
    {
        //cout<<"***"<<endl;

        

        if(p->m_left== nullptr && v < p->m_data)
        {
            p->m_left= new WordNode;
            
            p->m_left->m_data=v;
            p->m_left->freq=1;
            p->m_left->m_left= nullptr;
            p->m_left->m_right= nullptr;

            return; 

        }
        else if(p->m_right== nullptr && v > p->m_data)
        {
            p->m_right= new WordNode;
            
            p->m_right->m_data=v;
            p->m_right->freq=1;
            p->m_right->m_left= nullptr;
            p->m_right->m_right= nullptr;

            return; 

        }
        else if(v== p->m_data)
        {
            p->freq++;
            return; 
        }

        if(v > p->m_data)
        {
            FindNodeBTW(p->m_right, v);
        }
        else if(v < p->m_data)
        {
            FindNodeBTW(p->m_left, v);
        }
        
        
    }
    void PrintTree(WordNode* p)//cout<<"*** "<<p->m_data<<endl;
    {
        //cout<<"p: "<<p<<endl; 
        if (p == nullptr)
        {
            return;
        }
            
        PrintTree(p->m_left);
        //cout << p->m_data << " ";
        cout << p->m_data << " #"<<p->freq<<" | ";
        PrintTree(p->m_right);

    }
    
    void TreeCC(WordNode* p)
    {
        //cout<<"AAA"<<endl;
        if (p == nullptr)
        {
            return;
        }

        //cout << p->m_data << " #"<<p->freq<<" | ";  
        
        this->addWfreq(root, p->m_data, p->freq);
        
        TreeCC(p->m_left);
        
        TreeCC(p->m_right);
    }

    void addWfreq(WordNode* p, ItemType v, int FREQ)
    {
        if(p->m_left== nullptr && v < p->m_data)
        {
            p->m_left= new WordNode;
            
            p->m_left->m_data=v;
            p->m_left->freq=FREQ;
            p->m_left->m_left= nullptr;
            p->m_left->m_right= nullptr;

            return; 

        }
        else if(p->m_right== nullptr && v > p->m_data)
        {
            p->m_right= new WordNode;
            
            p->m_right->m_data=v;
            p->m_right->freq=FREQ;
            p->m_right->m_left= nullptr;
            p->m_right->m_right= nullptr;

            return; 

        }
        /*else if(v== p->m_data)
        {
            p->freq++;
            return; 
        }*/

        if(v > p->m_data)
        {
            addWfreq(p->m_right, v, FREQ);
        }
        else if(v < p->m_data)
        {
            addWfreq(p->m_left, v, FREQ);
        }
    }

    void NodeDeletion(WordNode* p)
    {
        //cout<<"***"<<endl; 
        if (p == nullptr)
        {
            return;
        }
            
        NodeDeletion(p->m_left);
        delete p;
        NodeDeletion(p->m_right);

    }
    int distinctWordsCounter(WordNode* p) const
    {
        
        if(p== nullptr) //no node
        {
            return 0; 
        }
        //cout<<p->m_data<<endl; 

        if (p->m_left == nullptr && p->m_right== nullptr) //single node
        {
            return 1;
        }

        return 1+distinctWordsCounter(p->m_left)+distinctWordsCounter(p->m_right);

        //cout<<p->m_data<<endl;

    }
    int totalWordsCounter(WordNode* p) const
    {
        
        if(p== nullptr) //no node
        {
            return 0; 
        }
        
        if (p->m_left == nullptr && p->m_right== nullptr) //single node
        {
            return p->freq;
        }

        return p->freq+totalWordsCounter(p->m_left)+totalWordsCounter(p->m_right);

        //cout<<p->m_data<<endl;
        return 0;

    }
    void swap(WordTree& rhs)
    {
        WordNode* temp= this->root; 

        this->root= rhs.root;
        rhs.root= temp;

    }

public:

        // default constructor            
    WordTree() : root(nullptr) { };

        // copy constructor
    WordTree(const WordTree& rhs);

        // assignment operator
    const WordTree& operator=(const WordTree& rhs);  

        // Inserts v into the WordTree    
    void add(ItemType v);

        // Returns the number of distince words / nodes   
    int distinctWords() const;

        // Returns the total number of words inserted, including duplicate
        // values    
    int totalWords() const;

        // Prints the LinkedList 
    friend ostream& operator<<(ostream &out, const WordTree& rhs);

        // Destroys all the dynamically allocated memory
        // in the tree.
    ~WordTree();

    void print()
    {
        PrintTree(root);
        cout<<endl; 
    }
    
    
};

void WordTree::add(ItemType v)
{

    if(root== nullptr)//if tree is empty
    {
        root= new WordNode;
        root->m_data=v;
        root->freq=1;
        root->m_left= nullptr;
        root->m_right= nullptr;

        return;
    }

    WordNode* p= root;

    FindNodeBTW(p, v);

}

WordTree::~WordTree()
{
    NodeDeletion(root);
}

int WordTree::distinctWords() const
{

    return distinctWordsCounter(root);
}

int WordTree::totalWords() const
{
    //return 10; 
    return totalWordsCounter(root);
}

WordTree::WordTree(const WordTree& rhs)
{
    if(rhs.root== nullptr)
    {
        return; 
    }
    else
    {
        root= new WordNode;
        root->m_data= rhs.root->m_data;
        root->freq= rhs.root->freq;
        root->m_left= nullptr;
        root->m_right= nullptr;

        TreeCC(rhs.root);

    }
    
    
}

const WordTree& WordTree::operator=(const WordTree& rhs)
{
    if(this == &rhs)
    {
        return *this; // the same so no need to change
    }

    WordTree temp(rhs);
    this->swap(temp);

    return *this;   
}

void PrintTree2(WordNode* p, string& out)//cout<<"*** "<<p->m_data<<endl;
{
    
    
    //cout<<"p: "<<p<<endl; 
    if (p == nullptr)
    {
        return;
    }
        
    PrintTree2(p->m_left, out);
    
    //cout << p->m_data << " #"<<p->freq<<" | ";
    out+=p->m_data+" "+ to_string(p->freq)+"\n";
    PrintTree2(p->m_right, out);

}

ostream& operator<<(ostream &out, const WordTree& rhs)
{
    string a="";
    //PrintTree2(root, a);
    //PrintTree(root);
    
    //cout<<rhs.root<<endl; 

    PrintTree2(rhs.root, a);

    out<<a;

    return out;
}

int main()
{

    WordTree t;
    
    t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Hank");
    t.add("Gus");
    t.add("Walter");
    t.add("Gus");

    cout << t;



    return 0;
}
