#include <iostream>
#include <string>
using namespace std;

class Task1 {
public:
    int noOfCows;
    const int noOfDays = 7;
    int* identityCode;
    double** amountOfMilkMorning;
    double** amountOfMilkEvening;
    string days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    Task1(int noOfCows) {
        
        this->noOfCows = noOfCows;
        this->identityCode = new int[noOfCows];
        this->amountOfMilkMorning = new double*[noOfDays];
        this->amountOfMilkEvening = new double*[noOfDays];

        for (int i = 0; i < noOfDays; ++i) {
            this->amountOfMilkMorning[i] = new double[noOfCows];
            this->amountOfMilkEvening[i] = new double[noOfCows];
        }
    }

    ~Task1() {
        delete[] identityCode;

        for (int i = 0; i < noOfDays; ++i) {
            delete[] amountOfMilkMorning[i];
            delete[] amountOfMilkEvening[i];
        }

        delete[] amountOfMilkMorning;
        delete[] amountOfMilkEvening;
    }

    void getIdentityCode() {
        for (int i = 0; i < noOfCows; i++) {
            do {
                cout << "Enter the 3-digit Identity Code of Cow " << i + 1 << " : ";
                cin >> identityCode[i];

                if (identityCode[i] < 100 || identityCode[i] > 999) {
                    cerr << "Error: Identity Code should be a 3-digit number." << endl;
                }
            } while (identityCode[i] < 100 || identityCode[i] > 999);
        }
    }

    void getDetails() {
        for (int i = 0; i < noOfDays; i++) {
            cout << "\nEnter the details for " << days[i] << endl;
            cout << "\nEnter result for Morning" << endl;
            for (int j = 0; j < noOfCows; j++) {
                int check;
                do{
                    check =0;
                    cout << "Enter the amount of milk from cow " << identityCode[j] << " in Morning (In Liter): ";
                    cin >> amountOfMilkMorning[i][j];
                    if (amountOfMilkMorning[i][j] < 0) {
                        cerr << "Error: Milk amount cannot be negative." << endl;
                        check = 1;
                    }
                }while(check == 1);
            }
            cout << "\nEnter result for Evening" << endl;
            for (int j = 0; j < noOfCows; j++) {
                int check;
                do{
                    check = 0;
                    cout << "Enter the amount of milk from cow " << identityCode[j] << " in Evening (In Liter): ";
                    cin >> amountOfMilkEvening[i][j];
                    if (amountOfMilkEvening[i][j] < 0) {
                        cerr << "Error: Milk amount cannot be negative." << endl;
                        check = 1;
                    }
                }while(check == 1);
            }
        }
    }
};

class Task2 : public Task1 {
public:
    double totalMilk;
    double totalMilkPerCow;

    Task2(int noOfCows) : Task1(noOfCows) {
        totalMilk = 0.0;
        totalMilkPerCow = 0.0;
    }

    void calculateMilkStatistics() {
        for (int i = 0; i < noOfDays; i++) {
            for (int j = 0; j < noOfCows; j++) {
                totalMilk += amountOfMilkEvening[i][j] + amountOfMilkMorning[i][j];
            }
        }
        totalMilkPerCow = totalMilk / (noOfCows * noOfDays);
        cout << "\n\nTotal weekly volume of milk for the herd: " << static_cast<int>(totalMilk + 0.5) << " liters." << endl;
        cout << "Average yield per cow in a week: " << static_cast<int>(totalMilkPerCow + 0.5) << " liters." << endl;
    }
};

class Task3 : public Task2 {
    double* weeklyYieldPerCow;
    int mostProductiveCow;
    double maxCowYield;

public:
    Task3(int noOfCows) : Task2(noOfCows) {
        weeklyYieldPerCow = new double[noOfCows];
        mostProductiveCow = -1;
        maxCowYield = 0.0;
    }
    
    ~Task3 (){
        delete[] weeklyYieldPerCow;
    }

    void findProductiveCow() {
        for (int i = 0; i < noOfCows; i++) {
            weeklyYieldPerCow[i] = 0.0;
        }

        for (int i = 0; i < noOfDays; i++) {
            for (int j = 0; j < noOfCows; j++) {
                weeklyYieldPerCow[j] += amountOfMilkEvening[i][j] + amountOfMilkMorning[i][j];
            }
        }
        for (int i = 0; i < noOfCows; i++) {
            if (weeklyYieldPerCow[i] > maxCowYield) {
                maxCowYield = weeklyYieldPerCow[i];
                mostProductiveCow = i;
            }
        }
        cout << "\nThe most productive cow is " << identityCode[mostProductiveCow] << " whose weekly yield is " << static_cast<int>(maxCowYield + 0.5) << " liters." << endl;
    }

    void findUnProductiveCow() {
        for (int j = 0; j < noOfCows; j++) {
            int lowYieldDays = 0;
            int unproductive = 0;

            for (int i = 0; i < noOfDays - 3; i++) {
                lowYieldDays = amountOfMilkEvening[i][j] + amountOfMilkMorning[i][j] + amountOfMilkMorning[i + 1][j] + amountOfMilkEvening[i + 1][j] + amountOfMilkMorning[i + 2][j] + amountOfMilkEvening[i + 2][j] + amountOfMilkMorning[i + 3][j] + amountOfMilkEvening[i + 3][j];

                if (lowYieldDays >= 12.0) {
                    unproductive = 1;
                    break;
                }
            }

            if (unproductive == 0) {
                cout << "The cow " << identityCode[j] << " produced less than 12 liters of milk for four or more consecutive days." << endl;
            } 
        }
    }
};

int main() {
    int numCows;

    do {
        cout << "Enter the number of cows: ";
        cin >> numCows;

        if (numCows <= 0) {
            cerr << "Error: Number of cows should be a positive integer." << endl;
        }
    } while (numCows <= 0);

    Task3 task(numCows);
    task.getIdentityCode();
    task.getDetails();
    task.calculateMilkStatistics();
    task.findProductiveCow();
    task.findUnProductiveCow();

    return 0;
}