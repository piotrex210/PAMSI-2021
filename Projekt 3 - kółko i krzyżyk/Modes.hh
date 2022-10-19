#pragma once

#include "Board.hh"

void Board::easyMode(){
  this->printBoard();
  for(int i = 0; i < size*size; i++){
    if(i % 2 == 0){
      if(playerSign == 'O') this->movePlayer();
      else moveRandO();
    } 
    else {
      if(playerSign == 'X') this->movePlayer();
      else moveRandX();
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

void Board::mediumMode(){
  this->printBoard();
  for(int i = 0; i < size*size; i++){
    if(i % 2 == 0){
      if(playerSign == 'O') this->movePlayer();
      else if(!this->moveSmartO()) this->moveRandO();
    } 
    else {
      if(playerSign == 'X') this->movePlayer();
      else if(!this->moveSmartX()) this->moveRandX();
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