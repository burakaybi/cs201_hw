//BURAK AYBI 20712

#include <iostream>
#include "DynIntStack.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;



int main()
{
	string file, line;
	cout<<"Please enter the file name that is going to be analyzed.\n" ;
	cin>>file;
	bool keywordcheck = false;// keyword varsa true yoksa false

	ifstream filename(file);

	while(filename.fail()) {// file acilmazsa
		cout<<"Unable to open file please enter a different file name.\n";
		cin>>file;
		filename.open(file.c_str());
	}
	DynIntStack mystack;// olusturdugum stack

	mystack.push(0); // 0 pushladim

	cout<<"Starting file analysis...\n";

	cout<<"Initial indentation level is pushed to the stack as 0.\n";

	int linenumber=1;
	int stacknumber; 
	
	while (getline(filename, line))//reading line by line
	{
		

		cout<<"Line number: "<<linenumber<<endl;
		cout<<"Line: "<<line<<endl;
		char ch;
		int a=0;
		istringstream str(line);
		
		while(str.get(ch)) //bosluklari bulmak icin
		{
			if(ch==' ')
				a++;
			else
				break;
		}
		
		

		mystack.pop(stacknumber); //stackten cikar
		mystack.push(stacknumber);// stacke ekle
		cout<<a<<" number of spaces observed before the start of the line.\n";

		cout<<"Current Level = "<< stacknumber<<" This Line = "<<a<<endl;
		/*	
		
		KEYWORD VE LINE  CHECK 

		*/
		
		if( a > stacknumber && keywordcheck==true)
		{
			mystack.pop(stacknumber);
			mystack.push(stacknumber);
			cout<<"Line correct. Depth "<< a<< " added to the stack.\n";
		}
		else if(keywordcheck==true && a<=stacknumber)
		{
			mystack.pop(stacknumber);
			mystack.push(stacknumber);
			while(!mystack.isEmpty())
			{
				mystack.pop(stacknumber);
			}
			
			cout<<"Incorrect file structure.\n Current line must be greater than the Current indentation level.\n Stopping file analysis...\n Stack emptied and program ending.\n";
			return 0;
		}
		else if(keywordcheck==false&& stacknumber>a)
		{
			mystack.pop(stacknumber);
			mystack.push(stacknumber);
			cout<<"Current line is smaller than Current indentation level; checking if line belongs to outer indentation.\n";
		}
		else if(keywordcheck==false && stacknumber<a)
		{
			mystack.pop(stacknumber);
			mystack.push(stacknumber);
			cout<<"Incorrect file structure.\n";
			cout<<"Current line cannot be greater than the Current indentation level.\n";
			while(!mystack.isEmpty())
			{
				mystack.pop(stacknumber);
			}
			
			cout<<"Stopping file analysis...\n";
			cout<<endl;
			cout<<"Stack emptied and program ending.\n";
			return 0;
		}
		else if(keywordcheck==false&& stacknumber==a)
		{
			mystack.pop(stacknumber);
			mystack.push(stacknumber);
			cout<<"Line belongs to current block.\n";
		}

		//KEYWORD BELIRLEME
		
		if (string::npos != line.find("while"))
        {
            cout<<"Keyword while found on this line.\n";
			keywordcheck=true;
        }
		else if (string::npos != line.find("if"))
        {
            cout<<"Keyword if found on this line.\n";
			keywordcheck=true;
        }
		else if (string::npos != line.find("else"))
        {
            cout<<"Keyword else found on this line.\n";
			keywordcheck=true;
        }
		else if (string::npos != line.find("elif"))
        {
            cout<<"Keyword elif found on this line.\n";
			keywordcheck=true;

        }
		else if (string::npos != line.find("for"))
        {
            cout<<"Keyword for found on this line.\n";
			keywordcheck=true;
        }

		else 
			keywordcheck=false;
	
		linenumber++;
	}

	//STACKI SILME
	while(!mystack.isEmpty())
	{
		mystack.pop(stacknumber);
	}
	
	cout<<"Finished file analysis. File structure is correct!\n";
	cout<<"Stack emptied and program ending.\n";
	
	return 0;
}