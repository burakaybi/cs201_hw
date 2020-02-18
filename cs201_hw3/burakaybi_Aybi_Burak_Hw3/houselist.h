#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "neighborList.h"
using namespace std;


struct Node {
  string name;
  Node * next;
  NeighborList list;
  Node (string name) :list(NeighborList(name)) {
    this->name = name;
    next = NULL;
  }
};

class HouseList {
public:
  HouseList() {
    head = NULL;
  }
  bool addPair(string h1, string h2) {
    cout<< "Processing " << h1 << ", " << h2 <<endl;
    addHouse(h1);
    addHouse(h2);
    Node* ptr1 = isExist(h1);
    if( ptr1->list.isExist(h2)) {
      cout<<"Redundant Information, " << h1 << ", "<< h2 << " already added!"<<endl<<endl;
      return false;
    }
    ptr1->list.addNeighbor(h2); 
    isExist(h2)->list.addNeighbor(h1);
    cout<<"Topology successfully added."<<endl<<endl;
    return true;
  }
  bool addHouse(string h1) {
    if(isExist(h1) == NULL) {
      if(!head)
        head = new Node(h1);
      else {
        Node * ptr = head;
        while(ptr->next) {
          ptr = ptr->next;
        }
        ptr->next = new Node(h1);
      }
      return true;
    }
    return false;
  }

  void annexation(string h1, string h2) {
    if(isExist(h1) == false) {
      cout<<h1 << " does not exist!"<<endl;
      cout<<"Update failed"<<endl;
      return;
    }
    else if( isExist(h2) == false) {
      cout<<h2 << " does not exist!"<<endl;
      cout<<"Update failed"<<endl;
      return;
    }
    else if(h1 == h2) {
      cout<<"House can not conquer itself!\nUpdate failed"<<endl;
      return;
    }
    else {
      Node *ptr = isExist(h1);
      Node *ptr2 = isExist(h2);
      if(ptr->list.isExist(h2)) {
        cout<<h1  << " counquered " << h2 << endl;
        ptr->list.copyFrom(ptr2->list);
        //remove the h2 from all
        ptr = head;
        while(ptr)
        {
          ptr->list.update(h2,h1);
          ptr = ptr->next;
        }
      }
      else {
        cout<<h2<< " is not a neighbor of " << h1<<endl;
        cout<<"Update failed"<<endl;
        return;
      }

      //remove the h2 from the houselinkedlist
      if(head->name == h2) {
        Node * ptr = head->next;
        delete head;
        head = ptr;
      }
      else {
        Node * ptr = head;
        while(ptr->next) {
          if(ptr->next->name == h2)
            break;
          ptr = ptr->next;
        }
        Node* ptr2 = ptr->next->next;
        delete ptr->next;
        ptr->next = ptr2;

      }
      printAll();
    }
  }
  void stringcheck(string str) {
    istringstream iss(str);
    string h,n;
    iss>>h;
    Node* ptr;
    Node* ptr2;
    while(iss>>n) {
      ptr = isExist(h);
      if (ptr == NULL) {
        cout<<h << " does not exist in the map!"<<endl;
        cout<<"Path search Failed!"<<endl<<endl;
        return;
      }
      if ( h == n) {
        cout<<"You already in the "<<h << endl;
      }
      else if(ptr->list.isExist(n)) {
        cout<<"Path found between " << h << " and " << n << endl;
      }
      else {
        cout<<n << " is not a neighbor of " << h << endl;
        cout<<"Path search Failed!"<<endl<<endl;
        return;
      }
      h = n;
    }
    cout<<"Path succeeded"<<endl<<endl;
  }

  Node * isExist(string h1) {
    Node * ptr = head;
    while(ptr) {
      if(ptr->name == h1)
        return ptr;
      ptr = ptr->next;
    }
    return NULL;
  }
  void printAll() {
    cout<<" ######## MAP ######## \n\n";
    Node * ptr = head;
    while(ptr) {
      ptr->list.printList();
      ptr = ptr->next;
    }
  }
private:
  Node * head;
};

#endif