#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Modes.hh"
//#include "Moves.hh"

using namespace std;

void chooseSettings(int &size, int &n, char& mode, char& playerSign);

int size = 5;
int n = 4;
char mode = ' '; // poziom trudnosci gry: e- easy, m - medium, h - hard
char playerSign = 'O';

int main(){
  srand(time(NULL)); // zresetowanie ziarna rand
  int temp = 0;

  chooseSettings(size, n, mode, playerSign);
  Board board(size, n);
  board.setPlayerSign(playerSign);
  //board.evaluate();
  board.finalPlay();


}

void chooseSettings(int &size, int &n, char& mode, char& playerSign){
  cout << "Wybierz rozmiar pola" << endl;
  cin >> size;
  
  cout << "Ile pol w rzędzie gwarantuje wygraną?" << endl;
  cin >> n;

  //cout << "Wybierz poziom trudności: e - easy, m - medium, h - hard" << endl;
  //cin >> mode;

  char choice;
  cout << "Chcesz zacząć grę?: t - tak, n - nie" << endl;
  cin >> choice;
  if(choice == 't') playerSign = 'O';
  else playerSign = 'X';
}

