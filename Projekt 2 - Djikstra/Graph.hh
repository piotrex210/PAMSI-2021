#pragma once

#include "Vertex.hh"
#include "Edge.hh"
#include "ListS.hh"
#include "EdgeLS.hh"
#include "ListVertex.hh"
#include "Heap.hh"

#define INF 2147483647 // maksymalna wartosc intigera, przybliza nieskonczonosc

#include <iostream>
#include <iomanip>

class Graph{
  
  unsigned v; // ilosc wierzcholkow
  unsigned e; // ilosc krawedzi
  Edge ***M; // Macierz sąsiedztwa
  ListS** LS; // Tablica wskaźników na listy sąsiedztwa
  //Heap* heap;

  int* endvertecies = new int[2];
  ListVertex* V;
  ListEdge *E;

  public:

    void insertEdge(int p, int n, int weight){ // weight - waga
      int length = V->length();
      if(p > length - 1 || n > length -1)
        cout << "Zły indeks przy dodawaniu krawędzi do Grafu!" << endl;
      // if(!edgeExist)   
      E->push(new Edge(V->getVertex(p), V->getVertex(n), weight));
    }

    Graph(int vert, int edge, ListVertex* lv, ListEdge* le, bool isSourceFile, int density){
      // pobranie informacji na temat ilości wierzchołków i krawędzi
      v = vert;
      e = edge;

      V = lv;
      E = le;

      LS = new ListS*[v];
      
      for(int i = 0; i < v; i++){
        LS[i] = new ListS;
      }

      M = new Edge**[v];

      // dodaje do listy v Wierzchołków ponumerowanych od 0 do v-1 po kolei
      for(int i = 0; i < v; i++){
        V->push(new Vertex(i));
      }

      for(int i = 0; i < v; i++){
        M[i] = new Edge*[v]; // rezerwacja pamięci na każdy wiersz o długości "v"
        for(int j = 0; j < v; j++){
          M[i][j] = nullptr;  // wypełnienie macierzy zerami
        }
      }

      int x, y;
      if(!isSourceFile){
        // wstawienie losowych krawędzi
        //if(density != 100)
          for(int i = 0; i < e; i++)
          {
            x = rand() % v;
            y = rand() % v;
            while(x == y || M[x][y] != nullptr){
              x = rand() % v;
              y = rand() % v;
            }
            insertEdge(x, y, rand() % MAX+1 + MIN);
            M[x][y] = E->getTail();
            }
      }
      else{      }
      setLS();
      setMatrix();
      }
    
    ~Graph(){
      deleteM();
      deleteLS();
      deleteE();
      deleteV();
      delete endvertecies;
    }

    void deleteM(){
      // zwalnia pamięć rezerwowaną dla macierzy sąsiedztwa
      for(int i = 0; i < v; i++)
        delete[] M[i];
      delete[] M; 
    }

    void deleteLS(){
      for(int i = 0; i < v; i++){
        int length = LS[i]->length(); // dłg listy sąsiedztwa
        for(int j = 0; j < length; j++){
          LS[i]->del(0);
        }
        delete LS[i];
      }
      delete LS;
    }

    void deleteE(){
      int Elength = E->length();
      for(int i = 0; i < Elength; i++){
        E->del(0);
      }
    }

    void deleteV(){
      int Vlength = V->length();
      for(int i = 0; i < Vlength; i++){
        V->del(0);
      }
    }

    void insertVertex(int element){
      V->push(new Vertex(element));
    }

    void setMatrix(){
      int length = E->length();
      int x,y;
      Edge* temp = E->getTail();
      for(int i = 0; i < length; i++){
        x = temp->getBeg()->getElement();
        y = temp->getEnd()->getElement();
        M[x][y] = temp;
        temp = temp->getPrev();
      }
    }
    // tworzy listy sąsiedztwa dla każdego wierzchołka zgodnie z listą krawędzi
    void setLS(){
      int length = E->length();
      int beg;
      Edge* temp;
      for(int i = 0; i < length; i++){
        temp = E->getEdge(i);
        beg = temp->getBeg()->getElement();
        LS[beg]->push(new EdgeLS(temp));
      }
    }


