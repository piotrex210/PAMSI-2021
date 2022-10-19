#pragma once

#include <iostream>
#include <vector>
#include <climits> // potrzebne do INT_MAX i INT_MIN
#include <cmath> // pow()


#define SIZE 3
#define N 3

using namespace std;

class Board{
  // size - wymiar planszy, n - ile pod rząd, aby wygrać, round - która runda(nieparzysta - ruch 'O')
  unsigned size, n, round, nEmpty; 
  vector<vector<char>> board;
  char winner, mode, playerSign;
  int valueMinMax; // wartość ruchu
  int value;
  vector<Board*> childrenNodes; // wektor potomków
  
  public:    
   Board(unsigned s, unsigned nArg){
    valueMinMax = 0;
    value = 9;
    round = 1;
    size = s;
    n = nArg;
    winner = 'P';
    mode = ' ';
    playerSign = 'X';
    // wstawianie pustych znaków
    vector<char> temp;
    for(int j = 0; j < size; j++){
      temp.push_back(' ');
    }
    for(int j = 0; j < size; j++)
      board.push_back(temp);    
  }

  Board(const Board& org){
    size = org.getSize();
    n = org.getN();
    valueMinMax = 0;
    value = 9;
    round = org.getRound();
    winner = 'P';
    mode = ' ';
    playerSign = 'X';
    // wstawianie pustych znaków
    vector<char> temp;
    for(int j = 0; j < size; j++){
      temp.push_back(' ');
    }
    for(int j = 0; j < size; j++)
      board.push_back(temp);  

    for(int i = 0; i < size; i++){
        this->board[i] = org.board[i];
    }
    evaluate();
  }

  ~Board(){
    int size = childrenNodes.size();
    for(int i = 0; i < size; i++){
     childrenNodes.pop_back();
    }
    //delete childrenNodes;
    //delete value;
  }

  // tworzy wektor plansz z każdym możliwym ruchem 1 poziom w dół
    void makeChildrenVector(){
      // isGameOver?
      Board temp = *this;
      for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
          if(board[i][j] == ' '){
            if(round%2) temp.moveO(i,j);
            else temp.moveX(i,j);
            temp.isGameOver();
            childrenNodes.push_back(new Board(temp));
            temp = *this;
          }
    }
  
    int correctIndex(int x, int y){
      if((x > size || y > size) || x < 0 || y < 0)  {
        cout << "Zly indeks, podaj 2 liczby z  zakresy od 0 do " << size - 1 << endl;
        return 0;
      }
      else 
        return 1;
    }

    bool isGameOver();

    bool moveO( unsigned int x, unsigned int y);

    bool moveX( unsigned int x, unsigned int y);

    void moveRandO();

    void moveRandX();

    bool moveSmartO();

    bool moveSmartX();

    void movePlayer();

    void printBoard();

    bool isMoveO(){
      return round%2;
    }

    bool isMoveX(){
      return !round%2;
    }

    bool isPlayerMove(){
      if((isMoveO() && playerSign == 'O') || (!isMoveO() && playerSign == 'X'))return true;
      else return false;
    }

    Board getChild(unsigned i) const {
      return *childrenNodes[i]; // lub *childrenNodes.operator[](i);
    }

    Board* getChildPtr(unsigned i) const {
      return childrenNodes[i]; // lub *childrenNodes.operator[](i);
    }

    int getRound() const{
      return round;
    }


    char getWinner(){
      return winner;
    }

    vector<char> getVector(unsigned i){
      return board[i];
    }

    void operator =(const Board &b){
      for(int i = 0; i < size; i++){
        this->board[i] = b.board[i];
      }
      this->setValue(b.getValue());
      this->setRound(b.getRound());
    }
    void countEmptyBoxes(){
      
    }

    void setRound(int r){
      round = r;
    }

    void automaticGame();

    void easyMode();

    void mediumMode();

    void hardMode();

    void readBoard(const char **B);

    void chooseSettings();

    bool evaluate(); // szacowanie wartości ruchu

    int getValue() const {
      return value;
    }

    void setValue(int v){
      value = v;
    }

    void setPlayerSign(char s){
      playerSign = s;
    }

    void tempPlay();

    void finalPlay();

    void Min();

    void Max();

    void makeTree(int depth, Board*);

    void deleteTree(Board* tree);

    int getChildrenNodesSize(){
      return childrenNodes.size();
    }

    int getSize() const{
      return size;
    }

    int getN() const{
      return n;
    }

