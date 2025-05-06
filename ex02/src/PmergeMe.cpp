/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:54:19 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/06 13:26:33 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(void) :vector_(0), deque_(0) {std::cout << "Default constructor" << std::endl;};
PmergeMe::~PmergeMe(void) {std::cout << "Default destructor" << std::endl;};
static unsigned int stringToUnsignedInt(const std::string &strNumber) {
    const unsigned int uIntMax = std::numeric_limits<unsigned int>::max();
    std::istringstream streamString(strNumber);
    size_t number = 0;
    streamString >> number;
    if (number > uIntMax)
        throw std::runtime_error("Error: input unsigned int too big");
    return ((unsigned int)number);
}
void PmergeMe::setValues(std::string &inputStr) {

    std::istringstream inStringStream(inputStr);
    std::string strNumber;
    unsigned int number = 0;

    while (inStringStream >> strNumber) {
        number = stringToUnsignedInt(strNumber);
        this->vector_.push_back(number);
        this->deque_.push_back(number);
    }
};
void PmergeMe::getValues(void) {

    unsigned int vSize = this->vector_.size();
    unsigned int dSize = this->deque_.size();
    
    std::cout << "Before: ";
    for (size_t i = 0; i < vSize; ++i) {
        if (i == 0) 
            std::cout << this->vector_[i];        
        else
            std::cout << " " << this->vector_[i];        
    }
    std::cout << " <std::vector>" << std::endl;

    std::cout << "Before: ";
    for (size_t i = 0; i < dSize; ++i) {
        if (i == 0) 
            std::cout << this->deque_[i];        
        else
            std::cout << " " << this->deque_[i];        
    }
    std::cout << " <std::deque>" << std::endl;
};





