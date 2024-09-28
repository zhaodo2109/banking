#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "checking.h"
#include "saving.h"
#include <string>
#include <vector>
using namespace std;

const long maxAccount = 1000;

class Account {
public:
  Account() {
    holderFirstName = "N/A";
    holderLastName = "N/A";
    holderSSN = "N/A";
    bankAccountNumber = "N/A";
    accountBalance = 0;
    numSubAcount = 0;
  }

  Account(string num, string fn, string ln, string SSN) {
    bankAccountNumber = num;
    holderFirstName = fn;
    holderLastName = ln;
    holderSSN = SSN;
  }

  // check valid input
  /*bool checkarea(string area) {
    bool check = true;
    for (unsigned int i = 0; i < area.size(); i++) {
      if (!isdigit(area.at(i))) {
        check = false;
      }
    }
    if (check == false) {
      return false;
    } else {
      return true;
    }
  }*/

  void setFirstName(string holderFirstName) {
    this->holderFirstName = holderFirstName;
  }
  void setLastName(string holderLastName) {
    this->holderLastName = holderLastName;
  }
  void setSSN(string holderSSN) { 
    this->holderSSN = holderSSN; 
  }
  void setAccountNum(string bankAccountNumber) {
    this->bankAccountNumber = bankAccountNumber;
  }
  void setBalance(int accountBalance) { 
    this->accountBalance = accountBalance; 
  }
  void setNumSubAccount(int numSubAcount) { 
    this->numSubAcount = numSubAcount; 
  }

  string getFirstName() const { 
    return this->holderFirstName; 
  }
  string getLastName() const { 
    return this->holderLastName; 
  }
  string getSSN() const { 
    return this->holderSSN; 
  }
  string getAccountNum() const {
    return this->bankAccountNumber; 
  }

  int getAccountBalance() const {
    int balance = 0;
    for (int i = 0; i < savingArray.size(); i++) {
      balance = balance + savingArray[i].getSubAccountBalance();
    }
    for (int i = 0; i < checkingArray.size(); i++) {
      balance = balance + checkingArray[i].getSubAccountBalance();
    }
    return balance;
  };

  int getNumSubAccount() const {
    return savingArray.size() + checkingArray.size();
  };

  void printDetail() {
    cout << "Bank Account Number: " << getAccountNum() << endl;
    cout << "Account Holder Full Name: " << getFirstName() << " "
         << getLastName() << endl;
    cout << "Aggreated Balance: " << getAccountBalance() << endl;
    cout << "Consist of " << getNumSubAccount() << " Sub-Accounts" << endl
         << endl;
    printInfoBalanceSorted();
  }

  int getNumSave() { return savingArray.size(); }

  int getNumCheck() { return checkingArray.size(); }

  void openSavingSubAccount() {
    string accountNumber;
    int initialBalance;
    static int inSavAccNum=1000;

    cout << "Enter the initial balance: ";
    cin >> initialBalance;
    cout << endl;
    accountNumber = "SAV";
    //initialAccountNumber = rand() % 1000;
    accountNumber.append(to_string(inSavAccNum));
    for (int i = 0; i < savingArray.size(); i++) {
      while (accountNumber == savingArray[i].getSubAccountNum()) {
        accountNumber.append(to_string(inSavAccNum));
      }
    }

    Saving newSaving;
    newSaving = Saving(accountNumber, initialBalance);
    savingArray.push_back(newSaving);
    
    
    cout << "A new Saving Sub-Account "
         << savingArray[savingArray.size() - 1].getSubAccountNum()
         << " was successfully created." << endl
         << endl;
    inSavAccNum++;
  }

  void openCheckingSubAccount() {
    string accountNumber;
    int maxCap;
    string lockChar;
    bool isLock;
    int initialBalance;
    static int inChkAccNum=1000;

    cout << "Enter the initial balance: ";
    cin >> initialBalance;
    cout << "Enter the desired maximun capacity: ";
    cin >> maxCap;
    cout << "Define intial state: (L - Locked, Otherwise - Unlocked) ";
    cin >> lockChar;
    if (lockChar == "l" || lockChar == "L") {
      isLock = true;
    } else {
      isLock = false;
    }

    cout << endl;
    accountNumber = "CHK";
    accountNumber.append(to_string(inChkAccNum));
    for (int i = 0; i < checkingArray.size(); i++) {
      while (accountNumber == checkingArray[i].getSubAccountNum()) {
        accountNumber.append(to_string(inChkAccNum));
      }
    }

    Checking newChecking;
    newChecking = Checking(accountNumber, initialBalance, maxCap, isLock);
    checkingArray.push_back(newChecking);
    
    cout << "A new Checking Sub-Account "
         << checkingArray[checkingArray.size() - 1].getSubAccountNum()
         << " was successfully created." << endl
         << endl;
    inChkAccNum++;
  }