    void removeEdge(unsigned i){
      E->del(i);
    }

    void removeVertex(int v){
      int length = V->length();
      if(v > length -1)
        cout << "Zły indeks przy usówaniu wierzchołka w funkcji Graph::removeVertex" << endl;
      else {
        // w tym meijscu USUŃ WSZYSTKIE PRZYLEGAJACE KRAWEDZIE
        
        V->del(v);
      }
    }

    void vertices(){
      V->printAll();
    }

    void edges(){
      E->printAll();
    }

    int* endVertices(unsigned edge){
      if(edge > E->length() - 1){
        cout << " Graph :: endVertices - wyjście poza listę krawędzi!" << endl;
        endvertecies[0] = 0;
        endvertecies[1] = 0;
      }
      else{
        endvertecies[0] = E->getEdge(edge)->getBeg()->getElement();
        endvertecies[1] = E->getEdge(edge)->getEnd()->getElement();
        return endvertecies;
      }
    }

    int opposite(int v, int e){
      if(E->getEdge(e)->getBeg()->getElement() == v)
        return E->getEdge(e)->getEnd()->getElement();
      else 
        return E->getEdge(e)->getBeg()->getElement();
    }


    void printMatrix(){
      // wyswietlanie tablicy
      for(int i = 0; i < v; i++)
      {
      for(int j = 0; j < v; j++)
      {
        if(M[i][j] == nullptr)
          cout << setw(4) <<  "-1";
        else
          cout << setw(4) << M[i][j]->getWeight();

      }
      cout << endl;
      }
    }

    void fillGraphByMatrix(){
        // wstawianie krawędzi zgodnie z macierzą sąsiedztwa

      for(int i = 0; i < v; i++){
        for(int j = 0; j < i; j++){ // sprawdza tylko dolną/lewą część macierzy, 
        // żeby nie dodawać jednej krawędzi 2 razy
          if(M[i][j]) insertEdge(i, j, rand() % 11);
        }
      }
    }


  ListVertex* doDjikstra(int start){
    Heap heap;
    ListVertex* tab = V;
    Vertex* temp;
    for(int i = 0; i < v; i++){
      temp = tab->getVertex(i);
      if(i == start) temp->setDistance(0);
      else temp->setDistance(INF);
      temp->setVisit(false);
      temp->setPrevD(nullptr); 
    }
    int u = start;
    
    while(u != -1){
      tab->getVertex(u)->setVisit(true);
      for(int i = 0; i < v; i++){
        if(M[u][i] != nullptr && tab->getVertex(u)->getDistance() + M[u][i]->getWeight() < tab->getVertex(i)->getDistance()){
          tab->getVertex(i)->setDistance(tab->getVertex(u)->getDistance() + M[u][i]->getWeight());
          tab->getVertex(i)->setPrevD(tab->getVertex(u));
          heap.push(tab->getVertex(i));
        }
      }
      if(heap.length())
        u = heap.pop()->getElement();
      else u = -1;
    }
    return tab;
   }


    // algorytm Djikstry przy użyciu listy sąsiedztwa
    ListVertex* doDjikstraLS(int start){
      Heap heap;
      ListVertex* tab = V;
      Vertex* temp;
      for(int i = 0; i < v; i++){
        temp = tab->getVertex(i);
        if(i == start) temp->setDistance(0);
        else temp->setDistance(INF);
        temp->setVisit(false);
        temp->setPrevD(nullptr); 
      }
     
      int  u = start;
      int lengthU;
      Vertex* beg, *end;

      while(u != -1){
        lengthU = LS[u]->length(); // długość listy sąsiedztwa wierzchołka u
        Edge* edgeTemp;
        beg = V->getVertex(u);
        beg->setVisit(true);
        for(int i = 0; i < lengthU; i++){ // przez całą listę sąsiedztwa wierzchołka End
          edgeTemp = LS[u]->getEdgeLS(i)->getEdge();
          end = edgeTemp->getEnd(); // przeciwległy do u koniec krawędzi - i
          if(beg->getDistance() + edgeTemp->getWeight() < end->getDistance()){
            end->setDistance(beg->getDistance() + edgeTemp->getWeight());
            end->setPrevD(beg); 
            heap.push(end);
          }
        }
        if(heap.length())
          u = heap.pop()->getElement();
        else u = -1;
      }
      return tab;
   }

  


