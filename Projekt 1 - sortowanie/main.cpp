#include <iostream>
#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <fstream>
#include "headers.h"
#define SIZE1 10000
#define SIZE2 50000
#define SIZE3 100000
#define SIZE4 500000
#define SIZE5 1000000
#define ILETABLIC 1 // ile sortujemy tablic każdego rozmiaru
// dla testów możemy zmniejszyć liczbę, żeby skrócić czas trwania programu

using namespace std;

// rozmiary koncowych tablic
const int sizes[5] = {10000, 50000, 100000, 500000, 1000000};
// stopien posortowania tablicy (w promilach)
const int part[8] = {0, 250, 500, 750, 950, 990, 997, 1000};
// czas sortowania kazdej tablicy
float sortTime[8][5][ILETABLIC+1];
// sredni czas sortowania 100 tablic
float avSortTime[3][8][5];

main(){
  for(int j = 0; j< 8;j++)
    for(int i = 0; i<5; i++)
      cleanTab(sortTime[j][i],100);

  clock_t timeSort;
  // tablice zaczynamy indeksowac od 1, a nie od 0, żeby 
  // można było łatwiej tlumacznyc algorytmy z pseudokodu
  unsigned int tab1[SIZE5+1];  // tablica z danymi, na której będziemy pracować
  unsigned int pom[SIZE5+1];  // tablica pomocnicza do sortowania przez scalanie
  cleanTab(pom, SIZE5);


// SORTOWANIE QUICKSORT
// TWORZENIE TABLIC, SORTOWANIE, MIERZENIE CZASU, ZAPISYWANIE CZASÓW ŚREDNICH DO PLIKU
  for(int k = 0; k < 8; k++){
    for(int j = 0; j<5; j++){
      for(int i = 0; i < ILETABLIC; i++){
        make(tab1, sizes[j], part[k]);
        timeSort = clock();
        quicksort(tab1, 1, sizes[j]);
        timeSort = clock() - timeSort;
        // Zwraca błąd, komunikat na wyjściu, jeśli tablica jest źle posortowana
        if(!checkSort(tab1, sizes[j], 'r')) cout << "Tablica źle posortowana" << endl;
        sortTime[k][j][i] = ((float)timeSort)/CLOCKS_PER_SEC;
      }
    }
  }
  // CZĘŚĆ PROGRAMU LICZĄCA CZASY ŚREDNIE
  for(int k = 0; k< 8; k++) // k - czesc juz posortowanej tablicy
    for(int j = 0;j<5; j++){ // j - rozmiar tablicy
      float sum = 0;
      for(int i=0; i<ILETABLIC; i++)
        sum = sum + sortTime[k][j][i];
      avSortTime[0][k][j] = sum/ILETABLIC;
  }
  // CZĘŚĆ PROGRAMU ZAPISUJĄCA ŚREDNIE CZASY DO PLIKU,
  // dane w plikach uporządkowane są w Grupy, według rozmiaru tablicy,
  // w każdej Grupie czas jest uporządkowany według stopnia wcześniejszego posortowania:
  // wszystkie elementy tablicy losowe, 25%, 50%, 75%, 95%, 99%, 99,7% posortowanych,
  // posortowane w odwrotnej kolejności;
  ofstream quickfile;
  quickfile.open("quick.txt");
  for(int j = 0; j<5; j++){
    quickfile << "Czasy sortowania tablicy o rozmiarze: " << sizes[j] << "\n";
    for(int i = 0; i<8;i++)
      quickfile << avSortTime[0][i][j] << "\n";
  }
  quickfile.close();

  // SORTOWANIE SHELLA
  // TWORZENIE TABLIC, SORTOWANIE, MIERZENIE CZASU, ZAPISYWANIE CZASÓW ŚREDNICH DO PLIKU
  for(int k = 0; k < 8; k++){
    for(int j = 0; j<5; j++){
      for(int i = 0; i < ILETABLIC; i++){
        make(tab1, sizes[j], part[k]);
        timeSort = clock();
        shellSort(tab1, sizes[j]);
        timeSort = clock() - timeSort;
        if(!checkSort(tab1, sizes[j], 'r')) cout << "Tablica źle posortowana" << endl;
        sortTime[k][j][i] = ((float)timeSort)/CLOCKS_PER_SEC;
      }
    }
  }
  for(int k = 0; k< 8; k++) // k - czesc juz posortowanej tablicy
    for(int j = 0;j<5; j++){ // j - rozmiar tablicy
      float sum = 0;
      for(int i=0; i<ILETABLIC; i++)
        sum = sum + sortTime[k][j][i];
      avSortTime[1][k][j] = sum/ILETABLIC;
  }
  ofstream shellfile;
  shellfile.open("shell.txt");
  for(int j = 0; j<5; j++){
    shellfile << "Czasy sortowania tablicy o rozmiarze: " << sizes[j] << "\n";
    for(int i = 0; i<8;i++)
      shellfile << avSortTime[1][i][j] << "\n";
  }
  shellfile.close();

  // SORTOWANIE PRZEZ SCALANIE (MERGE SORT)
  // TWORZENIE TABLIC, SORTOWANIE, MIERZENIE CZASU, ZAPISYWANIE CZASÓW ŚREDNICH DO PLIKU
    for(int k = 0; k < 8; k++){
    for(int j = 0; j<5; j++){
      for(int i = 0; i < ILETABLIC; i++){
        make(tab1, sizes[j], part[k]);
        timeSort = clock();
        mergeSort(tab1,pom, 1, sizes[j]);
        timeSort = clock() - timeSort;
        if(!checkSort(tab1, sizes[j], 'r')) cout << "Tablica źle posortowana" << endl;
        sortTime[k][j][i] = ((float)timeSort)/CLOCKS_PER_SEC;
      }
    }
  }
  for(int k = 0; k< 8; k++) // k - czesc juz posortowanej tablicy
    for(int j = 0;j<5; j++){ // j - rozmiar tablicy
      float sum = 0;
      for(int i=0; i<ILETABLIC; i++)
        sum = sum + sortTime[k][j][i];
      avSortTime[2][k][j] = sum/ILETABLIC;
  }
  ofstream mergefile;
  mergefile.open("merge.txt");
  for(int j = 0; j<5; j++){
    mergefile << "Czasy sortowania tablicy o rozmiarze: " << sizes[j] << "\n";
    for(int i = 0; i<8;i++)
      mergefile << avSortTime[2][i][j] << "\n";
  }
  mergefile.close();

  return 0;
}

