/**
 * @file Loan.cpp
 * @brief Implementation of Loan class methods
 */

#include "Loan.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

/**
 * @brief Parameterized constructor
 */
Loan::Loan(long double amount, long double rate, long double years)
    : loanAmount(amount), interestRate(rate), numberOfYears(years) {
    if (!validateInputs()) {
        throw invalid_argument("Invalid loan parameters provided");
    }
}

/**
 * @brief Default constructor
 */
Loan::Loan() : loanAmount(0), interestRate(0), numberOfYears(0) {
}

/**
 * @brief Validates input parameters
 */
bool Loan::validateInputs() const {
    if (loanAmount <= 0) {
        cerr << "Error: Loan amount must be positive!" << endl;
        return false;
    }
    if (interestRate < 0 || interestRate > 100) {
        cerr << "Error: Interest rate must be between 0 and 100!" << endl;
        return false;
    }
    if (numberOfYears <= 0) {
        cerr << "Error: Number of years must be positive!" << endl;
        return false;
    }
    if (numberOfYears > 100) {
        cerr << "Warning: Very long tenure (>100 years) detected!" << endl;
    }
    return true;
}

/**
 * @brief Calculates monthly EMI payment
 */
long double Loan::calculateMonthlyPayment() const {
    if (!validateInputs()) {
        return 0.0;
    }

    long double totalAmount = calculateTotalAmount();
    long double totalMonths = numberOfYears * 12.0;

    // Check for potential overflow
    if (totalMonths > 100000) {
        cerr << "Warning: Very large number of months!" << endl;
    }

    return totalAmount / totalMonths;
}

/**
 * @brief Calculates total amount payable
 */
long double Loan::calculateTotalAmount() const {
    if (!validateInputs()) {
        return 0.0;
    }

    // Formula: Total = Principal × Years + Principal × Years × (Rate/100)
    // This is simplified interest calculation, not compound
    long double principal = numberOfYears * loanAmount;
    long double interest = numberOfYears * loanAmount * (interestRate / 100.0);

    return principal + interest;
}

/**
 * @brief Calculates total interest
 */
long double Loan::calculateTotalInterest() const {
    if (!validateInputs()) {
        return 0.0;
    }

    long double totalPrincipal = numberOfYears * loanAmount;
    return calculateTotalAmount() - totalPrincipal;
}

/**
 * @brief Displays complete loan summary
 */
void Loan::displayLoanSummary() const {
    if (!validateInputs()) {
        cout << "Cannot display summary - invalid inputs!" << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "         LOAN SUMMARY                   " << endl;
    cout << "========================================" << endl;
    cout << fixed << setprecision(2);
    cout << "Loan Amount:        $" << loanAmount << endl;
    cout << "Interest Rate:      " << interestRate << "%" << endl;
    cout << "Loan Tenure:        " << numberOfYears << " years" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Monthly Payment:    $" << calculateMonthlyPayment() << endl;
    cout << "Total Amount:       $" << calculateTotalAmount() << endl;
    cout << "Total Interest:     $" << calculateTotalInterest() << endl;
    cout << "========================================\n" << endl;
}

/**
 * @brief Loads configuration from file
 */
bool Loan::loadFromConfig(const string& filename) {
    ifstream configFile(filename);

    if (!configFile.is_open()) {
        cerr << "Error: Could not open config file: " << filename << endl;
        return false;
    }

    string key;
    long double value;

    while (configFile >> key >> value) {
        if (key == "loan_amount") {
            loanAmount = value;
        } else if (key == "interest_rate") {
            interestRate = value;
        } else if (key == "number_of_years") {
            numberOfYears = value;
        }
    }

    configFile.close();

    if (!validateInputs()) {
        return false;
    }

    cout << "Configuration loaded successfully from " << filename << endl;
    return true;
}

/**
 * @brief Setter for loan amount with validation
 */
void Loan::setLoanAmount(long double amount) {
    if (amount <= 0) {
        throw invalid_argument("Loan amount must be positive");
    }
    loanAmount = amount;
}

/**
 * @brief Setter for interest rate with validation
 */
void Loan::setInterestRate(long double rate) {
    if (rate < 0 || rate > 100) {
        throw invalid_argument("Interest rate must be between 0 and 100");
    }
    interestRate = rate;
}

/**
 * @brief Setter for number of years with validation
 */
void Loan::setNumberOfYears(long double years) {
    if (years <= 0) {
        throw invalid_argument("Number of years must be positive");
    }
    numberOfYears = years;
}
