/**
 * @file Loan.h
 * @brief Header file for Loan class - handles loan calculations
 * @author Your Name
 * @date 2025
 */

#ifndef LOAN_H
#define LOAN_H

#include <string>

/**
 * @class Loan
 * @brief Represents a loan with principal, interest rate, and tenure
 *
 * This class provides methods to calculate EMI (Equated Monthly Installment),
 * total amount payable, and total interest for a given loan.
 */
class Loan {
private:
    long double loanAmount;      ///< Principal loan amount
    long double interestRate;    ///< Annual interest rate (in percentage)
    long double numberOfYears;   ///< Loan tenure in years

    /**
     * @brief Validates loan parameters
     * @return true if all parameters are valid, false otherwise
     */
    bool validateInputs() const;

public:
    /**
     * @brief Constructor with parameters
     * @param amount Principal loan amount
     * @param rate Annual interest rate (percentage)
     * @param years Loan tenure in years
     */
    Loan(long double amount, long double rate, long double years);

    /**
     * @brief Default constructor - loads values from config file
     */
    Loan();

    /**
     * @brief Calculates monthly payment (EMI)
     * @return Monthly EMI amount
     */
    long double calculateMonthlyPayment() const;

    /**
     * @brief Calculates total amount to be paid
     * @return Total amount including principal and interest
     */
    long double calculateTotalAmount() const;

    /**
     * @brief Calculates total interest
     * @return Total interest amount
     */
    long double calculateTotalInterest() const;

    /**
     * @brief Displays complete loan summary
     */
    void displayLoanSummary() const;

    /**
     * @brief Loads loan parameters from config file
     * @param filename Name of the configuration file
     * @return true if loaded successfully, false otherwise
     */
    bool loadFromConfig(const std::string& filename);

    // Getters
    long double getLoanAmount() const { return loanAmount; }
    long double getInterestRate() const { return interestRate; }
    long double getNumberOfYears() const { return numberOfYears; }

    // Setters
    void setLoanAmount(long double amount);
    void setInterestRate(long double rate);
    void setNumberOfYears(long double years);
};

#endif // LOAN_H