    int MinMax(Board*);

  };

  void Board::printBoard(){
      // funkcja wyswietlajaca planszę
    cout << "  ";
    for(int j = 0; j < size ; j++){
        cout << ' ' << j << "  ";
      }
      cout << endl << endl;

    for(int i = 0; i < size - 1; i++){
      cout << i << " ";
      for(int j = 0; j < size - 1; j++){
        cout << ' ' << board[i][j] << ' ' << '|';
      }
      cout << board[i][size - 1] << endl; 
      cout << "  ";
      for(int j = 0; j < size - 1; j++){
        cout << "----";
      }
      cout << "---" << endl;
    }
    cout << size - 1 << ' ';
    for(int j = 0; j < size - 1; j++){
        cout << ' ' << board[size - 1][j] << ' ' << '|';
      }
    cout << board[size - 1][size - 1] << endl << endl << endl; 
}

bool Board::isGameOver(){
    winner = ' ';
    int inRow = 0;
    // sprawdzanie wierszy X
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size - n + 1; j++){
        for(inRow = 0; inRow < n; inRow++){
          if(board[i][j + inRow] != 'X')  break;
        }
        if(inRow >= n)  
          winner = 'X';
        if(winner != ' ') break;
      }
      if(winner != ' ') break;
    }
    if(winner != ' ') return true;
    else // sprawdzanie kolumn
    {
      for(int i = 0; i < size; i++){
        for(int j = 0; j < size - n + 1; j++){
          for(inRow = 0; inRow < n; inRow++){
            if(board[j + inRow][i] != 'X')  break;
          }
          if(inRow >= n)  
            winner = 'X';
          if(winner != ' ') break;
        }
        if(winner != ' ') break;
      }
    }
    if(winner != ' ') return true;
    else{ // sprawdzanie przekątnych w prawo, do góry
        for(int i = n - 1; i < size; i++){
          for(int j = 0; j < size - n + 1; j++){
            for(inRow = 0; inRow < n; inRow++){
              if(board[i - inRow][j + inRow] != 'X')  break;
            }
            if(inRow >= n)  
              winner = 'X';
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
      if(winner != ' ') return true;
      else
      {
        // sprawdzanie przekątnych w prawo, w dół
        for(int i = 0; i < size - n + 1; i++){
          for(int j = 0; j < size - n + 1; j++){
            for(inRow = 0; inRow < n; inRow++){
              if(board[i + inRow][j + inRow] != 'X')  break;
            }
            if(inRow >= n)  
              winner = 'X';
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
        if(winner != ' ') return true;
      } 
    }
    if(winner != ' ') return true;
    else // sprawdzanie, czy 'O' wygrał
    {
      // sprawdzanie wierszy O
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size - n + 1; j++){
        for(inRow = 0; inRow < n; inRow++){
          if(board[i][j + inRow] != 'O')  break;
        }
        if(inRow >= n)  
          winner = 'O';
        if(winner != ' ') break;
      }
      if(winner != ' ') break;
    }
    if(winner != ' ') return true;
    else // sprawdzanie kolumn
    {
      for(int i = 0; i < size; i++){
        for(int j = 0; j < size - n + 1; j++){
          for(inRow = 0; inRow < n; inRow++){
            if(board[j + inRow][i] != 'O')  break;
          }
          if(inRow >= n)  
            winner = 'O';
          if(winner != ' ') break;
        }
        if(winner != ' ') break;
      }
    }
    if(winner != ' ') return true;
    else{ // sprawdzanie przekątnych w prawo, do góry
        for(int i = n - 1; i < size; i++){
          for(int j = 0; j < size - n + 1; j++){
            for(inRow = 0; inRow < n; inRow++){
              if(board[i - inRow][j + inRow] != 'O')  break;
            }
            if(inRow >= n)  
              winner = 'O';
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
      if(winner != ' ') return true;
      else
      {
        // sprawdzanie przekątnych w prawo, w dół
        for(int i = 0; i < size - n + 1; i++){
          for(int j = 0; j < size - n + 1; j++){
            for(inRow = 0; inRow < n; inRow++){
              if(board[i + inRow][j + inRow] != 'O')  break;
            }
            if(inRow >= n)  
              winner = 'O';
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
        if(winner != ' ') return true;
      } 
    }
    } 
    if(winner != ' ') return true;
    else return false;
}

bool Board::moveO( unsigned int x, unsigned int y){
  if(!correctIndex(x,y)){
    cout << "Nie mozna zrobic ruchu!" << endl;
    return false;
  }
  else
  {
    if(board[x][y] != ' '){
      cout << "Pole zajete!" << endl;
      return false;
    }
    else{
      board[x][y] = 'O';
      round++;
      return true;
    } 
  } 
}

bool Board::moveX( unsigned int x, unsigned int y){
  if(!correctIndex(x,y)){
    cout << "Nie mozna zrobic ruchu!" << endl;
    return false;
  }
  else
  {
    if(board[x][y] != ' '){
      cout << "Pole zajete!" << endl;
      return false;
    }
    else{
      board[x][y] = 'X';
      round++;
      return true;
    } 
  }     
}

void Board::moveRandO(){
  int x,y;
  x = rand() % size;
  y = rand() % size;
  while(board[x][y] != ' '){
    x = rand() % size;
    y = rand() % size;
  }
  this->moveO(x, y);
}

void Board::moveRandX(){
  int x,y;
  x = rand() % size;
  y = rand() % size;
  while(board[x][y] != ' '){
    x = rand() % size;
    y = rand() % size;
  }
  this->moveX(x, y);
}

bool Board::moveSmartO(){
  Board temp = *this;
  vector<Board> V;
  // Wykonaj ruch wygrywający
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(this->board[i][j] == ' '){
        temp.moveO(i, j);
        if(temp.isGameOver()){
          if(temp.getWinner() == 'O')
          {
            this->moveO(i, j);
            return true;
          }
        }
        else
          temp = *this;   
      }
    }
  }// wykonaj ruch blokujący
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(this->board[i][j] == ' '){
        temp.moveX(i, j);
        if(temp.isGameOver()){
          if(temp.getWinner() == 'X')
          {
            this->moveO(i, j);
            return true;
          }
        }
        else
          temp = *this;   
      }
    }
  }
  return false;
}

bool Board::moveSmartX(){
  Board temp = *this;
  vector<Board> V;
  // Wykonaj ruch wygrywający
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(this->board[i][j] == ' '){
        temp.moveX(i, j);
        if(temp.isGameOver()){
          if(temp.getWinner() == 'X')
          {
            this->moveX(i, j);
            return true;
          }
        }
        else
          temp = *this;   
      }
    }
  }// wykonaj ruch blokujący
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(this->board[i][j] == ' '){
        temp.moveO(i, j);
        if(temp.isGameOver()){
          if(temp.getWinner() == 'O')
          {
            this->moveX(i, j);
            return true;
          }
        }
        else
          temp = *this;   
      }
    }
  }
  return false;
}

