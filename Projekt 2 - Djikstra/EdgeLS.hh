#pragma once
#include <iostream>
#include "Edge.hh"


using namespace std;

class EdgeLS{
  Edge* edge;
  EdgeLS* prev;
  EdgeLS* next;
  public:
    EdgeLS(Edge* e){
      edge = e;
      prev = nullptr;
      next = nullptr;
    }
    EdgeLS* getPrev(){
      return prev;
    }

    EdgeLS* getNext(){
      return next;
    }

    Edge* getEdge(){
      return edge;
    }

    void setPrev(EdgeLS* newe){ // newe = new element
      prev = newe;
    }

    void setNext(EdgeLS* newe){
      next = newe;
    }

    void setEdge(Edge* e){
      edge = e;
    }

};