// funkcja tworząca tablice o losowych elementach, częściowo posortowaną
// part - część tablicy posortowanej od początku w promilach
void make(unsigned int *tab, unsigned int size, unsigned int part){
  cleanTab(tab, size);
  randtab(tab,1,size);
  quicksort(tab,1, size*part/1000);
  if(part == 1000)
    reverseTab(tab, size);
}

void reverseTab(unsigned int* tab, const unsigned int size){
  int x;
  for(int i = 1; i<=size/2; i++)
    swap(tab[i],tab[size-i+1]);
}

bool checkSort(const unsigned int* tab,const unsigned int size, const char type){
  bool correct = true;
  if(type != 'r' && type != 'm'){
    cout << "wprowadź inny typ sortowania, f-cja checkSort" << endl;
    correct = false;
    return correct;
  }
  if(type == 'r'){
    for(int i = 1; i <size; i++){
      if(tab[i]>tab[i+1]) {
        correct = false;
        break;
      }
    }
  }
  else if(type == 'm'){
    for(int i = 1; i <size; i++){
      if(tab[i]<tab[i+1]) {
        correct = false;
        break;
      }
    }
  }
  return correct;
}

void shellSort(unsigned int *tab,const unsigned int size){
  int i, j, h, x;
  h = 1;
  while(h<size)
    h = 3*h+1;
  h=h/9;
  if(h==0)  
    h = 1;
  while(h>0){
    for(j = size-h; j>=1; j--){
      x = tab[j];
      i = j+h;
      while(i<=size && x>tab[i]){
        tab[i-h] = tab[i];
        i = i+h;
      }
      tab[i-h] = x;
    }
    h = h/3;
  }
}

