#include <iostream>
#include <iomanip>
#include <stdlib.h> // do srand i rand
#include <time.h> // time
#include <fstream> // do odczytu i zapisu plików

#include "ListVertex.hh"
#include "ListEdge.hh"
#include "Vertex.hh"
#include "Edge.hh"
#include "Graph.hh"
#include "Heap.hh"

#define VERT 10 // ilość wierzchołków
#define DENS 25 // gęstość grafu w %
#define EDGE  VERT*(VERT-1)/2*DENS/100 // ilosc krawedzi
#define GAMOUNT 1 // liczba grafów danego typu

int densityTable[4] = {25, 50, 75, 100};
int verticesTable[5] = {10, 20, 50, 100, 200};
//int size

using namespace std;

int main(int argc, char* argv[]){
  // lososwe wypełnianie tablicy
  fstream sourcef, resoultf, pathsf, pathsf2;
  int edges = EDGE, vertices = VERT, vstart, density;
  bool isSourceFile = false;

  srand(time(NULL));
  
  ListVertex V;
  ListEdge E;
  ListVertex* resultD;

  
  int beg, end, weight, temp, lengthV;
  // jeśli czytamy z pliku
  if(argc == 1){
    cout << "Podaj argument: f - odczyt danych z pliku 'source.txt', r - losowo generowane dane" << endl;
    return 0;
  }
  else if(argc != 1 && (*argv[1] != 'f' && *argv[1] != 'r')){
    cout << "Podaj argument: f - odczyt danych z pliku 'source.txt', r - losowo generowane dane" << endl;
    return 0;
  }
  else if(*argv[1] == 'f'){
    sourcef.open("source.txt");
    if(sourcef.is_open()){
      isSourceFile = true;
      sourcef >> edges >> vertices >> vstart;
      cout << edges << '\t' << vertices << '\t' << vstart << endl;
    }
    else  cout << "Nie udało się otworzyć pliku: " << endl;
  }

  
  clock_t Start, End; // do mierzenia czasu
  double timeM, timeLS, sumTimeM, sumTimeLS; // czas dla Macierzy i Listy Sąsiedztwa i czas całkowity dla GAMOUNT powtorzeń
  double averageTimes[2][4][5]; // tablica zbierająca średnie czasy obliczeń dla danych zestawów tablic:
  // 2 - typ grafu: 0 - Matrix, 1 - LS; 4 - liczba różnych gęstosci: 25,50,75,100%, 5 - liczba liczb wierzchołków: 10, 20, 50, 100, 200

  if(isSourceFile){
    Graph* G = new Graph(vertices, edges, &V, &E, isSourceFile, densityTable[3]);
    for(int i = 0; sourcef >> temp; i++){
      if(i%3 == 0)  beg = temp;
      else if(i%3 == 1) end = temp;
      else if(i%3 == 2){
        weight = temp;
        if(beg > vertices - 1 || end > vertices - 1)
          cout << "Zły indeks przy dodawaniu krawędzi do Grafu!" << endl;   
        G->insertEdge(beg, end, weight);
      }
    }
    G->setMatrix();
    G->setLS();
    Start = clock();
    resultD = G->doDjikstraLS(0);
    End = clock();
    timeLS = double(End-Start)/CLOCKS_PER_SEC;
    pathsf.open("paths.txt");
    if(pathsf.is_open()){
      G->printWholeDjikstraToFile(resultD, pathsf);
    }
    G->resetV();
    Start = clock();
    resultD = G->doDjikstra(0); // algorytm Dijkstry na macerzy
    End = clock();
    timeM = double(End-Start)/CLOCKS_PER_SEC;
    pathsf2.open("paths2.txt");
    if(pathsf2.is_open()){
      G->printWholeDjikstraToFile(resultD, pathsf2);
    }
    cout << "Czas wykonywania DJ dla LS: " << timeLS << "\tczas dla Macierzy: " << timeM << endl;
    delete G;
  }
  else{
    for(int nVert = 0; nVert < 5; nVert++){ // dla każdej ilości wierzchołków
      for(int nDens = 0; nDens < 4; nDens++){ // dla każdej gęstości
      vertices = verticesTable[nVert];
      density = densityTable[nDens];
      edges = vertices*(vertices - 1)/2*density/100;
      for(int i = 0; i < GAMOUNT; i++){ // każda konfiguracja grafu generowana po GAMOUNT razy
        Graph* G = new Graph(vertices, edges, &V, &E, 0, density);
        Start = clock();
        resultD = G->doDjikstraLS(0);
        End = clock();
        timeLS = double(End-Start)/CLOCKS_PER_SEC;
        sumTimeLS += timeLS;
        G->resetV();
        Start = clock();
        resultD = G->doDjikstra(0);
        End = clock();
        timeM = double(End-Start)/CLOCKS_PER_SEC;
        sumTimeM += timeM;
        delete G;
      }
      averageTimes[0][nDens][nVert] = sumTimeM / GAMOUNT; // zapisanie średnich czasów do tablicy wyników
      averageTimes[1][nDens][nVert] = sumTimeLS / GAMOUNT;
      }
    }
    
    
  }

  resoultf.open("resoult.txt");
  if(resoultf.is_open()){
    
    resoultf << "Srednie czasy algorytmu Djikstry dla grafu opartego na Macierzy" << endl;
    for(int i = 0; i < 4; i++){
      resoultf << "Gestosc grafu: " << densityTable[i] << "%" << endl;
      resoultf << "Ilosc wierzcholkow  Sr. czas" << endl;
      for(int j = 0; j < 5; j++){
        resoultf << left << verticesTable[j] << "\t" << right << setw(24) << fixed << setprecision(6) << averageTimes[0][i][j] << endl;
      }
    }
    resoultf << "Srednie czasy algorytmu Djikstry dla grafu opartego na Liscie Sasiedztwa" << endl;
    for(int i = 0; i < 4; i++){
      resoultf << "Gestosc grafu: " << densityTable[i] << "%" << endl;
      resoultf << "Ilosc wierzcholkow  Sr. czas" << endl;
      for(int j = 0; j < 5; j++){
        resoultf << left << verticesTable[j] << "\t" << right << setw(24) << fixed << setprecision(6) << averageTimes[1][i][j] << endl;
      }
    }
  }
  
  

  

  cout << "Hello" << endl;
  //delete G;
}

