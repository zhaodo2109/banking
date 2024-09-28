#ifndef SUBACCOUNT_H
#define SUBACCOUNT_H
#include <string>
#include <iostream>
using namespace std;

class SubAccount{
public:
  SubAccount(){
    subAccountNum = "NA";
    subAccountBalance = 0;
  }

  SubAccount(string num, int balance){
    this -> subAccountNum = num;
    this -> subAccountBalance = balance;
  }

  void setSubAccountNum(string subAccountNum){this -> subAccountNum = subAccountNum;}
  void setSubAccountBalance(int subAccountBalance){this -> subAccountBalance = subAccountBalance;}

  string getSubAccountNum() const {return subAccountNum;}
  int getSubAccountBalance() const {return subAccountBalance;}

  void printSubAccountInfo(){
    cout << "Sub-Account Number: " << getSubAccountNum() << endl;
    cout << "Balance: " << getSubAccountBalance() << endl;
  }

  void subDeposit(int depositAmount){
    setSubAccountBalance(getSubAccountBalance() + depositAmount);
    cout << "The deposit was succesful."<< endl;
    cout << "The current balance is " << getSubAccountBalance() << endl << endl;
  }

  void subWithdraw(int withdrawAmount){
    if(getSubAccountBalance() >= withdrawAmount){
      setSubAccountBalance(getSubAccountBalance() - withdrawAmount);
      cout<< "The withdraw was succesful." << endl;
      cout << "The current balance is " << getSubAccountBalance() << endl << endl;
    } 
    else {
      cout << "Low balance" << endl;
      cout << "The withdraw was uncussesful."<<endl << endl;
    }  
  }


protected:
  string subAccountNum;
  int subAccountBalance;
};
#endif