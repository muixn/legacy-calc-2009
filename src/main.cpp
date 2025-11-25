/**
 * @file main.cpp
 * @brief Main entry point for the Loan Calculator application
 * @author Your Name
 * @date 2025
 */

#include <iostream>
#include <limits>
#include "Loan.h"

using namespace std;

/**
 * @brief Displays welcome message
 */
void displayWelcomeMessage() {
    cout << "\n========================================" << endl;
    cout << "    LOAN CALCULATOR - Version 2.0       " << endl;
    cout << "========================================\n" << endl;
}

/**
 * @brief Gets validated numeric input from user
 * @param prompt Message to display
 * @return Validated numeric input
 */
long double getValidatedInput(const string& prompt) {
    long double value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            if (value > 0) {
                return value;
            } else {
                cout << "Error: Please enter a positive number!" << endl;
            }
        } else {
            cout << "Error: Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

/**
 * @brief Main function - entry point of application
 */
int main() {
    try {
        displayWelcomeMessage();

        // Option to load from config file
        char useConfig;
        cout << "Load loan details from config.txt? (y/n): ";
        cin >> useConfig;
        cout << endl;

        Loan myLoan;

        if (useConfig == 'y' || useConfig == 'Y') {
            // Try to load from config file
            if (!myLoan.loadFromConfig("config.txt")) {
                cout << "Failed to load config. Please enter details manually.\n" << endl;

                long double amount = getValidatedInput("Enter the loan amount: $");
                long double rate = getValidatedInput("Enter the interest rate (%): ");
                long double years = getValidatedInput("Enter the number of years: ");

                myLoan = Loan(amount, rate, years);
            }
        } else {
            // Manual input
            long double amount = getValidatedInput("Enter the loan amount: $");
            long double rate = getValidatedInput("Enter the interest rate (%): ");
            long double years = getValidatedInput("Enter the number of years: ");

            myLoan = Loan(amount, rate, years);
        }

        // Display results
        myLoan.displayLoanSummary();

        // Ask if user wants to calculate another loan
        char again;
        cout << "Calculate another loan? (y/n): ";
        cin >> again;

        if (again == 'y' || again == 'Y') {
            // Recursive call or loop can be added here
            cout << "Restart the program to calculate another loan." << endl;
        }

        cout << "\nThank you for using Loan Calculator!" << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
