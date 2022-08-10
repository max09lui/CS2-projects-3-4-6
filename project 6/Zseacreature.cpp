#include <iostream>
#include <string>
using namespace std;

class SeaCreature//const= 0
{
public: 
    SeaCreature(string name)
    {
        cout<<"SeaCreature"<<name <<"is created"<<endl; 
        m_name= name;
        
        p= new int; 

    }
    ~SeaCreature()
    {
        cout<<"SeaCreature"<<m_name<<"is destroyed"<<endl; 
        delete p;
    }
    virtual void speak()=0;
    

    int InputAge(int n)
    {
        return n; 
    }

    string name()
    {
        return m_name; 
    }

private:
    string m_name; 
    int* p;
};

class fish : public SeaCreature
{
public:
    fish(string name)
    :SeaCreature(name)
    {
        cout<<"Fish "<<this->name()<<"is created"<<endl; 
        p2= new int; 
    }
    ~fish()
    {
        cout<<"Fish "<<this->name()<<"is destroyed"<<endl; 
        delete p2; 
    }
    void speak() override
    {
        cout<<"I am a Fish"<<endl; 
    }


private:
    int* p2;

};

int main()
{


    return 0;
}
