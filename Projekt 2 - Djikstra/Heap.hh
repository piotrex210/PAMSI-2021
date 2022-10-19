#pragma once

#include "Edge.hh"
#include <iostream>

using namespace std;

class Heap{
  Vertex* tab[1000];
  int n;
  //Edge* x;

  public:
    Heap(){
      n = 0;
      //x = nullptr;
      for(int i = 0; i < 1000; i++)
        tab[i] = nullptr;
    }

    int length(){
      return n;
    }

    void push(Vertex* x){
      int i, j;
      i = n;
      n++;
      j = (i-1)/2;
      
      while(i > 0 && tab[j]->getDistance() > x->getDistance()){
        tab[i] = tab[j];
        i = j;
        j = (i-1)/2;
      }
      tab[i] = x;
    }

    Vertex* pop(){
      int i, j;
      Vertex* x;
      if(n <= 0) return nullptr;
      Vertex* min = tab[0];
      n--;
      x = tab[n];
      i = 0;
      j = 1;
      while(j < n){
        if((j + 1 < n) && (tab[j + 1]->getDistance() < tab[j]->getDistance())) j++;
        if(x->getDistance() <= tab[j]->getDistance()) break;
        tab[i] = tab[j];
        i = j;
        j = 2*j + 1;
      }
      tab[i] = x;
      return min;
    }
    void printHeap(){
      for(int i = 0; i < n; i++){
        cout << tab[i]->getDistance() << '\t';
      }
    }

    void cleanHeap(){
      for(int i = 0; i < n; i++)
        pop();
    }
};