// contestant id: #000000

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <functional>

using namespace std;

class Runner {
    public:
        // constructor for the Runner class to set up the values
        Runner(string name, int age, int bib, double registrationFee) {
            this->name = name;
            this->age = age;
            this->bib = bib;
            this->registrationFee = registrationFee;
        }

        // getters for the private values
        string getName () { return name; }
        int getAge() { return age; }
        int getBib() { return bib; }
        double getRegistrationFee() { return registrationFee; }

        // get the vale
        string getCategory() {
            if (age >= 51) {
                return "Senior";
            } else if (age >= 35) {
                return "Adult";
            } else {
                return "Young Adult";
            }
        }
    private:
        // private variables so getters needed
        string name;
        int age;
        int bib;
        double registrationFee;
};

int main() {
    // vector with the runners input by the user
    vector<Runner> runners;

    string shouldContinue = "Y";
    do {
        // get the name of the runner
        string name;
        while (true) {
            std::cout << "Name of the runner: ";

            if (std::getline(std::cin >> std::ws, name) && !name.empty()) {
                break;
            }

            cout << "The name of the runner cannot be nothing!\n";
        }

        // get the age of the runner
        int age;
        while (true) {
            cout << "Age of the runner: ";

            if (cin >> age && age >= 18 && age <= 99) {
                break;
            }

            cout << "Error: Invalid Age. Must be a number between 18-99.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // get the bib number of the runner
        int bib;
        while (true) {
            cout << "Enter the bib number of the runner: ";

            if (cin >> bib && bib >= 1000 && bib <= 9999) {
                break;
            }

            cout << "Error: Bib must be 4 digits.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // get the registration fee for the runner
        double registrationFee;
        while (true) {
            cout << "Enter the registration fee for the runner: ";

            if (cin >> registrationFee && registrationFee >= 0) {
                break;
            }

            cout << "The registration fee for the runner must be positive\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // make a new runner and put it to the back of the runners vector
        runners.emplace_back(name, age, bib, registrationFee);

        // ask if the user wants to add another user and only go forward once a valid input is sent
        while (true) {
            cout << "Would you like to add another runner? (Y/N)";

            if (std::getline(std::cin >> std::ws, shouldContinue) && (shouldContinue == "Y" || shouldContinue == "y" || shouldContinue == "n" || shouldContinue == "N")) {
                break;
            }

            cout << "You need to enter a valid input (Y/N)!\n"; 
        }
        cout << "\n";
    } while (shouldContinue == "Y" || shouldContinue == "y");

    // file
    ofstream outFile("marathon_list.txt");

    double totalFees = 0;
    double totalAge = 0;

    if (outFile.is_open()) {
        for (Runner runner : runners) {
            // add values to total
            totalFees += runner.getRegistrationFee();
            totalAge += (double) runner.getAge();

            // output runner stats to file
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "%d | %s | %d | %s | %.2f\n", runner.getBib(), runner.getName().c_str(), runner.getAge(), runner.getCategory().c_str(), runner.getRegistrationFee());
            outFile << buffer;
        }

        // output the stats for all the runners to the file
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "\nTotal Fees Collected: %.2f\nAverage Age of all runners: %.2f", totalFees, totalAge / runners.size());
        outFile << buffer;

        // close the file for writing
        outFile.close();
    } else {
        // file did not open
        cerr << "Error: Coult not open the file." << std::endl;
    }

    // job done: exit program
    return 0;
}