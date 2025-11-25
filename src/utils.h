/**
 * @file Utils.h
 * @brief Utility functions for the loan calculator
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @brief Displays welcome message
 */
void displayWelcomeMessage();

/**
 * @brief Displays usage instructions
 */
void displayUsageInstructions();

/**
 * @brief Gets validated numeric input from user
 * @param prompt Message to display to user
 * @return User's input as long double
 */
long double getValidatedInput(const std::string& prompt);

/**
 * @brief Clears input buffer
 */
void clearInputBuffer();

#endif // UTILS_H
