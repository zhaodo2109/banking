#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <vector>
#include "account.h"
#include <cstdlib>
using namespace std;


class Bank {
public:
  Bank(){
    name = "NA";
    hour = "NA";
    address = "NA";
    accountSize = 0;
  }
  Bank(string nm, string hr, string ar){
    name = nm;
    hour = hr;
    address = ar;
    accountSize = 0;
  }

  void setName(string name) {
    this -> name = name;
  }
  void setAddress(string address) {
    this -> address = address;
  }
  void setBankHour(string hour) {
    this -> hour = hour;
  }
  string getName() const {return this-> name;}
  string getAddress() const {return this -> address;}
  string getHour() const {return this -> hour;}

  void printMenu() {
    string userInput;
    cout << "Eligible services for " << getName() << endl;
    cout << "  A -- Number of Bank-Accounts " << endl;
    cout << "  S -- Number of Saving-Accounts" << endl;
    cout << "  H -- Number of Checking-Accounts" << endl;
    cout << "  O -- Open Bank-Account" << endl;
    cout << "  C -- Close Bank-Account" << endl;
    cout << "  M -- Modify Bank-Account" << endl;
    cout << "  D -- Detailed Bank-Accounts" << endl;
    cout << "  B -- Brief Bank-Account Info Sorted Based on Aggregated Balances" << endl;
    cout << "  X -- Exit" << endl;

    cout << "Please enter your selection: ";
    cin >> userInput;
    cout << endl;
    if (userInput == "a" || userInput == "A"){ 
      cout << "The number of Bank-Accounts is " << getNumBankAccount() << endl << endl;
      printMenu();
    }
    else if (userInput == "s" || userInput == "S"){
      cout << "The number of Saving-Accounts is " << getBankNumSaving() << endl << endl;
      printMenu();
    }
    else if (userInput == "h" || userInput == "H"){
      cout << "The number of Checking-Accounts is " << getBankNumChecking() << endl << endl;
      printMenu();
    }
    else if (userInput == "o" || userInput == "O"){
      openBankAccount();
      printMenu();
    }
    else if (userInput == "c" || userInput == "C"){
      closeBankAccount();
      printMenu();
    }
    else if (userInput == "m" || userInput == "M"){
      modBankAccount();
      printMenu();
    }
    else if (userInput == "d" || userInput == "D"){
      printDetailBankAccount();
      printMenu();
    }
    else if (userInput == "b" || userInput == "B"){
      printBriefBankAccount();
      printMenu();
    }
    else if (userInput == "x" || userInput == "X"){
      cout << "End of service for " << getName() << endl;
      return;
    }
    else {
      cout << "Please make another selection!" << endl << endl;
      printMenu();
    }
  }

  bool checkSSN(string input){
    for (char c : input) {
      if (!isdigit(c)) {
        return false;
      }
    }
    return true;
  }
  
  int getBankBalance(){
    int bankBalance = 0;
    for (int i = 0; i < accountArray.size(); i++){
      bankBalance = bankBalance + accountArray[i].getAccountBalance();
    }
    return bankBalance;
  }

  void printInfo() { 
    cout << "Name of the Bank: " << getName() << endl;
    cout << "Address of the Bank: " << getAddress() << endl;
    cout << "Working hour: " << getHour() << endl;
    cout << "Aggregated Balance: " << getBankBalance() << endl;
    cout << "Consist of " << getNumBankAccount() << " Bank-Accounts" << endl << endl;
  }

  int getNumBankAccount(){
    return accountSize;
  }

  int getBankNumSaving(){
    int num = 0;
    for (int i = 0; i < accountSize; i++){
      num = num + accountArray[i].getNumSave();
    }
    return num;
  }

  int getBankNumChecking(){
    int num = 0;
    for (int i = 0; i < accountArray.size(); i++){
      num = num + accountArray[i].getNumCheck();
    }
    return num;
  }

