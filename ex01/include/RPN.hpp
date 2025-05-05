/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:13:15 by nige42            #+#    #+#             */
/*   Updated: 2025/05/05 17:20:15 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>      // Required for std::istringstream
#include <iostream>     // Required for std::cout
#include <exception>    // Required for try and catch
#include <stack>        // Required for std::stack - container
#include <string>       // Required for std::string
#include <limits>       // Required for std::numeric_limits
#include <iomanip>      // Required for std::fixed & std::setprecision
#include <cmath>        // Needed for std::floor

#define PRECISION 3     // Used for number of decimals displayed in the result
 
class RPN {

    public:
        RPN(void);
        RPN(std::string &inputStr);
        ~RPN(void);
        void setInput(std::string &inputStr);
        void getResult(std::string &inputStr);
    private:
        std::stack<char> input_;
        RPN(RPN &copy);
        RPN &operator=(RPN &copy);
        double safeMultiply(double nbr1, double nbr2); 
        double safeAdd(double nbr1, double nbr2); 
        double safeSubtract(double nbr1, double nbr2); 
        double safeDivide(double nbr1, double nbr2); 
};