    void printDjikstra(ListVertex* tab, int vert){
    Vertex* x = tab->getVertex(vert);
    ListVertex* path = new ListVertex;
    cout << vert << "\t";
    if(!x->isVisited()) cout << "nieodwiedzony";
    else if(x->getPrevD() == nullptr)  cout << "brak";
    else {
      cout << x->getDistance() << "\t";
      path->push(new Vertex(tab->getVertex(vert)->getElement()));
      for(int i = 0; x->getPrevD() != nullptr; i++){
        //cout << "push" << endl;
        x = x->getPrevD();
        path->push(new Vertex(x->getElement()));
        
      }
      int length = path->length();

      
      for(int i = 0; i < length; i++){
        if(i == 0)
          cout << path->getLast()->getElement();
        else cout << "->" << path->getLast()->getElement();
        path->delLast();
      }
      
      }
      cout << endl;
      delete path;
    }


   void printWholeDjikstra(ListVertex* tab){
     cout << "Wezel\tDystans\tSciezka" << endl;
     for(int i = 0; i < v; i++){
       printDjikstra(tab, i);
     }
   }

  void printDjikstraToFile(ListVertex* tab, int vert, fstream& file){
    Vertex* x = tab->getVertex(vert);
    ListVertex* path = new ListVertex;
    file << vert << "\t";
    if(!x->isVisited()) file << "nieodwiedzony";
    else if(x->getPrevD() == nullptr)  file << "brak";
    else {
      file << x->getDistance() << "\t";
      path->push(new Vertex(tab->getVertex(vert)->getElement()));
      for(int i = 0; x->getPrevD() != nullptr; i++){
        //file << "push" << endl;
        x = x->getPrevD();
        path->push(new Vertex(x->getElement()));
        
      }
      int length = path->length();

      
      for(int i = 0; i < length; i++){
        if(i == 0)
          file << path->getLast()->getElement();
        else file << "->" << path->getLast()->getElement();
        path->delLast();
      }
      
      }
      file << endl;
      delete path;
    }

   void printWholeDjikstraToFile(ListVertex* tab, fstream& file){
    file << "Wezel\tDystans\tSciezka" << endl;
    for(int i = 0; i < v; i++){
      printDjikstraToFile(tab, i, file);
    }
   }


   void testHeap(){
    Heap heap;
    Vertex* temp;
    for(int i = 0; i < 10; i++){
      heap.push(V->getVertex(i));
     }
    
    cout << "Test kopca: " ;
    for(int i = 0; i < 10; i++){
      heap.printHeap();
      cout << endl;
      temp = heap.pop();
      if(temp == nullptr) cout << "Błąd funkcji pop!" << endl;
      else
        cout << temp->getDistance() << '\t';
     }
    cout << endl; 
   }
   void printLS(){
      for(int i = 0; i < v; i++){
        cout << "LS wierzchołka " << i << endl;
        if(LS[i] != nullptr) LS[i]->printAll();
      }
   }

   void testLS(){
    Edge* temp;
    int length = V->length();
    int beg;
    E->printAll();
    cout << "przed: " << endl;
    for(int i = 0; i < v; i++){
      if(LS[i] != nullptr) LS[i]->printAll();
    }
    for(int i = 0; i < 10; i++){
      temp = E->getEdge(i);
      beg = temp->getBeg()->getElement();
      LS[beg]->push(new EdgeLS(temp));
    }
    printLS();
   }
   void resetV(){
     Vertex* temp = V->getVertex(0);
     for(int i = 0; i < v - 1; i ++){
       temp->setDistance(INF);
       temp->setPrevD(nullptr);
       if(temp->getNext() != nullptr)
        temp = temp->getNext();
     }
   }
   
                                              

};