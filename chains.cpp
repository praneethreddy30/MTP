#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

//Function to check whether a given string is a number or not.
bool is_number(string &str, int n)
{
	int i=0;
	if(str[0]=='-' || str[0]=='+')
		i=1;
    for (;i<n;i++) 
        if (isdigit(str[i]) == 0)
            return false;
	
    return true;
}


//Function to print all chains.
void printChains(vector <vector <pair <int,int> > > chains)
{
        int i,j;
        for (i = 0; i < chains.size(); i++)
        {
                cout<<"Chain "<<i+1<<": ";

                for (j = 0; j < chains[i].size()-1; j++)
                        cout << chains[i][j].first << "-"<<chains[i][j].second << " < ";
                cout << chains[i][j].first << "-"<<chains[i][j].second<<endl;
        }
}


int main()
{
    vector <vector <pair <int,int> > > chains;
    vector <pair <int,int> > tempVec;
    pair <int,int> tempPair;
    int i,j,x,y,flag=0;
    string str;
    
    while(1)
    {
        //Reading input line
        getline(cin,str);

        //Stops taking inputs if we give the empty line
        if(str.empty())
            break;
	
        //Validating the Input (Input is valid only if we give 2 integers in all other cases input is Invalid)
        else
        {
	    vector<string> temp;
	    string word;
	    stringstream ss;

            ss << str;

            //Storing all strings in a line to a string array(temp)
            while(ss >> word)
                temp.push_back(word);
	    
            //Checking if only two strings are entered
            if(temp.size()!=2)
            {
                cout<<"Invalid input"<<endl;
                continue;
            }
	    
            else
            {
                j=0;

                //Checking if the strings are numbers
                for(auto itr : temp)
                {
                    if(!is_number(itr,itr.size()))
                    {
                        j++;
                        break;
                    }
                }
                if(j!=0)
                    continue;

                //Converting strings to numbers
                x=stoi(temp[0]), y=stoi(temp[1]);
            }
	    
        }
	
        //Checking if the interval is valid
        if(x>=y)
        {
            cout<<"Invalid Input"<<endl;
            continue;
        }
        
        //Checking each chain till we find the right position to insert the input interval
        else
        {
            flag=0;

            //Checking if we can enter the interval into any existing chains
            for (i = 0; i < chains.size(); i++)
            {
                //Checking if interval could be inserted at the begining of a chain
                if(y <= chains[i][0].first)
                {
		            tempPair.first=x;
		            tempPair.second=y;
                    chains[i].insert(chains[i].begin(), tempPair);
                    cout<<"("<<x<<","<<y<<") is inserted into Chain "<<i+1<<endl;
                    break;
                }

                //Finding right place to insert an interval in the chain
                for (j = 0; j < chains[i].size()-1; j++)
                {

                    if(chains[i][j].second<=x && y <= chains[i][j+1].first)
                    {
			            tempPair.first=x;
                    	tempPair.second=y;
                        chains[i].insert(chains[i].begin()+j+1 , tempPair);
                        flag=1;
                        cout<<"("<<x<<","<<y<<") is inserted into Chain "<<i+1<<endl;
                        break;
                    }
                }

                //Checking if interval can be inserted at the end of chain
                if(j==chains[i].size()-1 && chains[i][j].second<=x)
                {
		            tempPair.first=x;
                    tempPair.second=y;
                    chains[i].insert(chains[i].begin()+j+1 , tempPair);
                    flag=1;
                    cout<<"("<<x<<","<<y<<") is inserted into Chain "<<i+1<<endl;
                    break;
                }
                if(flag==1)
                    break;
            }
            
            //Starting a new chain if we can't insert the interval in any of the existing chains
            if(i==chains.size())
            {
                tempVec.clear();
                tempVec.push_back({});
 		        tempVec[0].first=x;
		        tempVec[0].second=y;
                chains.push_back(tempVec);
                cout<<"Chain "<<i+1<<" is created with ("<<x<<","<<y<<")"<<endl;
            }
        }
    }

    //Calls the function that prints all the chains.
    printChains(chains);
    
    return 0;
}

