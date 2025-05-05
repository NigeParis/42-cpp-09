/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:13:15 by nige42            #+#    #+#             */
/*   Updated: 2025/05/05 08:42:10 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>
#include <iostream>
#include <exception>
#include <stack>
#include <string>



class RPN {

    public:

        RPN(void);
        RPN(std::string &inputStr);
        ~RPN(void);
        void setInput(const char *input);



    private:
    
        std::stack<std::string> input;
};


