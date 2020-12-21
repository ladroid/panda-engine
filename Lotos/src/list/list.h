//
// Created by Lado on 24/5/20.
//

#ifndef LOTOS_LIST_H
#define LOTOS_LIST_H

#include <iostream>
#include <string>
#include "../object/object.h"

struct node {
    int data;
    node* next;
};

class list: object {
private:
    node *head, *tail;
public:
    std::string getClass();
    list();
    list& createnode(int value);
    list& display();
    list& insert_start(int value);
    list& insert_position(int pos, int value);
    list& delete_first();
    list& delete_last();
    list& delete_position(int pos);
    bool find_elem(int data);
    list& size();
    list& clear();
    ~list();
    bool equals(list& obj);
    list& clone();
    std::string toString();

};

std::string list::getClass() {
    return "";
}

list::list() {
    head = nullptr;
    tail = nullptr;
}

list& list::createnode(int value) {
    node *temp = new node;
    temp->data = value;
    temp->next = nullptr;
    if(head == nullptr) {
        head = temp;
        tail = temp;
        temp = nullptr;
    } else {
        tail->next = temp;
        tail = temp;
    }
    return *this;
}

list& list::display() {
    node *temp = new node;
    temp = head;
    std::cout << "[ ";
    while (temp!=nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "]";
    std::cout << std::endl;
    return *this;
}

list& list::insert_start(int value) {
    node *temp=new node;
    temp->data=value;
    temp->next=head;
    head=temp;
    return *this;
}

list& list::insert_position(int pos, int value) {
    node *pre=new node;
    node *cur=new node;
    node *temp=new node;
    cur=head;
    for(int i=1;i<pos;i++) {
        pre=cur;
        cur=cur->next;
    }
    temp->data=value;
    pre->next=temp;
    temp->next=cur;
    return *this;
}

list& list::delete_first() {
    node *temp=new node;
    temp=head;
    head=head->next;
    delete temp;
    return *this;
}

list& list::delete_last() {
    node *current=new node;
    node *previous=new node;
    current=head;
    while(current->next!=NULL) {
        previous=current;
        current=current->next;
    }
    tail=previous;
    previous->next=NULL;
    delete current;
    return *this;
}

list& list::delete_position(int pos) {
    node *current=new node;
    node *previous=new node;
    current=head;
    for(int i=1;i<pos;i++) {
        previous=current;
        current=current->next;
    }
    previous->next=current->next;
    return *this;
}

bool list::find_elem(int data) {
    node *current = new node;
    current = head;
    if(current->data == data) {
        return true;
    }
    return false;
}

list& list::size() {
    int count = 0;
    node *current = new node;
    current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    std::cout << count << std::endl;
    return *this;
}

list& list::clear() {
    node *current = new node;
    node *next;
    while(current != nullptr) {
        next = current->next;
        free(current);
        current = next;
    }
    head = nullptr;
    return *this;
}

list::~list() { head = nullptr; tail = nullptr;}

bool list::equals(list &obj) {
    if (this == &obj) {
        return true;
    } else {
        return false;
    }
}

list& list::clone() {
    return *this;
}

std::string list::toString() {
    return typeid(list).name();
}

#endif //LOTOS_LIST_H
