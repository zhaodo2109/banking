#include <iostream>
#include <string>
#include "bank.h"
#include <algorithm>
using namespace std;


int main(){

  string bankname;
  string bankhour;
  string address;

  cout<<"Enter your financial institution : ";
  getline(cin,bankname);

  cout<<"Enter the address of the bank: ";
  getline(cin,address);

  cout<<"Enter working hours : ";
  getline(cin,bankhour);
  cout<<endl;
  
  Bank newBank;
  newBank = Bank(bankname, bankhour, address);
  newBank.printMenu();

return 0;
}
