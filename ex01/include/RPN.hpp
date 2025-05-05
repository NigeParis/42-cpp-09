/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:13:15 by nige42            #+#    #+#             */
/*   Updated: 2025/05/05 16:03:14 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>
#include <iostream>
#include <exception>
#include <stack>
#include <string>
#include <limits>
#include <iomanip> // Required for std::fixed & std::setprecision
#include <cmath> // Needed for std::floor

#define PRECISION 3

class RPN {

    public:

        RPN(void);
        RPN(std::string &inputStr);
        ~RPN(void);
        void setInput(std::string &inputStr);
        void setResult(std::string &inputStr);



    private:
    
        std::stack<char> input_;

        double safeMultiply(double nbr1, double nbr2); 
        double safeAdd(double nbr1, double nbr2); 
        double safeSubtract(double nbr1, double nbr2); 
        double safeDivide(double nbr1, double nbr2); 
};


