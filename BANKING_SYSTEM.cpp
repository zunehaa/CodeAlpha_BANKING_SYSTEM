#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<iomanip>
#include<algorithm>
using namespace std;

class Transaction{
private:
    string transactionId;
    string type;
    double amount;
    string date;
    string description;

public:
    Transaction(string t,double a,string desc=""):type(t),amount(a),description(desc){
        transactionId="TXN"+to_string(rand()%10000+1000);
        time_t now=time(0);
        date=ctime(&now);
        date.pop_back(); // Remove the annoying newline
    }

    void display() const{
        cout<<left<<setw(12)<<transactionId<<setw(15)<<type<<setw(10)<<fixed<<setprecision(2)<<amount<<setw(30)<<date<<description<<endl;
    }
    string getType() const{return type;}
    double getAmount() const{return amount;}
    string getDate() const{return date;}
    string getDescription() const{return description;}
    string getTransactionId() const{return transactionId;}
};

class Account{
private:
    string accountNumber;
    string accountType;
    double balance;
    string customerId;
    vector<Transaction> transactions;

public:
    Account(string accNum,string accType,string custId,double initialBalance=0.0):accountNumber(accNum),accountType(accType),customerId(custId),balance(initialBalance){}

    void deposit(double amount,string description = ""){
        if(amount<=0){
            cout<<"COME ON, YOU CAN'T DEPOSIT NEGATIVE MONEY!!!"<<endl;
            return;
        }
        balance+=amount;
        transactions.emplace_back("DEPOSIT",amount,description);
        cout<<"MONEY ADDED..NEW BALANCE: "<<balance<<endl;
    }

    bool withdraw(double amount,string description=""){
        if(amount<=0){
            cout<<"WITHDRAWAL AMOUNT MUST BE POSITIVE!!"<<endl;
            return false;
        }
        if(balance>=amount){
            balance-=amount;
            transactions.emplace_back("WITHDRAWAL",amount,description);
            cout<<"CASH WITHDRAWN..NEW BALANCE: "<<balance<<endl;
            return true;
        }
        cout<<"OOPS, NOT ENOUGH MONEY!!"<<endl;
        return false;
    }

    bool transfer(Account &toAccount,double amount,string description=""){
        if(amount<=0){
            cout<<"YOU CAN'T TRANSFER AIR!!"<<endl;
            return false;
        }
        if(this->withdraw(amount,"TRANSFER TO "+toAccount.getAccountNumber())){
            toAccount.deposit(amount,"TRANSFER FROM "+accountNumber);
            return true;
        }
        return false;
    }

    void display() const{
        cout<<"ACCOUNT #: "<<accountNumber<<endl;
        cout<<"TYPE: "<<accountType<<endl;
        cout<<"BALANCE: $"<<fixed<<setprecision(2)<<balance<<endl;
    }

    void showTransactions(int limit=10) const{
        cout<<"\nLAST "<<limit<<" TRANSACTIONS FOR "<<accountNumber<<":\n";
        cout<<left<<setw(12)<<"ID"<<setw(15)<<"TYPE"<<setw(10)<<"AMOUNT"<<"DESCRIPTION\n";
        
        int start=max(0,(int)transactions.size()-limit);
        for(size_t i=start;i<transactions.size();i++){
            transactions[i].display();
        }
    }

    string getAccountNumber() const{return accountNumber;}
    double getBalance() const{return balance;}
    string getAccountType() const{return accountType;}
    string getCustomerId() const{return customerId;}
};

class Customer{
private:
    string customerId;
    string name;
    string address;
    string phone;
    vector<Account*> accounts;

public:
    Customer(string custId,string n,string addr="",string ph=""):customerId(custId),name(n),address(addr),phone(ph){}
    ~Customer(){
        for(auto acc:accounts)delete acc;
    }

    Account* openAccount(string type,double initialDeposit=0.0){
        string accNum="ACC"+to_string(rand()%90000+10000);
        Account* newAcc=new Account(accNum,type,customerId,initialDeposit);
        accounts.push_back(newAcc);
        return newAcc;
    }

    void showInfo() const{
        cout<<"\nCUSTOMER: "<<name<<" ("<<customerId<<")\n";
        cout<<"CONTACT: "<<phone<<" | "<<address<<"\n";
        cout<<"ACCOUNTS: "<<accounts.size()<<endl;
    }

    void listAccounts() const{
        for(const auto& acc:accounts){
            acc->display();
            cout<<endl;
        }
    }

    Account* findAccount(string accNum){
        for(auto acc:accounts){
            if(acc->getAccountNumber()==accNum)return acc;
        }
        return nullptr;
    }

    // More getters
    string getId() const{return customerId;}
    string getName() const{return name;}
};

class Bank{
private:
    vector<Customer*>clients;
public:
    ~Bank(){
        for(auto cust:clients)delete cust;
    }

    Customer* addCustomer(string name,string addr="",string phone=""){
        string id="CUST"+to_string(rand()%9000+1000);
        Customer* newCust=new Customer(id,name,addr,phone);
        clients.push_back(newCust);
        return newCust;
    }

