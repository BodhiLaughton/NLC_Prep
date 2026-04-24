// Contestant ID: #000000

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <functional>

using namespace std;

// item class
class Item {
    private:
        // private values that cannot be accessed from outside the class without getters
        int itemID;
        string itemName;
        double price;
        int quantity;
    public:
        // public constructor
        Item(int itemID, string itemName, double price, int quantity) {
            this->itemID = itemID;
            this->itemName = itemName;
            this->price = price;
            this->quantity = quantity;
        }

        // getters
        int getItemID() { return itemID; }
        string getItemName() { return itemName; }
        double getPrice() { return price; }
        int getQuantity() { return quantity; }

        // returns calculated value
        double getTotalValue() {
            return price * quantity;
        }
};

int main() {
    // vector of items
    vector<Item> items;

    string shouldContinue;    
    do {
        // get itemID
        int itemID;
        while (true) {
            cout << "ItemID: ";

            if (cin >> itemID && itemID >= 10000 && itemID <= 99999) {
                break;
            }

            cout << "Error: Item ID must be 5 digits.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // get itemName
        string itemName;
        while(true) {
            cout << "ItemName: ";

            if (getline(cin >> ws, itemName) && !itemName.empty()) {
                break;
            }

            cout << "Error: Name cannot be blank.\n";
        }

        // get price
        double price;
        while (true) {
            cout << "Price: ";

            if (cin >> price && price >= 0.0) {
                break;
            }

            cout << "Error: Price must be greater than 0.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // get quantity
        int quantity;
        while (true) {
            cout << "Quantity: ";

            if (cin >> quantity && quantity >= 0) {
                break;
            }

            cout << "Error: Quantity cannot be negative.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // make item and put it in the vector for later
        items.emplace_back(itemID, itemName, price, quantity);

        // ask user if they want to keep adding more items
        while(true) {
            cout << "Would you like to add another item? (Y/N): ";

            if (getline(cin >> ws, shouldContinue) && (shouldContinue == "Y" || shouldContinue == "y" || shouldContinue == "n" || shouldContinue == "N")) {
                break;
            }

            cout << "Error: Must enter (Y/N).\n";
        }
        cout << "\n";
    } while (shouldContinue == "Y" || shouldContinue == "y");

    // ask for id to find
    int itemIDToFind;
    while (true) {
        cout << "Enter an ItemID to find: ";

        if (cin >> itemIDToFind && itemIDToFind >= 0) {
            break;
        }

        cout << "Error: ItemID cannot be negative.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // try to find item
    bool foundItem = false;
    for (Item& item : items) {
        if (item.getItemID() == itemIDToFind) {
            foundItem = true;
            // item found!
            cout << "Item Found: " << item.getItemName() << " - " << item.getQuantity() << " in stock at $" << item.getPrice() << "\n";
        }
    }
    if (!foundItem) {
        // item not found :(
        cout << "Notice: Item ID not found in current inventory.\n";
    }

    // sort items with selection sort (note: slow time complexity but fine because low amount of items)
    for (int i = 0; i < items.size(); i++) {
        int maxIndex = i;
        for (int j = items.size() - 1; j > i; j--) {
            if (items[j].getTotalValue() > items[maxIndex].getTotalValue()) {
                maxIndex = j;
            }
        }

        Item temp = items[i];
        items[i] = items[maxIndex];
        items[maxIndex] = temp;
    }

    // file
    ofstream outFile("inventory_report.txt");

    if (outFile.is_open()) {
        outFile << "ID    | Name                 | Qty | Price  | Total Value\n---------------------------------------------------------\n";
        
        double totalValue = 0.0;
        for (Item& item : items) {
            totalValue += item.getTotalValue();

            // output stats for each item
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "%d | %-21s| %-4d| $%-6.2f| $%.2f\n", item.getItemID(), item.getItemName().c_str(), item.getQuantity(), item.getPrice(), item.getTotalValue());
            outFile << buffer;
        }

        // output total store inventory value
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "\nTotal Store Inventory Value: $%.2f", totalValue);
        outFile << buffer;

        // close file
        outFile.close();
    }
    
    // job done: exit program
    return 0;
}