/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:14:59 by nige42            #+#    #+#             */
/*   Updated: 2025/05/05 16:02:50 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

RPN::RPN(void) {};

RPN::~RPN(void) {};

RPN::RPN(std::string &inputStr) {
    std::cout << "named RPN constructor" << std::endl;
    for (std::string::iterator itc = inputStr.begin(); itc != inputStr.end(); ++itc ) {
        this->input_.push(*itc);
    }
    std::cout << inputStr << std::endl;
};

void removeExtraSpaces(std::string &inputStr) {
    std::string result;
    bool lastWasSpace = false;
    for (size_t i = 0; i < inputStr.size(); ++i) {
        if (inputStr[i] == ' ') {
            if (!lastWasSpace) {
                result += inputStr[i];
            }
            lastWasSpace = true;
        } else {
            result += inputStr[i];
            lastWasSpace = false;
        }
    }
    inputStr = result;
}

bool isValidExpression(const std::string &inputStr) {
    std::istringstream inStringStream(inputStr);
    std::stack<int> counter;
    std::string extractedStr;
    
    //  you can use also while (inStringStream >> extractedStr) {
        while (std::getline(inStringStream, extractedStr, ' ')) {
        if (extractedStr == "+" || extractedStr == "-" || extractedStr == "*" || extractedStr == "/") {
            if (counter.size() < 2) return false;
            counter.pop();
        } else {
            counter.push(1);
        }
    }
    
    if (counter.size() == 1)
        return true;
    return false;
}




bool checkInputStr(std::string &inputStr) {
    
    for (size_t i = inputStr.size(); i > 0; i--) {
        if (i%2 != 0 && inputStr[i] != '\0') {
            if (inputStr[i] != ' ') {
                return (true);
            }
        } else {
            if (inputStr[i] == '+' || inputStr[i] == '-'
                || inputStr[i] == '*'|| inputStr[i] == '/' 
                || inputStr[i] == ' ')
                continue;
            if (isdigit(inputStr[i]))
                continue;
            else {
                if (i != inputStr.size())
                    return true;
            }
        }
    }
    return (false);
};





void RPN::setInput(std::string &inputStr) {
    
    std::cout << "setInput() called" << std::endl;
    if (inputStr.empty()) {
        throw std::runtime_error("Error: Input empty");
    }
    
    removeExtraSpaces(inputStr);

    if(checkInputStr(inputStr))
        throw std::runtime_error("Error: Input format");
    
    if (!isValidExpression(inputStr))
        throw std::runtime_error("Error: invalid expression"); 

    for (std::string::iterator itc = inputStr.begin(); itc != inputStr.end(); ++itc ) {
        this->input_.push(*itc);
    }
    std::cout << "input_: " << "'" << inputStr << "'" << std::endl;
};


double RPN::safeMultiply(double nbr1, double nbr2) {

    const double LL_MIN = -std::numeric_limits<double>::max();
    const double LL_MAX = std::numeric_limits<double>::max();

    if ((nbr1 > 0 && nbr2 > 0 && nbr1 > LL_MAX / nbr2) ||  // Positive overflow
    (nbr1 < 0 && nbr2 < 0 && nbr1 < LL_MAX / nbr2) ||  // Negative overflow
    (nbr1 > 0 && nbr2 < 0 && nbr2 < LL_MIN / nbr1) ||  // Mixed underflow
    (nbr1 < 0 && nbr2 > 0 && nbr1 < LL_MIN / nbr2)) {  // Mixed underflow
        throw std::runtime_error("Error: Multiplication exceeds double limits!");
    }
    return (nbr1 * nbr2);
}

double RPN::safeAdd(double nbr1, double nbr2) {

    const double LL_MIN = -std::numeric_limits<double>::max();
    const double LL_MAX = std::numeric_limits<double>::max();

    if ((nbr1 > 0 && nbr2 > LL_MAX - nbr1) ||  // Positive overflow
    (nbr1 < 0 && nbr2 < LL_MIN - nbr1)) {  // Negative overflow
        throw std::runtime_error("Error: Addition exceeds double limits!");
    }
    return (nbr1 + nbr2);
}

double RPN::safeSubtract(double nbr1, double nbr2) {

    const double LL_MIN = -std::numeric_limits<double>::max();
    const double LL_MAX = std::numeric_limits<double>::max();

    if ((nbr1 > 0 && nbr2 < LL_MIN + nbr1) ||  // Positive overflow
        (nbr1 < 0 && nbr2 > LL_MAX + nbr1)) {  // Negative overflow
        throw std::runtime_error("Error: Subtraction exceeds double limits!");
    }
    return (nbr1 - nbr2);
}

double RPN::safeDivide(double nbr1, double nbr2) {

    if (nbr2 == 0) {
        throw std::runtime_error("Error: Division by zero!");
    }
    return (nbr1 / nbr2);
}




void RPN::setResult(std::string &inputStr) {
    
    std::stack<double> numberStack;
    double nbr1 = 0;
    double  nbr2 = 0;
    double result = 0;
    

    for (std::string::iterator it = inputStr.begin(); it != inputStr.end(); ++it ) {

        if (isdigit(*it)) {
            numberStack.push(*it -'0');            
        }
        else if (*it == '+' || *it == '-' || *it == '*' || *it == '/') {

            if (numberStack.size() < 2) {
                throw std::runtime_error("Error: invalid too few values for operand");
            }
        
            nbr2 = numberStack.top();
            numberStack.pop();
            nbr1 = numberStack.top();
            numberStack.pop();
            
            if (*it == '+')
                result = safeAdd(nbr1, nbr2);
            else if (*it == '-')
                result = safeSubtract(nbr1, nbr2);
            else if (*it == '*') 
                result = safeMultiply(nbr1, nbr2);
            else if (*it == '/')
                result = safeDivide(nbr1, nbr2);
            
            numberStack.push(result);
            
        }        
    }
    if (std::floor(result) == result) {
        std::cout << std::fixed << std::setprecision(0) << result << std::endl;; // No decimals if it's an integer
    } else {
        std::cout << std::fixed << std::setprecision(PRECISION) << result << std::endl;; // Show 4 decimals if it's not an integer
    }

}
