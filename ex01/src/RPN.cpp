/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:14:59 by nige42            #+#    #+#             */
/*   Updated: 2025/05/05 08:56:43 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

RPN::RPN(void) {};

RPN::~RPN(void) {};

RPN::RPN(std::string &inputStr) {
    std::cout << "named RPN constructor" << std::endl;
    this->input.push(inputStr);
    std::cout << inputStr << std::endl;
};

void removeExtraSpaces(std::string &inputStr) {
    std::string result;
    bool lastWasSpace = false;
    // std::cout << "str '" << inputStr << "'" << std::endl;
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
    
    removeExtraSpaces(inputStr);
    for (size_t i = inputStr.size(); i > 0; i--) {
        if (i%2 != 0 && inputStr[i] != '\0') {
            if (inputStr[i] != ' ')
                return (true);
        } else {
            if (inputStr[i] == '+' || inputStr[i] == '-'|| inputStr[i] == '*'|| inputStr[i] == '/' || inputStr[i] == ' ')
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





void RPN::setInput(const char *input) {


    std::string inputStr = input;
    
    std::cout << "setInput() called" << std::endl;
    if (inputStr.empty()) {
        throw std::runtime_error("Error: Input empty");
    }

    if(checkInputStr(inputStr))
        throw std::runtime_error("Error: Input format");
    
    if (!isValidExpression(inputStr))
        throw std::runtime_error("Error: invalid expression");


    
    this->input.push(inputStr);
    std::cout << inputStr << std::endl;
    
};