void Board::automaticGame(){
  this->printBoard();
  for(int i = 0; i < size*size; i++){
    if(i % 2 == 0){
      if(!this->moveSmartO()) this->moveRandO();
    } 
    else {
      if(!this->moveSmartX()) this->moveRandX();
    }
    this->printBoard();

    if(this->isGameOver()){
      cout << "Zwyciezyl gracz: " << this->getWinner() << endl;
      break;
    }
  }
  if(!this->isGameOver())
    cout << "Remis!" << endl;
}

void Board::movePlayer(){
  int x, y;
  cout << "Graczu " << playerSign << "! Podaj wzspółrzędne x, y Twojego kolejnego ruchu!" << endl;
  cin >> x >> y;
  while(!correctIndex(x,y)) {
    cout << "Złe współrzędne, podaj 2 liczby z zakresu od 0 do " << size - 1 << endl;
    cin >> x >> y;
  }
  if(playerSign == 'O'){
    while(!moveO(x, y)){
      cout << "Graczu " << playerSign << "! Podaj wzspółrzędne x, y Twojego kolejnego ruchu!" << endl;
      cin >> x >> y;
    }
  } 
  else 
    while(!moveX(x, y)){
      cout << "Graczu " << playerSign << "! Podaj wzspółrzędne x, y Twojego kolejnego ruchu!" << endl;
      cin >> x >> y;
    }
}

void Board::readBoard(const char **B){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      board[i][j] = B[i][j];
    }
  }
}

