#pragma once
#include <iostream>
#include "Edge.hh"
#include "EdgeLS.hh"

using namespace std;


class ListS{ // ListaSasiedztwa
  EdgeLS* head;
  EdgeLS* tail;

  public:
    ListS(){
      head = nullptr;
      tail = nullptr;
    }

    int length(){
      int length;
      EdgeLS* temp = head;
      if(temp == nullptr) return 0;
      for(length = 0; temp->getNext() != nullptr; ++length){
        temp = temp->getNext();
      }
      length++;
      return length;
    }

    void push(EdgeLS* newEdge){
    if(head == nullptr) {
      head = newEdge;
      tail = newEdge;
    }
    else{
      newEdge->setPrev(tail); 
      tail->setNext(newEdge);
      tail = newEdge;
    }
    }

      // wypisuje na ekran: wierzchołek_poczatkowy wierzchołek_koncowy waga 
    void printEdge(unsigned index){
      EdgeLS* temp = head;
      if(index > length() - 1)
        cout << "Zbyt duży index listy krawędzi, długość listy to: " << length() << endl;
      else{
      for(int i = 0; i < index; i++)
        temp = temp->getNext();
      cout << temp->getEdge()->getBeg()->getElement() << " ";
      cout << temp->getEdge()->getEnd()->getElement() << " " << temp->getEdge()->getWeight() << endl; 
      }
    }

  void printAll(){
    EdgeLS* temp = head;
    int length = this->length();
    for(int i = 0; i < length; i++){
      printEdge(i);
    }
  }

  void del(unsigned index){
    EdgeLS* temp = head;
    int length = this->length();
    if(length == 0)
      cout << "Lista krawedzi pusta nie można usunać elementu" << endl; 
    else{
    if(length == 1 && index == 0){
      delete temp;
      head = nullptr;
      tail = nullptr;
    }
    else{
    if(index < 0) 
      cout << "Ujemny index w funkcji del" << endl;
    else{
    if(index > length - 1)
      cout << "Zły index listy Krawędzi, rozmiar listy to: " << length << endl;
    else{
      if(length == 1){
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
  }

  void delLast(){
    del(length() - 1);
  }

  EdgeLS* getEdgeLS(int i){
    EdgeLS* temp = head;
    if(i < 0 || (i > length() - 1))
      cout << "Zły indeks przy funkcji getEdge" << endl;
    else
    for(int j = 0; j < i; j++)
      temp = temp->getNext();
    return temp;
  }
  
  EdgeLS* getTail(){
    return tail;
  }
};