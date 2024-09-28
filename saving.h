#ifndef SAVING_H
#define SAVING_H
#include "subaccount.h"
#include <iostream>
#include <string>
using namespace std;
class Saving : public SubAccount {
public:
  Saving() {
    subAccountNum = "NA";
    subAccountBalance = 0;
  }

  Saving(string num, int balance) {
    this->subAccountNum = num;
    this->subAccountBalance = balance;
  }

  void printSaveInfo() {
    SubAccount :: printSubAccountInfo(); 
    cout << endl;
  }

  void saveDeposit(){
    int depositAmount;
    cout << "Enter deposit amount: ";
    cin >> depositAmount;
    if (cin.good()){
      SubAccount :: subDeposit(depositAmount);
    } 
    else {
      cout << "Please enter an avaible numbers!" << endl << endl;
    }
    cin.clear();
    cin.ignore();
  }

  void saveWithdraw(){
    int withdrawAmount;
    cout << "Enter withdraw amount: ";
    cin >> withdrawAmount;
    if (cin.good()){
      SubAccount :: subWithdraw(withdrawAmount);    } 
    else {
      cout << "Please enter an avaible numbers!" << endl << endl;
    }
    cin.clear();
    cin.ignore();
  }

  void printSaveMenu(){
    
    string userInput;
    cout << "Eligible services for sub-account " << getSubAccountNum() << endl;
    cout << "  D -- Deposit"<< endl;
    cout << "  W -- Withdraw" <<  endl;
    cout << "  X -- Exit" << endl;
    cout << "Please enter your selection: ";
    cin >> userInput;
    
    if (userInput == "d" || userInput == "D"){ 
      saveDeposit();
      printSaveMenu();
    }
    else if (userInput == "w" || userInput == "W"){
      saveWithdraw(); 
      printSaveMenu();
    }
    else if (userInput == "x" || userInput == "X"){
      cout << "End of service for sub-account " << getSubAccountNum() << endl;
      return;
    }
    else {
      cout << "Please make another selection!" << endl;
      printSaveMenu();
    }
  }
};
#endif