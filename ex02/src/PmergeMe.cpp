/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:54:19 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/14 17:16:23 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(void) :vector_(), main_(), pend_(), deque_(), vpair_() {std::cout << "Default constructor" << std::endl;};
PmergeMe::~PmergeMe(void) {std::cout << "Default destructor" << std::endl;};

template <typename T>
void PmergeMe::sortPair(T &a, T &b) {

    if (a < b)
         std::swap(a, b);
};

template <typename T>
void PmergeMe::sort(T &a, T &b) {

    if (a < b)
        std::swap(a, b);
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
        if (number == 0)
            throw std::runtime_error("Error: Not positive integer");
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
    this->leftover_ = 0;
    this->leftOverFlag_ = false;
    
    if (size %2 != 0) {
        if (!vector_.empty()) {
            this->leftover_ = this->vector_[size - 1];
            this->vector_.pop_back();
            leftOverFlag_ = true;
        }
    }
    size = this->vector_.size();
    for (std::vector<unsigned long>::iterator it = vector_.begin(); it != vector_.end(); it++) {
        vpair_.push_back(std::make_pair(*it, *(++it)));
    }    
    size_t vSize = vpair_.size();
    for (size_t i = 0; i < vSize; i++)
    sortPair(vpair_[i].first, vpair_[i].second);
};
    
    
    
    
void PmergeMe::makeMain(void) {
       
    size_t vSize = vpair_.size();
     
    for (unsigned int i = 0; i < vSize; ++i) {
        for (unsigned int y = 0; y < vSize; ++y) {
            sortPair(vpair_[i], vpair_[y]);
        }
    }    
    for (size_t i = 0; i < vSize; ++i) {     
        main_.push_back(vpair_[i].first);
    }
    main_.insert(main_.begin(), vpair_[0].second);    
    displayContainer(main_);       
    displayContainerPairs(vpair_);
};


void PmergeMe::makePend(void) {

    size_t vSize = vpair_.size();
    for (size_t i = 1; i < vSize; i++) {     
        pend_.push_back(vpair_[i].second);
    }

    displayContainer(pend_);       
};



template <typename T>
void PmergeMe::displayContainer(T &container) {\
            
    std::cout << "Container:  ";
    for (typename T::iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << ", ";
    }            
    std::cout << std::endl;        
}




template <typename T>
void PmergeMe::displayContainerPairs(T &container) {
    for (typename T::iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
    }
    std::cout << std::endl;
}
