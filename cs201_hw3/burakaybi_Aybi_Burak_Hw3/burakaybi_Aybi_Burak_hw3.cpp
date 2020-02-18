#include "houselist.h"


int main() {

  HouseList house;
  cout<<"Please enter a filename.\n";
  string f;
  cin>>f;

  ifstream file;

  file.open(f.c_str());
  while(file.fail()) {
    cout<<"Can not open the file\n";
    cout<<"Please enter a filename.\n";
    cin>>f;
    file.open(f.c_str());
  }

  cout<<"Successfully opened the file " << f << endl<< endl;

  cout<<" ######## TOPOLOGY ######## \n\n";
  while(getline(file,f)) {

    istringstream streamer;

    streamer.str(f);
    string h,n;
    streamer>>h>>n;
    house.addPair(h,n);
    streamer.clear();
  }
  house.printAll();


  string option = "";

  while(option != "3") {
    cout<<"Please select an option [1-2-3].\n";
    cout<<"1. Annexation! War for the iron throne continues...\n";
    cout<<"2. Tyrion must travel, do a path check for the famous imp.\n";
    cout<<"3. Exit\n";
    cin>>option;
    if(option == "1")
    {
      string h,n;
      cout<<"Please enter two houses first the annexer and the annexed. (ex: Tyrell Stark).\n";
      cin>>h>>n;
      house.annexation(h,n);
    }
    else if(option == "2") {
      cout<<"Please enter a path. (ex: Tyrell Martell Tully)\n";
      string houses;
      cin.ignore();
      getline(cin,houses);
      house.stringcheck(houses);
    }
    else if(option == "3") {
      cout<<"List deleted program exited"<<endl;
    }
    else {
      cout<<"Invalid option please select from the menu.\n\n";
    }

  }
  return 0;
}