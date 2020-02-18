#ifndef NEIGHBOR_H
#define NEIGHBOR_H
#include <iostream>
#include <string>
#include<sstream>
using namespace std;


class NeighborList {
public:
  NeighborList(string hname) {
    this->hname = hname;
    head = nullptr;
  }
  bool isExist(string h) {
    node * ptr = head;
    while(ptr) { 
      if(ptr->name == h) return true; 
      ptr = ptr->next;
    }
    return false;
  }
  bool update(string h1, string h2) {// update h1 either remove or change to h2
    if(!isExist(h1))
      return false;
    else {
      if ( head->name == h1) {
        if(isExist(h2)) {
          node * ptr = head->next;
          delete head;
          head = ptr;
        }
        else {
          head->name = h2;
        }
        return true;
      }
      node * ptr = head;
      while(ptr->next) { 
        if(ptr->next->name == h1)
        {
          if (isExist(h2)) {
            node * ptr2 = ptr->next->next;
            delete ptr->next;
            ptr->next = ptr2;
          }
          else {
            ptr->next->name = h2;
          }
          return true;
        }
        ptr= ptr->next;
      }
    }
  }


  void copyFrom(const NeighborList & n) {

    //first remove the n.hname from headslist
    if(head->name == n.hname) {
      node* ptr = head->next;
      delete head;
      head = ptr;
    } else {
      node* ptr2 = head;
      while(ptr2->next) {
        if(ptr2->next->name == n.hname)
          break;
        ptr2 = ptr2->next;
      }
      node*ptr = ptr2->next->next;
      delete ptr2->next;
      ptr2->next = ptr;
    }

    node * ptr = n.head;
    while(ptr) {
      if(!isExist(ptr->name) && ptr->name != this->hname)
      {
        if(!head)
        {
          head = new node(ptr->name);
        }
        else {
          node* ptr2 = head;
          while(ptr2->next) {
            ptr2 = ptr2->next;
          }
          ptr2->next = new node(ptr->name);
        }

      }
      ptr = ptr->next;
    }
  }

  bool addNeighbor(string n) {
    if (isExist(n))
      return false;
    node* ptr = head;
    if(!head)
      head = new node(n);
    else {
      while(ptr->next) {
        ptr = ptr->next;
      }
      ptr->next = new node(n);
    }
    return true;
  }
  void printList() {
    cout<<hname<<": ";
    node* ptr = head;
    while(ptr) {
      cout<<ptr->name<<", ";
      ptr = ptr->next;
    }
    cout<<endl;
  }
private:
  struct node {
    string name;
    node* next;
    node(string name) {
      this->name = name;
      next = NULL;
    }
  };
  node * head;
  string hname;

};

#endif