  void openBankAccount(){
    string accountNumber;
    string holderFirstName;
    string holderLastName;
    string holderSSN;
    string choice;
    static int initialAccountNumber = 1000;

    cin.ignore();
    cout << "Enter the first name of the account holder: ";
    getline(cin,holderFirstName);

    //cin.ignore();
    cout << "Enter the last name of the account holder: ";
    getline(cin,holderLastName);
    
    cout << "Enter the SSN of the account holder: ";
    cin>>holderSSN;
    //cin.ignore();
    while(checkSSN(holderSSN)==false){
      cout<<"Invalid SSN"<<endl;
      cout<<"Enter :"<<endl;
      cout<<" X -- to exit to main menu"<<endl;
      cout<<" C -- to continue"<<endl;
      cin>>choice;
      if(choice=="c"||choice=="C"){
        cout <<"Please enter valid SSN : ";
        cin>>holderSSN;
      } else if (choice=="x"||choice=="X") {
        printMenu();
      } else {
        cout<<"Please enter valid input : ";
        cin>>choice;
      }
      
    }

    accountNumber = "BNK";
    //initialAccountNumber = 1000;
    accountNumber.append(to_string(initialAccountNumber));
    for (int i = 0; i < accountArray.size(); i++){
      while (accountNumber == accountArray[i].getAccountNum()) {
        accountNumber.append(to_string(initialAccountNumber));
      }
    }

    Account newAcc;
    newAcc = Account(accountNumber, holderFirstName, holderLastName, holderSSN);
    accountArray.push_back(newAcc);
  
    cout << "A new bank account " << accountArray[accountArray.size()].getAccountNum() << " was successfully created." << endl << endl;
    accountSize++;
    initialAccountNumber++;
    accountArray[accountArray.size()-1].printAccountMenu();
  }

  void closeBankAccount(){
    string choice;
    string accountNumber;    
    bool available = true;
    cout << "Enter Account Number to close: ";
    cin >> accountNumber;

    for (int i = 0; i < accountArray.size(); i++) {
      if (accountNumber == accountArray[i].getAccountNum()) {
        if (accountArray.size() > 1){
          string num = accountArray[i].getAccountNum();
          accountArray.erase(accountArray.begin() + i);
          available = true;
          cout << "Account " << num << " was successfully closed." << endl << endl;
         accountSize--;
          break;
        }
        else {
          string num = accountArray[i].getAccountNum();
          accountArray.clear();
          available = true;
          cout << "Account " << num << " was successfully closed."<< endl << endl;
          accountSize--;
          break;
        }
      } else {
        available=false;
        break;
      }
    }

    while (available == false) {
      cout << "Account Number is unavailable!" << endl;
      cout<<endl;
      cout<<"Please enter :" << endl; 
      cout<< " x if you don't have an account" <<endl; 
      cout<< " c to continue" <<endl;
      cin>>choice;
      if ( choice == "c" || choice == "C"){
        cout << "Please enter valid Account Number: ";
        cin>>accountNumber;
        cout<<endl;
      } else if (choice == "x" || choice == "X"){
        break;
      }
    }
  }

  void modBankAccount(){
    string choice;
    bool found = true;
    string accountNumber;
    cout << "Enter Account Number to modify: ";
    cin >> accountNumber;
    cin.ignore();
    for (int i = 0; i < accountArray.size(); i++){
      if (accountNumber == accountArray[i].getAccountNum()){
        accountArray[i].printAccountMenu();
        found=true;
        break;
      } else {
        cout<< endl;
        found=false;
        break;
        }
      }
    

    while (found == false) {
      cout << "Account Number is unavailable!" << endl;
      cout<<endl;
      cout<<"Please enter :" << endl; 
      cout<< " x if you don't have an account" <<endl; 
      cout<< " c to continue" <<endl;
      cin>>choice;
      cin.ignore();
      if ( choice == "c" || choice == "C"){
        cout << "Please enter valid Account Number: ";
        cin>>accountNumber;
        cout<<endl;
      } else if (choice == "x" || choice == "X"){
        break;
      }
    }
    
  }  

  void printDetailBankAccount(){
    printInfo();
    for (int i = 0; i < accountArray.size(); i++){
      accountArray[i].printDetail();
    }
    cout << endl;
  }

  void printBriefBankAccount(){
    printInfo(); 
    for (int i = 0; i < accountArray.size(); i++){
      int j = i;
       while (j > 0 && accountArray[j].getAccountBalance() > accountArray[i - 1].getAccountBalance()){
         swap(accountArray[i], accountArray[i - 1]);
         j--;
       }
    }

    for (int i = 0; i < accountArray.size(); i++){
      cout << "Aggregated Balance of the bank account: " << accountArray[i].getAccountNum() << " with " <<  accountArray[i].getNumSubAccount() << " is " << accountArray[i].getAccountBalance() << endl << endl;
    }
  }

protected:
  string name;
  string hour;
  string address;
  vector<Account> accountArray;
  int accountSize;
};
#endif