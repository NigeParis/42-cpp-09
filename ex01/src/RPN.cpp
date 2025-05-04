/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:14:59 by nige42            #+#    #+#             */
/*   Updated: 2025/05/04 23:23:01 by nige42           ###   ########.fr       */
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

bool isValidPrefix(const std::string &expr) {
    std::istringstream iss(expr);
    std::stack<int> s;
    std::string token;
    
    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (s.size() < 2) return false;
            s.pop();
        } else {
            s.push(1);
        }
    }
    
    return s.size() == 1;
}




bool checkInputStr(std::string &inputStr) {
    
    removeExtraSpaces(inputStr);
    for (size_t i = inputStr.size(); i > 0; i--) {
        if (i%2 != 0 && inputStr[i] != '\0') {
            //std::cout << "inputStr = '" << inputStr[i] << "'" << "i = " << i << std::endl;
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





void RPN::setInput(std::string &inputStr) {

    std::cout << "setInput() called" << std::endl;
    if (inputStr.empty()) {
        throw std::runtime_error("Error: Input empty");
    }

    if(checkInputStr(inputStr))
        throw std::runtime_error("Error: Input format");
    
    if (isValidPrefix(inputStr))
        std::cout << "Expression is valid.\n";
    else
        std::cout << "Expression is INVALID!\n";

    
    this->input.push(inputStr);
    std::cout << inputStr << std::endl;
    
};


