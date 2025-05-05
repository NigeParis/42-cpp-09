/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:12:53 by nige42            #+#    #+#             */
/*   Updated: 2025/05/05 15:31:21 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    RPN input;
    std::stringstream lineEpression;
    std::string inputStr = "";
    
    if (argc < 2) {
        std::cout << "Error: ./RPN [ARG]" << std::endl;
        return -1;
    }
    try {
        for (int i = 1; i < argc; i++) {
            lineEpression << argv[i];
            if (i < argc - 1)
                lineEpression << " ";
        }
        std::getline(lineEpression, inputStr);
        
        input.setInput(inputStr);

        input.setResult(inputStr);

        
    }
    catch(std::exception &e) {

        std::cout << e.what() << std::endl;
        
    }   
    return 0;

}