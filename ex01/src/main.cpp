/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:12:53 by nige42            #+#    #+#             */
/*   Updated: 2025/05/05 08:28:15 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    RPN input;
    std::string inputStr = "";
    
    if (argc < 2) {
        std::cout << "Error: ./RPN [ARG]" << std::endl;
        return -1;
    }
    try {
        for (int i = 1; i < argc; i++) {
            inputStr.append(argv[i]);
            if (i < argc - 1)
                inputStr.append(" ");
        }
        
        input.setInput(inputStr.c_str());
    }
    catch(std::exception &e) {

        std::cout << e.what() << std::endl;
        
    }
    
   
   
    std::cout << argc << " input " << inputStr << std::endl;
    
   
   


   

    return 0;

}