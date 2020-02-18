#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct ListNode {

	string racer;
	unsigned lap_record;
	ListNode* next;

	ListNode(string racer, unsigned lap_record) {
		this->racer = racer;
		this->lap_record = lap_record;
		this->next = NULL;
	}

	void SetNext(ListNode* n) {
		next = n;
	}
	ListNode* Next() {
		return this->next;
	}

	ListNode* getPrevPlace(unsigned record) {
		if(this->Next() == NULL)
			return this;
		else {
			if(this->Next()->lap_record  <= record)
				return this->Next()->getPrevPlace(record);
			else
				return this;
		}
	}
};

struct LinkedList {

	LinkedList() {
		head = NULL;
	}
	~LinkedList() {
		//Deleting all the list here
		ListNode * ptr = head;
		while(head) {
			head = head->Next();
			delete ptr;
			ptr = head;
		}
		head = NULL;
	}

	void AddToList(string r, unsigned l) {
		if(head == NULL) {
			head = new ListNode(r,l);
		}
		else if(head->lap_record > l) {
			ListNode* newHead = new ListNode(r,l);
			newHead->next = head;
			head = newHead;
		}
		else {
			ListNode* place = head->getPrevPlace(l);
			ListNode* skipped = place->Next();
			place->next =  new ListNode(r,l);
			place->Next()->next = skipped;
		}

	}

	int getPosition(string r) {

		int i = 0;
		for (ListNode * temp = head; temp; temp = temp->Next())
		{
			if(temp->racer == r)
				return i;

			i++;
		}
		return -1;
	}

	unsigned getRecord(int pos) {
		ListNode* temp = head;
		for (int i = 0; i < pos; i++)
		{
			temp = temp->Next();
		}
		return temp->lap_record;
	}

	void UpdateList(string FullName, int prevPos, unsigned millis) {

		//check if we need to remove and update head
		if(prevPos == 0) {
			ListNode* tmp = head;
			head = head->next;
			delete tmp;
		}
		else {
			ListNode* tmp = head;
			for (int i = 0; i < (prevPos - 1); i++)
			{
				tmp = tmp->Next();
			}
			//Update the next one of the tmp pointer

			ListNode* temp = tmp->next; //will be removed

			ListNode* temp2 = temp->Next();
			delete temp;
			tmp->next = temp2;
		}
		AddToList(FullName,millis);
	}

	string PrintRank() {
		string res = "";
		res = "###############################\nResults:\n###############################\n";
		int i = 1;
		for (ListNode * temp = head; temp; temp = temp->Next())
		{
			res += to_string(i) + ". " + temp->racer + " " + to_string(temp->lap_record) + "\n"; 
			i++;
		}
		return res;
	}


	ListNode * head;

};
string getFileName() {
	string file;
	ifstream input;
	cout<<"Please enter a filename."<<endl;
	cin>>file;
	input.open(file);
	while(input.fail()) {
		cout<<"Unable to open file: "+ file <<endl;
		cout<<"Please enter a different file name."<<endl;
		cin>>file;
		input.open(file);
	}
	input.close(); //Close the successfully opened file

	cout<<"Successfully opened file "<<file<<endl;
	return file;
}

int main() {

	LinkedList list;

	ifstream input;
	input.open(getFileName());
	string line;

	cout<<"###############################\nQualifying Laps:\n###############################\n";
	while(getline(input,line)) {
		stringstream stream(line);

		string FullName;
		unsigned millis;
		stream >> FullName;
		stream >> millis;

		cout<<FullName<<"  completed the lap in "<<millis<<" milliseconds"<<endl;
		int prevPos = list.getPosition(FullName);
		if(prevPos == -1) {
			list.AddToList(FullName,millis);
			prevPos = list.getPosition(FullName);
			cout<<FullName<<": current personal best is "<<millis<<"; current position is "<<prevPos + 1<<endl;
		}
		else {
			int prevRec = list.getRecord(prevPos);
			if(prevRec > millis) {
				//That means update the list now
				list.UpdateList(FullName, prevPos, millis);
				prevPos = list.getPosition(FullName);
				cout<<FullName<<": current personal best is "<<millis<<"; current position is "<<prevPos + 1<<endl;

			}
			else {
			cout<<FullName<<": current personal best is "<<prevRec<<"; current position is "<<prevPos + 1<<endl;

			}
		}
		
	}

	string output = list.PrintRank();
	cout<<output<<endl;
	
	return 0;

}