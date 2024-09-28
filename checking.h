#ifndef CHECKING_H
#define CHECKING_H
#include "subaccount.h"
#include <string>
#include <iostream>
using namespace std;
class Checking : public SubAccount{
public:
  Checking(){
    subAccountNum = "NA";
    subAccountBalance = 0;
    maxCap = 0;
    isLock = true;
  }

  Checking(string num, int balance, int max, bool lk ){
    subAccountNum = num;
    subAccountBalance = balance;
    maxCap = max;
    isLock = lk;
  }

  void setMaxCap(int maximumCap) {
    this -> maxCap = maximumCap;
  }
  void setIsLock(bool isLock) {this -> isLock = isLock;}

  int getMaxCap() const {return maxCap;}
  bool getIsLock() const {return isLock;}

  void printCheckInfo(){
    SubAccount :: printSubAccountInfo();
    cout << "Maximum Capacity: " << getMaxCap() << endl;
    if (isLock == true){
      cout << "The sub-account is locked." << endl;
    }
    else {
      cout << "The sub-account is not locked." << endl;
    }
    cout << endl;
  }

  void checkDeposit(){
    int depositAmount;
    if (getIsLock() == false){
      cout << "Enter deposit amount: ";
      cin >> depositAmount;
      if (cin.good()){
        SubAccount :: subDeposit(depositAmount);
      }
      else {
        cout << "Please enter an avaible numbers!" << endl << endl;
      }    
    } 
    else {
      cout << "Sub-Account is locked!" << endl << endl;
    }
    cin.clear();
    cin.ignore();
  }

  void checkWithdraw(){
    int withdrawAmount;
    
    if (getIsLock() == false){
      cout << "Enter withdraw amount: ";
      cin >> withdrawAmount;
      if (cin.good()){
        if (withdrawAmount > maxCap){
          cout << "The withdraw amount is larger than max capacity!" << endl;
          cout << "The withdraw was unsuccessful." << endl << endl;
        }
        else {
          SubAccount :: subWithdraw(withdrawAmount);
        }  
      } 
      else {
        cout << "Please enter an avaible numbers!" << endl << endl;
      }
    }
    else {
      cout << "Sub-Account is locked!" << endl << endl;
    }
    cin.clear();
    cin.ignore();
  }

  void printCheckMenu(){
    string userInput;
    cout << "Eligible services for sub-account " << getSubAccountNum() << endl;
    cout << "  D -- Deposit"<< endl;
    cout << "  W -- Withdraw" <<  endl;
    cout << "  C -- Max Capacity" << endl;
    cout << "  L -- Lock Sub-Account" << endl;
    cout << "  U -- Unlock Sub-Account" << endl;
    cout << "  X -- Exit" << endl;
    cout << "Please enter your selection: ";
    cin >> userInput;
    if (userInput == "d" || userInput == "D"){ 
      checkDeposit();
      printCheckMenu();
    }
    else if (userInput == "w" || userInput == "W"){
      checkWithdraw(); 
      printCheckMenu();
    }
    else if (userInput == "c" || userInput == "C"){
      string choice;
      cout<<"Your current max capacity is : "<<getMaxCap()<<endl;
      cout<<"Do you wish to change your max capacity ?"<<endl;
      cout<<"Please enter: "<<endl;
      cout<<" y -- yes"<<endl;
      cout<<" n -- no"<<endl;
      cin>>choice;
      cin.ignore();
      if(choice == "y" || choice == "Y"){
        cout<<"Enter your new maximum capacity: ";
        cin>>maxCap;
        cin.ignore();
        setMaxCap(maxCap);
        cout<<"Your new maximum capacity is "<< getMaxCap()<<endl;
        printCheckMenu();
      } else if (choice == "n" || choice == "N")  {
        printCheckMenu();
      } else {
        cout<<"Please enter the valid input :";
        cin>>choice;
      }  
      
    }
    else if (userInput == "l" || userInput == "L"){
      setIsLock(true);
      cout << "The Sub-Account " << getSubAccountNum() << " is locked!" << endl << endl;
      printCheckMenu();
    }
    else if (userInput == "u" || userInput == "U"){
      setIsLock(false);
      cout << "The Sub-Account " << getSubAccountNum() << " is unlocked!" << endl << endl;
      printCheckMenu();
    }
    else if (userInput == "x" || userInput == "X"){
      cout << "End of service for sub-account " << getSubAccountNum() << endl << endl;
      return;
    }
    else {
      cout << "Please make another selection!" << endl;
      printCheckMenu();
    }
  }


protected:
  int maxCap;
  bool isLock;
};
#endif