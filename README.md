
A C++ program that calculates monthly EMI payments for loans.

---

 Quick Start

 1. Compile the Program

bash
g++ -std=c++11 -o calc.exe src/main.cpp src/Loan.cpp


2. Run the Program

bash
./calc.exe


3. Enter Your Loan Details


Load loan details from config.txt? (y/n): n

Enter the loan amount: $100000
Enter the interest rate (%): 12
Enter the number of years: 10


 4. View Results


========================================
         LOAN SUMMARY                   
========================================
Loan Amount:        $100000.00
Interest Rate:      12.00%
Loan Tenure:        10.00 years
----------------------------------------
Monthly Payment:    $1833.33
Total Amount:       $220000.00
Total Interest:     $120000.00
========================================


---

 Using Configuration File (Optional)

 1. Edit config.txt

txt
loan_amount 100000
interest_rate 12
number_of_years 10


 2. Run and Choose 'y'

bash
./calc.exe
Load loan details from config.txt? (y/n): y


---

 Running Tests

bash
 Compile tests
g++ -std=c++11 -o test_runner.exe test/test_emi_simple.cpp src/Loan.cpp

 Run tests
./test_runner.exe


---

 Requirements

- C++ compiler with C++11 support (g++, MinGW, etc.)


Authors: 

MASHAAL KHAN   24p-3112
ABDUL MUIZ     24p-3090

g++ -std=c++11 LoanCalculator.cpp -o calc

./calc -cp -a 100000 -i 12 -n 360