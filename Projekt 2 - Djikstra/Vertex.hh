#pragma once

#define INF 2147483647 // maksymalna wartosc intigera, przybliza nieskonczonosc

class Vertex {
    int element;
    Vertex* next; // wskaźnik na następny wierzchołek w liście
    Vertex* prev; // wskaxnik na poprzedni wierzchołek w liście
    Vertex* prevD; // wskaźnik na poprzedni wierzchołek w ścieżce z alg. Djikstry
    //int refer; // referencja do pozycji w liście krawędzi
    int distance;
    bool visited;

  public:

    Vertex(const int elem){
      element = elem;
      next = nullptr;
      prev = nullptr;
      visited = false;
      distance = INF; // INF
      prevD = nullptr;
      //refer = 0;
    }
    // ustawia wskaźnik na poprzedni element listy
    void setPrev(Vertex* p){
      prev = p;
    }
    // ustawia wskaźnik na następny element listy
    void setNext(Vertex* n){
      next = n;
    }
    // zwraca wskaźnik na poprzedni element
    Vertex* getPrev(){
      return prev;
    }
    // zwraca wskaźnik na następny element
    Vertex* getNext(){
      return next;
    }
    // zwraca element wierzchołka
    int getElement(){
      return element;
    }

    void setElement(int e){
      element = e;
    }

    void setDistance(unsigned d){
      distance = d;
    }

    int getDistance(){
      return distance;
    }

    void setVisit(bool state){
      visited = state;
    }

    bool isVisited(){
      return visited;
    }

    void setPrevD(Vertex* p){
      prevD = p;
    }

    Vertex* getPrevD(){
      return prevD;
    }


    //~Vertex();
};