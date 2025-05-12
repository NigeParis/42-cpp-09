/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:54:19 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/12 21:17:39 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(void) :vector_(0), deque_(0) {std::cout << "Default constructor" << std::endl;};
PmergeMe::~PmergeMe(void) {std::cout << "Default destructor" << std::endl;};

template <typename T>
void PmergeMe::swapPairs(T &a, T &b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
};

template <typename T>
void PmergeMe::sortPair(T &a, T &b) {

    if (a < b)
        swapPairs(a,b);
};



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


void PmergeMe::makePairs(void) {

    unsigned int size = this->vector_.size();
    unsigned int y = 0;
    this->leftover_ = '\0';
    this->leftOverFlag_ = false;
    
    if (size %2 != 0) {
        this->leftover_ = this->vector_[size - 1];
        leftOverFlag_ = true;
    }
    for (unsigned int i = 0; i < size; i++) {

        if (i == size - 1 && this->leftOverFlag_ ) {
            break ;
        }
        this->vpair_.push_back(std::make_pair(this->vector_[y], this->vector_[y + 1]));
        y += 2;
    }    
    sortPair(vpair_[0], vpair_[1]);
        

    std::cout << "pair->first: " << vpair_[0].first << " pair->second: " << vpair_[0].second << std::endl;    
    std::cout << "pair->first: "  << vpair_[1].first << " pair->second: " << vpair_[1].second << std::endl;    
    std::cout << "leftOverFlag_: " << leftOverFlag_ << " leftOver_: " << leftover_ << " SIZE: " << size << std::endl;
    std::cout << "Pair size: " << vpair_.size() / 2 << std::endl;
};


