#include<bits/stdc++.h>
using namespace std;

// Abstract Class: Medicine
class Medicine{
protected:
    string name;
    int quantity;
    double price;

public: 
    Medicine(string n , int q , double p):name(n) , quantity(q),price(p){}

virtual void showDetails() = 0; // Polymorphism

    string getName(){return name;}
    int getQuantity(){return quantity;}
    double getPrice(){return price;}

    void updateQuantity(int q){
        quantity = q;
    }

    bool reduceStock(int q){
        if(q<=quantity){
            quantity -= q;
            return true;
        }
        return false;
    }

    virtual ~Medicine(){}
};

//Derived class
class Antibiotic : public Medicine{
public:
    Antibiotic(string n , int q , double p):Medicine(n,q,p){}

    void showDetails() override{
        cout<<"[Antibiotic] "<<name
        << "| Stock: "<<quantity
        << "| Price: $"<<price<<endl;
    }
};

class Painkiller : public Medicine
{
public:
    Painkiller(string n, int q, double p) : Medicine(n, q, p) {}

    void showDetails() override{
        cout << "[Painkiller] " << name
        << " | Stock: " << quantity
        << " | Price: $" << price << endl;
    }
};

//Billing class
class Bill{
    double totalAmount =0;
public:
    void additem(double price,int qty){
        totalAmount += (price*qty);
    }

    void generate(){
        cout << "\n------ BILL ------" << endl;
        cout << "Total Payable: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "------------------" << endl;
    }
};


//Pharmacy class
class Pharmacy{
    vector<Medicine*> items;

public:
    void addMedicine(Medicine* m){
        items.push_back(m);
        cout<< "Medicine added successfully!\n";
    }

    void showAll(){
        cout<<"\n---- Medicine List ---"<<endl;
        for(auto m : items){
            m->showDetails();
        }
    }

    void purchaseMedicine(){
        string med;
        int qty;
        Bill bill;

        cout << "\nEnter medicine name to purchase: ";
        cin >> med;
        cout << "Enter quantity: ";
        cin >> qty;

        for (auto m : items){
            if (m->getName() == med){
                if (m->reduceStock(qty)){
                    bill.additem(m->getPrice(), qty);
                    cout << "Purchase successful!" << endl;
                }
                else{
                    cout << "Insufficient stock!" << endl;
                }
                bill.generate();
                return;
            }
        }
        cout << "Medicine not found!" << endl;
    }
};

int main(){
    Pharmacy ph;
    int choice;

    do{
        cout << "\n===== Pharmacy Management System =====" << endl;
        cout << "1. Add Medicine" << endl;
        cout << "2. Show All Medicines" << endl;
        cout << "3. Purchase Medicine" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1){
            int type,qty;
            double price;
            string name;

            cout << "Select Type: 1. Antibiotic  2. Painkiller: ";
            cin >> type;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Quantity: ";
            cin >> qty;
            cout << "Enter Price: ";
            cin >> price;

            if(type == 1){
                ph.addMedicine(new Antibiotic(name,qty,price));
            }
            else{
                ph.addMedicine(new Painkiller(name,qty,price));
            }
        }

        else if(choice == 2){
            ph.showAll();
        }

        else if(choice == 3){
            ph.purchaseMedicine();
        }
    }
    while(choice != 4);

    cout<<"Thank You!"<<endl;
    return 0;
}