  void printInfoBalanceSorted() {
    int size = savingArray.size() + checkingArray.size();
    SubAccount subArray[size];
    for (int i = 0; i < savingArray.size(); i++) {
      subArray[i].setSubAccountBalance(savingArray[i].getSubAccountBalance());
      subArray[i].setSubAccountNum(savingArray[i].getSubAccountNum());
    }
    
    for (int i = 0 + savingArray.size(); i < size; i++) {
      subArray[i].setSubAccountBalance(checkingArray[i - savingArray.size()].getSubAccountBalance());
      subArray[i].setSubAccountNum(checkingArray[i - savingArray.size()].getSubAccountNum());
    }

    for (int i = 0; i < size; i++) {
      int j = i;
      while (j > 0 && subArray[j].getSubAccountBalance() > subArray[j - 1].getSubAccountBalance()) {
        swap(subArray[j], subArray[j - 1]);
        j--;
      }
    }

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < savingArray.size(); j++) {
        if (subArray[i].getSubAccountNum() == savingArray[j].getSubAccountNum()) {
          savingArray[j].printSaveInfo();
        }
      }
      for (int j = 0; j < checkingArray.size(); j++) {
        if (subArray[i].getSubAccountNum() == checkingArray[j].getSubAccountNum()) {
          checkingArray[j].printCheckInfo();
        }
      }
    }
  }

  void modSubAccount() {
    string choice;
    bool found = false;
    string subAccountNumber;
    cout << "Enter Sub-Account Number to modify: ";
    cin >> subAccountNumber;
    for (int i = 0; i < savingArray.size(); i++) {
      if (subAccountNumber == savingArray[i].getSubAccountNum()) {
        found = true;
        savingArray[i].printSaveMenu();
        break;
      }
    }
    for (int i = 0; i < checkingArray.size(); i++) {
      if (subAccountNumber == checkingArray[i].getSubAccountNum()) {
        found =true;
        checkingArray[i].printCheckMenu();
        break;
      }
    }

    while (found == false) {
      cout << "Sub-Account Number is unavailable!" << endl;
      cout<<endl;
      cout<<"Please enter :" << endl; 
      cout<< " x if you don't have an account" <<endl; 
      cout<< " c to continue" <<endl;
      cin>>choice;
      if ( choice == "c" || choice == "C"){
        cout << "Please enter valid Sub-Account Number: ";
        cin>>subAccountNumber;
        cout<<endl;
      } else if (choice == "x" || choice == "X"){
        break;
      }
      
      
    }
    
  }

  void closeSubAccount() {
    string choice;
    string accountNumber;
    bool available = false;
    cout << "Enter Sub-Account Number to close: ";
    cin >> accountNumber;
    
    for (int i = 0; i < savingArray.size(); i++) {
      if (accountNumber == savingArray[i].getSubAccountNum()) {
        if (savingArray.size() > 1){
          string num = savingArray[i].getSubAccountNum();
          savingArray.erase(savingArray.begin() + i);
          available = true;
          
          cout << "A Saving Sub-Account " << num << " was successfully closed." << endl << endl;
          break;
        }
        else {
          string num = savingArray[i].getSubAccountNum();
          savingArray.clear();
          available = true;
          
          cout << "A Saving Sub-Account " << num << " was successfully closed." << endl << endl;
          break;
        }
      }
    }
    for (int i = 0; i < checkingArray.size(); i++) {
      if (accountNumber == checkingArray[i].getSubAccountNum()) {
        if (checkingArray.size() > 1){
          string num = checkingArray[i].getSubAccountNum();
          checkingArray.erase(checkingArray.begin() + i);
          available = true;
          
          cout << "A Checking Sub-Account " << num << " was successfully closed." << endl << endl;
          break;
        } else {
          string num = savingArray[i].getSubAccountNum();
          savingArray.clear();
          available = true;
          
          cout << "A Saving Sub-Account " << num << " was successfully closed." << endl << endl;
          break;
        }
      }  
    }
    
    while (available == false) {
      cout << "Sub-Account Number is unavailable!" << endl;
      cout<<endl;
      cout<<"Please enter :" << endl; 
      cout<< " x if you don't have an account" <<endl; 
      cout<< " c to continue" <<endl;
      cin>>choice;
      if ( choice == "c" || choice == "C"){
        cout << "Please enter valid Sub-Account Number: ";
        cin>>accountNumber;
        cout<<endl;
      } else if (choice == "x" || choice == "X"){
        break;
      }
      
      
    }
  }

  void printAccountMenu() {
    string userInput;
    cout << "Eligible services for Bank-Account " << getAccountNum() << endl;
    cout << "  S -- Open Saving-Sub Account" << endl;
    cout << "  C -- Open Checking-Sub Account" << endl;
    cout << "  M -- Modify a Sub-Account" << endl;
    cout << "  E -- Close a Sub-Account" << endl;
    cout << "  D -- Detailed Bank Account Info Sorted on Balances of "
            "Sub-Accounts"
         << endl;
    cout << "  B -- Brief Bank Account Info" << endl;
    cout << "  X -- Exit" << endl;

    cout << "Please enter your selection: ";
    cin >> userInput;
    cout << endl;
    if (userInput == "s" || userInput == "S") {
      openSavingSubAccount();
      printAccountMenu();
    } else if (userInput == "c" || userInput == "C") {
      openCheckingSubAccount();
      printAccountMenu();
    } else if (userInput == "m" || userInput == "M") {
      modSubAccount();
      printAccountMenu();
    } else if (userInput == "e" || userInput == "E") {
      closeSubAccount();
      printAccountMenu();
    } else if (userInput == "d" || userInput == "D") {
      printInfoBalanceSorted();
      printAccountMenu();
    } else if (userInput == "b" || userInput == "B") {
      cout << "Aggregated Balance of the bank account : " << getAccountNum()
           << " with " << getNumSubAccount() << " Sub-Accounts is "
           << getAccountBalance() << endl
           << endl;
      printAccountMenu();
    } else if (userInput == "x" || userInput == "X") {
      cout << "End of services for bank-account " << getAccountNum() << endl
           << endl;
      //getAccountNum().PrintMenu();
      return;
    } else {
      cout << "Please make another selection!" << endl << endl;
      printAccountMenu();
    }
  }

protected:
  string holderFirstName;
  string holderLastName;
  string holderSSN;
  string bankAccountNumber;
  int accountBalance;
  int numSubAcount;
  
  

  vector<Saving> savingArray;

  vector<Checking> checkingArray;
};
#endif