bool Board::evaluate(){
    int checked = 0;
    value = 0;
    winner = ' ';
    int inRow = 0;
    // sprawdzanie wierszy X
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size - n + 1; j++){
        checked = 0;
        for(inRow = 0; inRow < n; inRow++){
          if(board[i][j + inRow] == 'X') checked++;
          if(board[i][j + inRow] == 'O'){
            checked = 0;
            break;
          } 
        }
        if(checked) value -= pow(10,checked);
        if(checked >= n)  {
          winner = 'X';
          value = INT_MIN;
        }
        //cout << "VwX: " << *value << " ";
        if(winner != ' ') break;
      }
      if(winner != ' ') break;
    }
    if(winner != ' ') return true;
    else // sprawdzanie kolumn X
    {
      for(int i = 0; i < size; i++){
        for(int j = 0; j < size - n + 1; j++){
          checked = 0;
          for(inRow = 0; inRow < n; inRow++){
            if(board[j + inRow][i] == 'X')  checked++;
            if(board[i][j + inRow] == 'O'){
            checked = 0;
            break;
            } 
          }
          if(checked) value -= pow(10, checked);
          if(checked >= n)  {
            winner = 'X';
            value = INT_MIN;
          }
          //cout << "VkX: " << *value << " ";
          if(winner != ' ') break;
        }
        if(winner != ' ') break;
      }
    }
    if(winner != ' ') return true;
    else{ // sprawdzanie przekątnych w prawo, do góry
        for(int i = n - 1; i < size; i++){
          for(int j = 0; j < size - n + 1; j++){
            checked = 0;
            for(inRow = 0; inRow < n; inRow++){
              if(board[i - inRow][j + inRow] == 'X')  checked++;
              if(board[i - inRow][j + inRow] == 'O'){
                checked = 0; 
                break;
              }
            }
            if(checked) value -= pow(10, checked); // dodajemy punkty do sumy
            if(checked >= n)  {
              winner = 'X';
              value = INT_MIN;
            }
            //cout << "VppX: " << value << " ";
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
      if(winner != ' ') return true;
      else
      {
        // sprawdzanie przekątnych w prawo, w dół
        for(int i = 0; i < size - n + 1; i++){
          for(int j = 0; j < size - n + 1; j++){
            checked = 0;
            for(inRow = 0; inRow < n; inRow++){
              if(board[i + inRow][j + inRow] == 'X')  checked++;
              if(board[i + inRow][j + inRow] == 'O'){
                checked = 0;
                break;
              }
            }
            if(checked) value -= pow(10, checked);
            if(checked >= n)  {
              value = INT_MIN;
              winner = 'X';
            }
            //cout << "VplX: " << value << " ";
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
        if(winner != ' ') return true;
      } 
    }
    if(winner != ' ') return true;
    else // sprawdzanie, czy 'O' wygrał
    {
      // sprawdzanie wierszy O
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size - n + 1; j++){
        checked = 0;
        for(inRow = 0; inRow < n; inRow++){
          if(board[i][j + inRow] == 'O')  checked++;
          if(board[i][j + inRow] == 'X'){
            checked = 0;
            break;
          }
        }
        if(checked) value += pow(10, checked);
        if(checked >= n)  {
          winner = 'O';
          value = INT_MAX;
        }
        //cout << "VwO: " << value << " ";
        if(winner != ' ') break;
      }
      if(winner != ' ') break;
    }
    if(winner != ' ') return true;
    else // sprawdzanie kolumn
    {
      for(int i = 0; i < size; i++){
        for(int j = 0; j < size - n + 1; j++){
          checked = 0;
          for(inRow = 0; inRow < n; inRow++){
            if(board[j + inRow][i] == 'O')  checked++;
            if(board[j + inRow][i] == 'X'){
              checked = 0;
              break;
            }
          }
          if(checked) value += pow(10, checked);
          if(checked>= n) {
            winner = 'O';
            value = INT_MAX;
          } 
          //cout << "VkO: " << value << " ";
          if(winner != ' ') break;
        }
        if(winner != ' ') break;
      }
    }
    if(winner != ' ') return true;
    else{ // sprawdzanie przekątnych w prawo, do góry
        for(int i = n - 1; i < size; i++){
          for(int j = 0; j < size - n + 1; j++){
            checked = 0;
            for(inRow = 0; inRow < n; inRow++){
              if(board[i - inRow][j + inRow] == 'O')  checked++;
              if(board[i - inRow][j + inRow] == 'X'){
                checked = 0;
                break;
              }
            }
            if(checked) value += pow(10, checked);
            if(checked >= n)  {
            winner = 'O';
            value = INT_MAX;
            }
            //cout << "VppO: " << value << " ";
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
      if(winner != ' ') return true;
      else
      {
        // sprawdzanie przekątnych w prawo, w dół
        for(int i = 0; i < size - n + 1; i++){
          for(int j = 0; j < size - n + 1; j++){
            checked = 0;
            for(inRow = 0; inRow < n; inRow++){
              if(board[i + inRow][j + inRow] == 'O')  checked++;
              if(board[i + inRow][j + inRow] == 'X'){
                checked = 0;
                break;
              }
            }
            if(checked) value += pow(10, checked);
            if(checked >= n)  {
              winner = 'O';
              value = INT_MAX;
            }
            //cout << "VplO: " << value << " ";
            if(winner != ' ') break;
          }
          if(winner != ' ') break;
        }
        if(winner != ' ') return true;
      } 
    }
    } 
    //boardValue = value;
    //cout << "V na koncu: " << value << " ";
    //cout << "getValue(): " << getValue() << " " << endl;
    //setValue(temp);
    if(winner != ' ') return true;
    else return false;
}

void Board::tempPlay(){
  int score;
  int position = -1;
  Board* tree = this;

  moveRandO();
  moveRandX();
  moveRandO();
  moveRandX();
  moveRandO();
  if(round%2) score = INT_MIN;
  else score = INT_MAX;
  cout << "Plansza początkowa " << endl;
  printBoard();
  if(!isGameOver()){
    tree = this;
    makeTree(4, this);
    int length = getChildrenNodesSize();
    for(int i = 0; i < length; i++){
      int temp = MinMax(getChildPtr(i));
      if(round%2){ // ruch O
        if(temp >= score){
          position = i;
          score = temp;
        }
      }
      else{ // ruch X
        if(temp <= score){
          position = i;
          score = temp;
        }
      }
    }
    
    *this = getChild(position);
    //printBoard();
    deleteTree(tree);
  }
  if(isGameOver())
      printBoard();
}

void Board::finalPlay(){
  int score;
  int position = -1;
  Board* tree = this;
  int length = 0;
  int temp;

  
  cout << "Plansza początkowa " << endl;
  printBoard();
  while(!isGameOver()){
    tree = this;
    //cout << "PSign: " << playerSign << "PM: " << isPlayerMove() << " Round: " << getRound() << " round%2: " << getRound()%2 << endl;
    if(isPlayerMove()){
      movePlayer();
      printBoard();
    }
    else{
      if(round%2) score = INT_MIN;
      else score = INT_MAX;

      position = -1;
      
      makeTree(4, this);
      length = getChildrenNodesSize();
      for(int i = 0; i < length; i++){
        temp = MinMax(getChildPtr(i));
        if(round%2){ // ruch O
          if(temp >= score){
            position = i;
            score = temp;
          }
        }
        else{ // ruch X
          if(temp <= score){
            position = i;
            score = temp;
          }
        }
      }
    
    *this = getChild(position);
    printBoard();
    deleteTree(tree);
    }
    if(round == size*size+1 && !isGameOver()){
      cout << "Remis!" << endl;
    }
    if(round == size*size+1){
      break;
    }
  }
  if(isGameOver()){
    if(getWinner() == playerSign) 
      cout << "Gratulacje, wygrałeś!" << endl;
    else  
      cout << "Niestety przegrałeś!" << endl;
  }
    
}

void Board::Min(){
  int min = INT_MAX;
  int temp;
  int length = childrenNodes.size();
  
  for(int i = 0; i < length; i++){
    temp = getChild(i).getValue();
    if(temp < min) min = temp;
  }
  if(length)
    value = min;
  else
    evaluate();
}

void Board::Max(){
  int max = INT_MIN;
  int temp;
  int length = childrenNodes.size();
  
  for(int i = 0; i < length; i++){
    temp = getChild(i).getValue();
    if(temp > max) max = temp;
  }
  if(length)
    value = max;
  else
    evaluate();
}

void Board::makeTree(int depth, Board* child){
  int length;
  if(depth <= 0){
    child->evaluate();
    //cout << "Poziom " << depth << "Value: " << getValue() << endl;
    //printBoard();
  }
  else{
    if(!child->isGameOver()){
      child->makeChildrenVector();
      length = child->getChildrenNodesSize();
      for(int i = 0; i < length; i++){
        makeTree(depth - 1, child->getChildPtr(i));
      }
    }
  }
}

void Board::deleteTree(Board* tree){
  int length = tree->getChildrenNodesSize();
  for(int i = 0; i < length; i++){
      tree->childrenNodes.pop_back();
    }
}

// round%2 -> ruch O
int Board::MinMax(Board *child){
  int Min = INT_MAX;
  int Max = INT_MIN;
  int length = child->getChildrenNodesSize();
  if(length == 0){ // jeśli jest na dnie
    child->evaluate();
    return child->getValue();
  }
  else{
    for(int i = 0; i < length; i++){
      if(child->getRound()%2){
        Max = max(Max, MinMax(child->getChildPtr(i)));
      }
      else{
        Min = min(Min,MinMax(child->getChildPtr(i)));
      }
    }
    if(child->getRound()%2) return Max;
    else return Min;
  }
}
