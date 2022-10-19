#pragma once

#include "Vertex.hh"
#include <iostream>

using namespace std;

struct ListVertex {
  Vertex* head;
  Vertex* tail;

  // konstruktor
  ListVertex(){
    head = nullptr;
    tail = nullptr;
  }

  // dodaje nowy element listy
  void push(Vertex* newVert){
    if(head == nullptr) {
      head = newVert;
      tail = newVert;
    }
    else{
      newVert->setPrev(tail); 
      tail->setNext(newVert);
      tail = newVert;
    }
  }

  int length(){
    int length;
    Vertex* temp = head;
    if(temp == nullptr) return 0;
    else{
    for(length = 0; temp->getNext() != nullptr; ++length){
      temp = temp->getNext();
    }
    length++;
    return length;
    }
  }
  

  Vertex* getVertex(int i){
    Vertex* temp = head;
    if(i < 0 || i > length() - 1)
      cout << "Zły indeks przy funkcji getVertex" << endl;
    else
    for(int j = 0; j < i; j++)
      temp = temp->getNext();
    return temp;
  }

  void del(unsigned index){
    Vertex* temp = head;
    unsigned int length = this->length();
    if(length == 0)
      cout << "Lista wierzcholkow pusta nie można usunać elementu" << endl; 
    else{
    if(length == 1 && index == 0){
      delete temp;
      head = nullptr;
      tail = nullptr;
    }
    else{
    if(index < 0) 
      cout << "Ujemny index w funkcji del" << endl;
    else
    if(index > length - 1)
      cout << "Zły index listy Vektorów, rozmiar listy to: " << length << endl;
    else{
      if(length == 1 && index == 0){
        delete temp;
        head = nullptr;
        tail = nullptr;
      }
      else{
        if(index == 0){ // jeśli usówamy pierwszy element
          head = head->getNext();
          delete temp;
        }
        else{
          // dojście do elementu o indeksie index
          int i;
          for(i = 0; i < index; i++)
              temp = temp->getNext();
          
          if(index == length - 1){ // jeśli usówamy ostatni element listy
            temp->getPrev()->setNext(nullptr);
            tail = temp->getPrev();
            delete temp;
          }
          else{ // jeśli nie jesteśmy na początku ani na końcu listy
            temp->getNext()->setPrev(temp->getPrev());
            temp->getPrev()->setNext(temp->getNext());
            delete temp;
          }
        }
      }
    }
    }
    }
  }

  void delLast(){
    del(length() - 1);
  }

  Vertex* getLast(){
    return tail;
  }

  void printVertex(unsigned index){
    Vertex* temp = head;
    if(index > length() - 1)
      cout << "Zbyt duży index listy wierzchołków, długość listy to: " << length() << endl;
    else{
    for(int i = 0; i < index; i++)
      temp = temp->getNext();
    cout << temp->getElement() << endl; 
    }
  }

  void printAll(){
    Vertex* temp = head;
    int length = this->length();
    for(int i = 0; i < length; i++){
      cout << temp->getElement() << endl;
      temp = temp->getNext();
    }
  }
  // zakładamy, że kolejne wierzchołki są nazywane i dodawane od 0 i są ustawione pokolei 
  bool elementExist(unsigned element){
      return (element < length() && element >= 0);
  }


};