    Customer* findCustomer(string id){
        for(auto cust:clients){
            if(cust->getId()==id)return cust;
        }
        return nullptr;
    }
    Account* findAccount(string accNum){
        for(auto cust:clients){
            Account* acc=cust->findAccount(accNum);
            if(acc)return acc;
        }
        return nullptr;
    }

    void listCustomers() const{
        cout<<"\nOUR VALUED CUSTOMERS:\n";
        for(const auto& cust:clients){
            cust->showInfo();
            cout<<endl;
        }
    }
};

void showMenu(){
    cout<<"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout<<"|          Bank Menu:          |";
    cout<<"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout<<"1. NEW CUSTOMER\n2. OPEN ACCOUNT\n3. DEPOSIT\n4. WITHDRAW\n5. TRANSFER\n6. VIEW CUSTOMER\n7. VIEW ACCOUNT\n8. TRANSACTION HISTORY\n9. CUSTOMERS INFORMATION\n0. EXIT\n";
    cout<<"CHOICE: ";
}

int main(){
    Bank myBank;
    srand(time(0));
    cout<<"\n\nWELCOME TO BANK!!\n";
    int choice;
    do{
        showMenu();
        cin>>choice;
        cin.ignore();
        switch(choice){
            case 1:{
                string name,addr,phone;
                cout<<"NAME: ";getline(cin,name);
                cout<<"ADDRESS: ";getline(cin,addr);
                cout<<"PHONE: ";getline(cin,phone);
                Customer* newCust=myBank.addCustomer(name,addr,phone);
                cout<<"CUSTOMER ID: "<<newCust->getId()<<endl;
                break;
            }
            case 2:{
                string custId;
                cout<<"CUSTOMER ID: ";getline(cin,custId);
                Customer* cust=myBank.findCustomer(custId);
                if(cust){
                    string type;
                    double init;
                    cout<<"ACCOUNT TYPE: ";getline(cin,type);
                    cout<<"INITIAL DEPOSIT: ";cin>>init;cin.ignore();
                    Account* acc=cust->openAccount(type,init);
                    cout<<"ACCOUNT #: "<<acc->getAccountNumber()<<endl;
                } 
                else{
                    cout<<"CUSTOMER NOT FOUND!!\n";
                }
                break;
            }
            case 3:{
                string accNum;
                double amt;
                cout<<"ACCOUNT #: ";getline(cin,accNum);
                cout<<"AMOUNT: ";cin>>amt;cin.ignore();
                Account* acc=myBank.findAccount(accNum);
                if(acc)acc->deposit(amt);
                else cout<<"ACCOUNT NOT FOUND!!\n";
                break;
            }
            case 4:{
                string accNum;
                double amt;
                cout<<"ACCOUNT #: ";getline(cin,accNum);
                cout<<"AMOUNT: ";cin>>amt;cin.ignore();
                Account* acc=myBank.findAccount(accNum);
                if(acc)acc->withdraw(amt);
                else cout<<"ACCOUNT NOT FOUND!!\n";
                break;
            }
            case 5:{
                string from,to;
                double amt;
                cout<<"FROM ACCOUNT #: ";getline(cin,from);
                cout<<"TO ACCOUNT #: ";getline(cin,to);
                cout<<"AMOUNT: ";cin>>amt;cin.ignore();
                Account* src=myBank.findAccount(from);
                Account* dst=myBank.findAccount(to);
                if(src&&dst)src->transfer(*dst,amt);
                else cout<<"ONE OR BOTH ACCOUNTS NOT FOUND!!\n";
                break;
            }
            case 6:{
                string custId;
                cout<<"CUSTOMER ID: ";getline(cin,custId);
                Customer* cust=myBank.findCustomer(custId);
                if(cust){
                    cust->showInfo();
                    cust->listAccounts();
                } 
                else cout<<"CUSTOMER NOT FOUND!!\n";
                break;
            }
            case 7:{
                string accNum;
                cout<<"ACCOUNT #: ";getline(cin,accNum);
                Account* acc=myBank.findAccount(accNum);
                if(acc)acc->display();
                else cout<<"ACCOUNT NOT FOUND!!\n";
                break;
            }
            case 8:{
                string accNum;
                int limit;
                cout<<"ACCOUNT #: ";getline(cin,accNum);
                cout<<"MAX TRANSACTIONS TO SHOW: ";cin>>limit;cin.ignore();
                Account* acc=myBank.findAccount(accNum);
                if(acc)acc->showTransactions(limit);
                else cout<<"ACCOUNT NOT FOUND!!\n";
                break;
            }
            case 9:{
                myBank.listCustomers();
                break;
            }
            case 0:{
                cout<<"THANKS FOR BANKING WITH US>>>>\n";
                break;
            }
            default:cout<<"INVALID CHOICE!!\n";
        }
    }while(choice!=0); 
    return 0;
}