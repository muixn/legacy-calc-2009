/**
 * @file test_emi_gtest.cpp
 * @brief Full GoogleTest unit tests for Loan Calculator
 * @author Your Name
 * @date 2025
 */

#include <gtest/gtest.h>
#include "../src/Loan.h"
#include <stdexcept>

/**
 * @brief Test fixture for Loan class tests
 */
class LoanTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code runs before each test
    }

    void TearDown() override {
        // Cleanup code runs after each test
    }
};

/**
 * @brief Test normal EMI calculation with valid inputs
 */
TEST_F(LoanTest, NormalEMICalculation) {
    Loan loan(100000, 12, 10);

    long double monthly = loan.calculateMonthlyPayment();
    long double total = loan.calculateTotalAmount();
    long double interest = loan.calculateTotalInterest();

    EXPECT_GT(monthly, 0);
    EXPECT_GT(total, 0);
    EXPECT_GT(interest, 0);
    EXPECT_GT(total, loan.getLoanAmount());

    long double calculatedTotal = monthly * (loan.getNumberOfYears() * 12);
    EXPECT_NEAR(calculatedTotal, total, 0.01);
}

/**
 * @brief Test that negative loan amount throws exception
 */
TEST_F(LoanTest, InvalidNegativeLoanAmount) {
    EXPECT_THROW({
        Loan loan(-10000, 12, 10);
    }, std::invalid_argument);
}

/**
 * @brief Test that zero loan amount throws exception
 */
TEST_F(LoanTest, InvalidZeroLoanAmount) {
    EXPECT_THROW({
        Loan loan(0, 12, 10);
    }, std::invalid_argument);
}

/**
 * @brief Test that invalid interest rate throws exception
 */
TEST_F(LoanTest, InvalidInterestRate) {
    EXPECT_THROW({
        Loan loan(100000, -5, 10);
    }, std::invalid_argument);

    EXPECT_THROW({
        Loan loan(100000, 150, 10);
    }, std::invalid_argument);
}

/**
 * @brief Test that invalid tenure throws exception
 */
TEST_F(LoanTest, InvalidTenure) {
    EXPECT_THROW({
        Loan loan(100000, 12, -5);
    }, std::invalid_argument);

    EXPECT_THROW({
        Loan loan(100000, 12, 0);
    }, std::invalid_argument);
}

/**
 * @brief Test large tenure calculations without overflow
 */
TEST_F(LoanTest, LargeTenureNoOverflow) {
    EXPECT_NO_THROW({
        Loan loan(1000000, 8, 50);
        long double emi = loan.calculateMonthlyPayment();
        EXPECT_GT(emi, 0);
        EXPECT_LT(emi, loan.getLoanAmount());
    });
}

/**
 * @brief Test very large loan amount
 */
TEST_F(LoanTest, VeryLargeLoanAmount) {
    EXPECT_NO_THROW({
        Loan loan(10000000, 10, 20);
        long double total = loan.calculateTotalAmount();
        EXPECT_GT(total, 0);
    });
}

/**
 * @brief Test edge case: zero interest rate
 */
TEST_F(LoanTest, ZeroInterestRate) {
    Loan loan(100000, 0, 10);
    long double interest = loan.calculateTotalInterest();
    EXPECT_DOUBLE_EQ(interest, 0.0);
}

/**
 * @brief Test edge case: one year tenure
 */
TEST_F(LoanTest, OneYearTenure) {
    Loan loan(12000, 10, 1);

    long double monthly = loan.calculateMonthlyPayment();
    long double total = loan.calculateTotalAmount();

    EXPECT_GT(monthly, 0);
    EXPECT_GT(total, 12000);
    EXPECT_NEAR(monthly * 12, total, 0.01);
}

/**
 * @brief Test getters and setters
 */
TEST_F(LoanTest, GettersAndSetters) {
    Loan loan(100000, 12, 10);

    EXPECT_DOUBLE_EQ(loan.getLoanAmount(), 100000);
    EXPECT_DOUBLE_EQ(loan.getInterestRate(), 12);
    EXPECT_DOUBLE_EQ(loan.getNumberOfYears(), 10);

    EXPECT_NO_THROW({
        loan.setLoanAmount(200000);
        loan.setInterestRate(15);
        loan.setNumberOfYears(20);
    });

    EXPECT_DOUBLE_EQ(loan.getLoanAmount(), 200000);
}

/**
 * @brief Test config file loading
 */
TEST_F(LoanTest, ConfigFileLoading) {
    Loan loan;
    bool loaded = loan.loadFromConfig("config.txt");

    if (loaded) {
        EXPECT_GT(loan.getLoanAmount(), 0);
        EXPECT_GE(loan.getInterestRate(), 0);
        EXPECT_GT(loan.getNumberOfYears(), 0);
    }
}

/**
 * @brief Main function for running all tests
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