void quicksort(unsigned int* tab,const unsigned int left,const unsigned int right){
  int pivot, i ,j; // pivot - element podziałowy
  i = (left+right)/2;
  pivot = tab[i];
  tab[i] = tab[right];
  j = left;
  for(i=left; i<right;i++){
    if(tab[i]<pivot){
      swap(tab[i],tab[j]);
      j++;
    }
  }
  tab[right]=tab[j];
  tab[j] = pivot;
  if(left<j-1)
    quicksort(tab, left, j-1);
  if(j+1<right)
    quicksort(tab,j+1,right);
}

void mergeSort(unsigned int* tab,unsigned int* pom,const unsigned int ip,const unsigned int ik){
  int is = (ip+ik+1)/2;
  if(is-ip>1)
    mergeSort(tab,pom,ip,is-1);
  if(ik-is>0)
    mergeSort(tab,pom,is,ik);
  merge(tab,pom,ip,is,ik);
}
// funkcja scalająca 2 uporządkowane rosnąco zbiory
void merge(unsigned int* tab, unsigned int* pom,const unsigned int ip,const unsigned int is,const unsigned int ik){
  int i1, i2, i;
  i1 = ip; i2 = is; i = ip;
  for(i = ip; i<= ik; i++){
    if(i1==is || (i2<=ik && (tab[i1] > tab[i2]))){
      pom[i]=tab[i2]; 
      i2++;
    }
    else{
      pom[i] = tab[i1];
      i1++;
    }
  }
  for(i = ip; i<=ik; i++)
    tab[i] = pom[i];
}
// budowa kopca
void buildHeap(unsigned int* tab, unsigned int size){ // F-cja budująca kopiec
  int n, i, j, k, x;
  n = size;
  for(i = 2; i<=n; i++){
    j = i;
    k = j/2;
    x = tab[i];
    while(k>0 && tab[k] < x){
      tab[j] = tab[k];
      j=k;
      k=j/2;
    }
    tab[j] = x;
  }
}

 // stripHeap - rozbierz kopiec
void stripHeap(unsigned int* tab, unsigned int size){ // F-cja rozbierająca kopiec
  int n, i, j, k, m, x;
  bool endd = false; // czy koniec petli 2?
  n = size;
  for(i = n; i>1; i--){
    x = tab[1];
    tab[1] = tab[i];
    tab[i] = x;
    j = 1;
    k = 2;
    endd = false;
    while(k<i && !endd){ // petla 2
      if(k+1<i && tab[k+1]>tab[k])
        m = k+1;
      else m = k;
      if(tab[m]<=tab[j]){
        endd = true;
      }
      else{
        x = tab[j];
        tab[j] = tab[m];
        tab[m] = x;
        j = m;
        k = 2*j;
      }
    }
  }
}

void readtab(const unsigned int* tab,unsigned int from,unsigned int to){
  if (from<=to)
    for (int i = from; i<=to; i++)
      cout << tab[i] << " ";
  else cout << "Złe indeksy tablic" << endl;
}
void readtabtofile(const unsigned int* tab,unsigned int from,unsigned int to){
  if (from<=to){
    for (int i = from; i<to; i++)
      cout << tab[i] << endl;
    cout << tab[to];
  }
  else cout << "Złe indeksy tablic" << endl;
}
void randtab(unsigned int* tab,unsigned int start, unsigned int size){
    srand((unsigned)time(NULL));
    tab[0] = 0;
    for(int i = start; i<=size; i++)
      tab[i] = rand() % size;
}

void cleanTab(unsigned int* tab, unsigned int size){
  for(int i = 1; i<=size; i++)
    tab[i] = 0;
}
void cleanTab(float* tab, unsigned int size){
  for(int i = 1; i<=size; i++)
    tab[i] = 0;
}