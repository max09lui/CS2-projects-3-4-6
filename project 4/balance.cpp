#include <iostream>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

bool isOpeningBrace(char c)
{
    if(c== '{' || c== '(' || c== '[')
    {
        return true;
    }
    else
    {
        return false; 
    }
}
bool isClosingBrace(char c)
{
    if(c== '}' || c== ')' || c== ']')
    {
        return true;
    }
    else
    {
        return false; 
    }
}
char reverse(char c)
{
    if(c== '}')
    {
        return '{';
    }
    if(c== ')')
    {
        return '(';
    }
    if(c== ']')
    {
        return '[';
    }
    return '*';
}

bool opensBlockComment(char* c)//do we have to use?
{
     if(*(c)=='/' && *(c+1) == '*')
     {
         return true;
     }

    return false;
}
bool closeBlockComment(char* c)//do we have to use?
{
     if(*(c)=='*' && *(c+1) == '/')
     {
         return true;
     }

    return false;
}

void printFile(istream &dictfile)
{
    string a;
    int linenum=1; 
    while(getline(dictfile, a))
    {
        cout<<linenum<<" "<<a<<endl; 
        linenum++;
    }
    dictfile.clear();
    dictfile.seekg(0, dictfile.beg);
    

}
bool balanceFile(istream &dictfile)
{
    dictfile.clear();
    dictfile.seekg(0, dictfile.beg);

    stack<char> balance;
    stack<int> LNbalance;
    
    string LINE;
    int linenum=1; 

    while(getline(dictfile, LINE))
    {
        //cout<<"Line number: "<<linenum<<endl;

        int linelength= LINE.length();
        for(int i=0; i< linelength; i++)
        {
            //cout<<LINE[i]<<endl;
            
            if(balance.empty() || balance.top()!= '*')// *: signifies block comment is on stack, no block comment able to take open/closing on stack
            {
                if(LINE[i]=='/' && LINE[i+1]== '*')// push * to signify for block comment
                {
                    //cout<<"block comment opened"<<endl;
                    balance.push('*'); 
                    LNbalance.push(linenum);
                }
                else if(LINE[i]=='*' && LINE[i+1]== '/')// closing block comment without an opener
                {
                    cout<<"unmatched"<<LINE[i]<<LINE[i+1]<<"symbol on line "<<linenum<<endl; 
                    return false;
                }
                else if(isOpeningBrace(LINE[i]))
                {
                    balance.push(LINE[i]);
                    LNbalance.push(linenum);
                }
                else if(isClosingBrace(LINE[i]))
                {
                    if(!balance.empty())
                    {
                        if(balance.top()== reverse(LINE[i]))
                        {
                            cout<<"pair matching "<<balance.top()<<" and "<<LINE[i]<<endl; 
                            balance.pop();
                            LNbalance.pop();
                        }
                        else
                        {
                            cout<<"unmatched"<<LINE[i]<<"symbol on line "<<linenum<<endl; 
                            return false;
                        }
                    }
                    else
                    {
                        cout<<"Close symbol: unmatched symbol on line "<<linenum<<endl;
                        return false;
                    }
                }
                else if(LINE[i]=='/')// blocks out whole line
                {
                    if(LINE[i+1]=='/')
                    {
                        cout<<"// matched"<<endl;
                        i=linelength;// i goes to end of the line thus skipping it
                    }
                    /*else
                    {
                        cout<<"unmatched symbol (/) on line "<<linenum<<endl;
                        return false;
                    }*/
                }
                else if(LINE[i]== '"')// ("") blocks out part of line
                {
                    balance.push('"');
                    LNbalance.push(linenum);

                    for(int j=i+1; j<linelength; j++)// starts one after so start quote wont be reread
                    {
                        //cout<<"* "<<LINE[j]<<endl;
                        if(LINE[j]== '"')
                        {
                            cout<<"pair matching \" and \""<<endl; 
                            balance.pop();
                            LNbalance.pop();
                            i=j;// i returns to the ends of the quotes, starts one after j so end quote wont be reread
                            break; //??? may need to set a j so next char can be read over when it loops
                        }
                    }
                }
                else if(LINE[i]== '\'')
                {
                    //cout<<"*\"** "<<LINE[i+2]<<" \'"<<endl;
                    if(LINE[i+2]== '\'')
                    {
                        cout<<"pair matching \' and \'"<<endl;
                        i+=2;// moves 2 over to other ' so i can shift to the next one when the for loop iterates 
                    }
                    else
                    {
                        cout<<"quotes (\') unmatched on line "<<linenum<<endl; 
                        return false; 
                    }
                }

            }
            else// (*) block comment opener is on stack signifing that block comment needs to be satisfied
            {
                if(LINE[i]=='*' && LINE[i+1]== '/')
                {
                    cout<<"pair matching /* and */ "<<endl; 
                    balance.pop();
                    LNbalance.pop();
                    i+=1;// move from block comment end so dont repeat a read
                    //??? may need to move only one away since i++ is done after the loop
                }
            }
            
        }
        
        linenum++;
    }

    if(!balance.empty())
    {
        cout<<"Open symbol: unmatched symbol on line "<<LNbalance.top()<<endl;
        return false;

    }

    return true;
}

int main()
{
    
    ifstream dictfile;         
    dictfile.open("text.txt");
    if (!dictfile)
    {
        cout << "File not found!" << endl;
        return (1);
    }
    
    //printFile(dictfile);

    //balanceFile(dictfile);
    if(balanceFile(dictfile))
    {
        cout<<"Balance is ok"<<endl;
    }
    else
    {
        cout<<"failed"<<endl;
    }


    /*ifstream infile;
    string filename;
    
    cout << "Please enter filename for C++ code: ";
    cin >> filename;
    infile.open(filename.c_str());

    if (!infile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    //printFile(infile);
    
    if (balanceFile(infile))
    {
        cout << "balance ok" << endl;
    }
    else
    {
        cout<<"failed"<<endl;
    }*/
        

}