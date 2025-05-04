/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:14:59 by nige42            #+#    #+#             */
/*   Updated: 2025/05/04 12:52:00 by nige42           ###   ########.fr       */
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


bool checkInputStr(std::string &inputStr) {
    
    if((!isdigit(inputStr[0])) || (!isdigit(inputStr[2])) || !isspace(inputStr[1])) {
        return (true);
    }
    
    
    return (false);
};





void RPN::setInput(std::string &inputStr) {

    std::cout << "setInput() called" << std::endl;
    if (inputStr.empty()) {
        throw std::runtime_error("Error: Input empty");
    }

    if(checkInputStr(inputStr))
        throw std::runtime_error("Error: Input format incorrect");
    


    
    this->input.push(inputStr);
    std::cout << inputStr << std::endl;
    
};


