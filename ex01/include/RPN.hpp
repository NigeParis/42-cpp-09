/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:13:15 by nige42            #+#    #+#             */
/*   Updated: 2025/05/04 12:13:41 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <exception>
#include <stack>


class RPN {

    public:

        RPN(void);
        RPN(std::string &inputStr);
        ~RPN(void);
        void setInput(std::string &input);



    private:
    
        std::stack<std::string> input;
};


