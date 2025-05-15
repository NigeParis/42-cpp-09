/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:54:19 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/15 13:12:25 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(void) :vector_(), vMain_(), vPend_(), deque_(), dMain_(),
dPend_(), vpair_(), jacLadder_() {std::cout << "Default constructor" << std::endl;};
PmergeMe::~PmergeMe(void) {std::cout << "Default destructor" << std::endl;};

template <typename T>
void PmergeMe::sortPair(T &a, T &b) {

    if (a < b)
         std::swap(a, b);
};

unsigned int jacobsthal(unsigned int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}


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
    for (std::vector<unsigned int>::iterator it = vector_.begin(); it != vector_.end(); it++) {
        vpair_.push_back(std::make_pair(*it, *(++it)));
    }    
    size_t vSize = vpair_.size();
    for (size_t i = 0; i < vSize; i++)
    sortPair(vpair_[i].first, vpair_[i].second);
};
    
    
    
    
void PmergeMe::makeMain(void) {
       
    unsigned int vSize = vpair_.size();
    if (vSize == 0) {
        return ;        
    }
    for (unsigned int i = 0; i < vSize; ++i) {
        for (unsigned int y = 0; y < vSize; ++y) {
            sortPair(vpair_[i], vpair_[y]);
        }
    }    
    for (unsigned int i = 0; i < vSize; ++i) { 
        if (vpair_[i].first)     
            vMain_.push_back(vpair_[i].first);
    }
    if (vpair_[0].second) 
        vMain_.insert(vMain_.begin(), vpair_[0].second);    
    //displayContainer(vMain_);       
    //displayContainerPairs(vpair_);
    // for (unsigned int i = 0; i < vSize * 2; ++i)
    //     std::cout << jacobsthal(i) << ", "; 
    // std::cout << std::endl;
};


void PmergeMe::makePend(void) {

    unsigned int vSize = vpair_.size();
    for (unsigned int i = 1; i < vSize; i++) {  
        if (vpair_[i].second)   
            vPend_.push_back(vpair_[i].second);
    }

    //displayContainer(vPend_);     
};


void PmergeMe::makeJacobsthalLadder(void) {
    unsigned int n = 0;
    unsigned int nbr = 0;
    while (1) {
        nbr = jacobsthal(n);
        if (nbr >= (unsigned int)vPend_.size())
            break;
        jacLadder_.push_back(nbr);
        n++;
    }
};



void PmergeMe::mergeJacob(void) {
    
    jacLadder_.clear();
    std::vector<bool> inserted(vPend_.size());
    std::fill(inserted.begin(), inserted.end(), false);
    makeJacobsthalLadder();
    unsigned int pendSize = jacLadder_.size();

    for (unsigned int i = 1; i < pendSize; ++i) {
        unsigned int start = jacLadder_[i - 1];
        unsigned int end = (jacLadder_[i] < vPend_.size()) ? jacLadder_[i] : static_cast<unsigned int>(vPend_.size());

        for (int j = static_cast<int>(end) - 1; j >= static_cast<int>(start); --j) {  // Prevent unsigned underflow
            if (inserted[j]) {
                continue;
            }

            unsigned int position = 0;
            while (position < vMain_.size() && vPend_[j] > vMain_[position]) {
                ++position;
            }

            vMain_.insert(vMain_.begin() + static_cast<int>(position), vPend_[j]);
            inserted[j] = true;
        }
    }

    // **Ensure all remaining elements are inserted**
    for (unsigned int i = 0; i < vPend_.size(); ++i) {  
        if (inserted[i]) {
            continue; // Skip elements that are already inserted
        }

        unsigned int position = 0;
        while (position < vMain_.size() && vPend_[i] > vMain_[position]) {
            ++position;
        }

        // If the element is larger than everything in `vMain_`, append it at the end.
        if (position == vMain_.size()) {
            vMain_.push_back(vPend_[i]);
        } else {
            vMain_.insert(vMain_.begin() + static_cast<int>(position), vPend_[i]);
        }

        inserted[i] = true;
    }
     
}

template <typename T>
void PmergeMe::insertLastElement(T &container) {

    if (leftOverFlag_ ) {
        std::vector<unsigned int>::iterator pos = std::lower_bound(container.begin(), container.end(), leftover_);
        container.insert(pos, leftover_);
    }
};


void PmergeMe::mergeMainWithPend(void) {

    mergeJacob();   
    insertLastElement(vMain_);    

    
    displayContainer(vMain_);       
    displayContainer(vPend_);
    std::cout << "Leftover: " << leftover_ << std::endl;  
    
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
