#include <bits/stdc++.h>
using namespace std;

// ---------------- Abstract Class: Medicine ----------------
// This class serves as a blueprint for all medicines.
// It contains common attributes like name, quantity, and price.
class Medicine{
protected:
    string name;
    int quantity;
    double price;

public:
    // Constructor to initialize medicine details
    Medicine(string n, int q, double p) : name(n), quantity(q), price(p) {}

    // Pure virtual function (abstract function)
    virtual void showDetails() = 0; // Enables runtime polymorphism

    // Getter functions
    string getName() { return name; }
    int getQuantity() { return quantity; }
    double getPrice() { return price; }

    // Update quantity
    void updateQuantity(int q){
        quantity = q;
    }

    // Reduce stock after purchase
    bool reduceStock(int q){
        if (q <= quantity){
            quantity -= q;
            return true;
        }
        return false; // If not enough stock
    }

    // Virtual destructor for safe cleanup
    virtual ~Medicine() {}
};

// ---------------- Derived Class: Antibiotic ----------------
class Antibiotic : public Medicine{
public:
    // Constructor using base class initializer list
    Antibiotic(string n, int q, double p) : Medicine(n, q, p) {}

    // Display details of antibiotic
    void showDetails() override{
        cout << "[Antibiotic] " << name
             << " | Stock: " << quantity
             << " | Price: $" << price << endl;
    }
};

// ---------------- Derived Class: Painkiller ----------------
class Painkiller : public Medicine{
public:
    Painkiller(string n, int q, double p) : Medicine(n, q, p) {}

    // Display details of painkiller
    void showDetails() override{
        cout << "[Painkiller] " << name
             << " | Stock: " << quantity
             << " | Price: $" << price << endl;
    }
};

// ---------------- Class: Bill ----------------
// Responsible for calculating and displaying total bill
class Bill{
    double totalAmount = 0;

public:
    // Add item to bill
    void additem(double price, int qty){
        totalAmount += (price * qty);
    }

    // Generate final bill
    void generate(){
        cout << "\n------ BILL ------" << endl;
        cout << "Total Payable: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "------------------" << endl;
    }
};

// ---------------- Class: Pharmacy ----------------
// Manages list of medicines, adding, showing, and purchasing
class Pharmacy{
    vector<Medicine *> items; // Stores all medicines (using base class pointer)

public:
    // Add a new medicine to inventory
    void addMedicine(Medicine *m){
        items.push_back(m);
        cout << "Medicine added successfully!\n";
    }

    // Display all medicines in stock
    void showAll(){
        cout << "\n---- Medicine List ----" << endl;
        for (auto m : items){
            m->showDetails();
        }
    }

    // Purchase medicine by name
    void purchaseMedicine(){
        string med;
        int qty;
        Bill bill;

        cout << "\nEnter medicine name to purchase: ";
        cin >> med;
        cout << "Enter quantity: ";
        cin >> qty;

        // Search for medicine in list
        for (auto m : items){
            if (m->getName() == med){
                // Check if enough stock is available
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

// ---------------- Main Function ----------------
int main(){
    Pharmacy ph; // Pharmacy object
    int choice;

    do{
        cout << "\n===== Pharmacy Management System =====" << endl;
        cout << "1. Add Medicine" << endl;
        cout << "2. Show All Medicines" << endl;
        cout << "3. Purchase Medicine" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1){
            // Add a new medicine
            int type, qty;
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

            // Create medicine object dynamically based on type
            if (type == 1){
                ph.addMedicine(new Antibiotic(name, qty, price));
            }
            else{
                ph.addMedicine(new Painkiller(name, qty, price));
            }
        }

        else if (choice == 2){
            // Show all medicines
            ph.showAll();
        }

        else if (choice == 3){
            // Purchase a medicine
            ph.purchaseMedicine();
        }

    } while (choice != 4); // Continue until user chooses to exit

    cout << "Thank You!" << endl;
    return 0;
}
