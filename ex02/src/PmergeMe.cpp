/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:54:19 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/12 23:00:30 by nige42           ###   ########.fr       */
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
    size_t sizev = vpair_.size();

    for (size_t i = 0; i < sizev / 2; ++i)
        sortPair(vpair_[i].first, vpair_[i].second);



        
        sortPair(vpair_[0], vpair_[1]);
        

  
   displayContainerPairs(vpair_);
   displayContainer(deque_);
};


template <typename T>
void PmergeMe::displayContainer(T &container) {
    size_t size = container.size();

    for (size_t i = 0; i < size; ++i)
        std::cout << container[i] << ", ";    
    std::cout << std::endl;        
    std::cout << "Size: " << size << std::endl;
}

template <typename T>
void PmergeMe::displayContainerPairs(T &container) {
    size_t size = container.size() / 2;
    
    for (size_t i = 0; i < size; ++i)
        std::cout << "(" << container[i].first << ", " << container[i].second << ") ";    
    std::cout << std::endl;        
    std::cout << "Size: " << size << std::endl;
}
