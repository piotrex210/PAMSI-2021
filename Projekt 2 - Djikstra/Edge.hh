#pragma once

#define MIN 10  // min i max wagi gałęzi
#define MAX 20
#include "Vertex.hh"

class Edge
{
  protected:
  int weight;
  Edge* prev; // następna krawędź w liście krawędzi
  Edge* next; // poprzednia krawędź w liście krawędzi
  //Edge* prevLS; // używany do listy sąsiedztwa
  Vertex* beg;
  Vertex* end;
  int index;

  //int &refer; // referencja do pozycji w liście krawędzi
  public:
    Edge(Vertex* b, Vertex* e, const int elem){
      weight = elem;
      beg = b;
      end = e;
      prev = nullptr;
      next = nullptr;
      index = 0;
    }
    Edge(){
      weight = 0;
      beg = 0;
      end = 0;
      prev = nullptr;
      next = nullptr;
      index = 0;
    }

    int getWeight(){
      return weight;
    }

    Edge* getPrev(){
      return prev;
    }

    Edge* getNext(){
      return next;
    }

    Vertex* getBeg(){
      return beg;
    }

    Vertex* getEnd(){
      return end;
    }

    int getIndex(){
      return index;
    }

    void setIndex(int i){
      index = i;
    }

    void setWeight(int el){
      weight = el;
    }

    void setPrev(Edge* newe){ // newe = new element
      prev = newe;
    }

    void setNext(Edge* newe){
      next = newe;
    }

    void setBeg(Vertex* newe){
      beg = newe;
    }

    void setEnd(Vertex* newe){
      end = newe;
    }

    //~Edge();
  
  
};
