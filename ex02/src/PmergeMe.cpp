/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:54:19 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/16 09:23:38 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

static unsigned int jacobsthal(unsigned int n);
static unsigned int countDigitsString(unsigned int num);
static unsigned int stringToUnsignedInt(const std::string &strNumber);

PmergeMe::PmergeMe(void) : vecTime_(0), deqTime_(0), vector_(), vpair_(), vMain_(), vPend_(),  vJacLadder_(), 
deque_(), dMain_(), dPend_(), dJacLadder_(), leftover_(0), leftOverFlag_(false) {
    //std::cout << "Default constructor" << std::endl;
};

PmergeMe::PmergeMe(PmergeMe &copy) {
    //std::cout << "Copy constructor" << std::endl;
    *this = copy;
};

PmergeMe &PmergeMe::operator=(PmergeMe &copy) {
    //std::cout << "Assignement operator" << std::endl;
    if(this != &copy) {
        this->vector_ = copy.vector_;
        this->deque_ = copy.deque_;
        this->vMain_ = copy.vMain_;
        this->dMain_ = copy.dMain_;
        this->vPend_ = copy.vPend_;
        this->dPend_ = copy.dPend_;
        this->vJacLadder_ = copy.vJacLadder_;
        this->dJacLadder_ = copy.dJacLadder_;
        this->vpair_ = copy.vpair_;
        this->dpair_ = copy.dpair_;
        this->vecTime_ = copy.vecTime_;
        this->deqTime_ = copy.deqTime_;
        this->leftover_ = copy.leftover_;
        this->leftOverFlag_ = copy.leftOverFlag_;
    }
    return (*this);
};

PmergeMe::~PmergeMe(void) {
    //std::cout << "Default destructor" << std::endl;
    this->vector_.clear();
    this->deque_.clear();
    this->vMain_.clear();
    this->dMain_.clear();
    this->vPend_.clear();
    this->dPend_.clear();
    this->vJacLadder_.clear();
    this->dJacLadder_.clear();
    this->vpair_.clear();
    this->dpair_.clear();
};

/**
* FUNCTION GENERIC
**/

template <typename T>
void PmergeMe::sortPair(T &a, T &b) {
    if (a < b)
         std::swap(a, b);
};

/**
* STD-VECTOR FUNCTIONS
**/

void PmergeMe::vecSetValues(std::string &inputStr) {
    std::istringstream inStringStream(inputStr);
    std::string strNumber;
    unsigned int number = 0;

    while (inStringStream >> strNumber) {
        number = stringToUnsignedInt(strNumber);
        if (number == 0)
            throw std::runtime_error("Error: Not positive integer");
        this->vector_.push_back(number);
    }
};

void PmergeMe::getBeforeValues(void) {
    unsigned int vSize = this->vector_.size();
    unsigned int charcount = 0;
    
    if (leftover_) {
        this->vector_.push_back(leftover_);
        vSize++;
    }
    std::cout << "Before: ";
    for (size_t i = 0; i < vSize; ++i) {   
        if (charcount > DISPLAYLIMIT) {
            std::cout << " [...]";
            break ;
        } 
        if (i == 0) {
            std::cout << this->vector_[i];
            charcount += countDigitsString(this->vector_[i]);        
        } else {
            std::cout << " " << this->vector_[i];
            charcount += countDigitsString(this->vector_[i]) + 1;        
        }      
    }
    std::cout << std::endl;
};

void PmergeMe::getAfterValues(void) {
    unsigned int vSize = this->vector_.size();
    unsigned int charcount = 0;
    
    std::cout << "After:  ";
    for (size_t i = 0; i < vSize; ++i) {
        if (charcount > DISPLAYLIMIT) {
            std::cout << " [...]";
            break ;
        }        
        if (i == 0) {
            std::cout << this->vector_[i];
            charcount += countDigitsString(this->vector_[i]);        
        } else {
            std::cout << " " << this->vector_[i];
            charcount += countDigitsString(this->vector_[i]) + 1;        
        }
    }
    std::cout << std::endl;
};

void PmergeMe::vecMakePairs(void) {
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
    for (std::vector<unsigned int>::iterator it = 
        vector_.begin(); it != vector_.end(); it++) {
        vpair_.push_back(std::make_pair(*it, *(++it)));
    }    
    unsigned int vSize = vpair_.size();
    for (unsigned int i = 0; i < vSize; i++)
        sortPair(vpair_[i].first, vpair_[i].second);
};
    
void PmergeMe::vecMakeMain(void) {
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
};

void PmergeMe::vecMakePend(void) {
    unsigned int vSize = vpair_.size();
    
    for (unsigned int i = 1; i < vSize; i++) {  
        if (vpair_[i].second)   
            vPend_.push_back(vpair_[i].second);
    }
};

void PmergeMe::vecMakeJacobsthalLadder(void) {
    unsigned int n = 0;
    unsigned int nbr = 0;
    while (1) {
        nbr = jacobsthal(n);
        if (nbr >= (unsigned int)vPend_.size())
            break;
        vJacLadder_.push_back(nbr);
        n++;
    }
};

void PmergeMe::vecMergeMainWithPend(void) {
    vecMergeJacob();   
    vecInsertLastElement();    
};

void PmergeMe::vecReplaceVecWithMain(void) {
    this->vector_.clear();
    this->vector_.insert(this->vector_.begin(), this->vMain_.begin(), this->vMain_.end());
    this->vMain_.clear();
    this->vPend_.clear();
    this->vJacLadder_.clear();
    this->vpair_.clear();    
};

void PmergeMe::vecMergeJacob(void) {
    vJacLadder_.clear();
    std::vector<bool> inserted(vPend_.size());
    std::fill(inserted.begin(), inserted.end(), false);
    vecMakeJacobsthalLadder();
    unsigned int pendSize = vJacLadder_.size();

    for (unsigned int i = 1; i < pendSize; ++i) {
        unsigned int start = vJacLadder_[i - 1];
        unsigned int end = (vJacLadder_[i] < vPend_.size()) ? 
        vJacLadder_[i] : static_cast<unsigned int>(vPend_.size());
        for (int j = static_cast<int>(end) - 1; j >= static_cast<int>(start); --j) { 
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
    for (unsigned int i = 0; i < vPend_.size(); ++i) {  
        if (inserted[i]) {
            continue;
        }
        unsigned int position = 0;
        while (position < vMain_.size() && vPend_[i] > vMain_[position]) {
            ++position;
        }
        if (position == vMain_.size()) {
            vMain_.push_back(vPend_[i]);
        } else {
            vMain_.insert(vMain_.begin() + static_cast<int>(position), vPend_[i]);
        }
        inserted[i] = true;
    }
}

void PmergeMe::vecInsertLastElement(void) {
    if (leftOverFlag_ ) {
        std::vector<unsigned int>::iterator pos = 
        std::lower_bound(vMain_.begin(), vMain_.end(), leftover_);
        vMain_.insert(pos, leftover_);
    }
};

void PmergeMe::getVecTimes(void) {
    std::cout << "Time to process a range of " 
    << this->vector_.size() << " elements with std::vector : " 
    << this->vecTime_ << " µs" << std::endl;
};

/**
* STD-DEQUE FUNCTIONS
**/

void PmergeMe::deqMergeJacob(void) {  
    dJacLadder_.clear();
    std::vector<bool> inserted(dPend_.size());
    std::fill(inserted.begin(), inserted.end(), false);
    deqMakeJacobsthalLadder();
    unsigned int pendSize = dJacLadder_.size();

    for (unsigned int i = 1; i < pendSize; ++i) {
        unsigned int start = dJacLadder_[i - 1];
        unsigned int end = (dJacLadder_[i] < dPend_.size()) 
        ? dJacLadder_[i] : static_cast<unsigned int>(dPend_.size());
        for (int j = static_cast<int>(end) - 1; j >= static_cast<int>(start); --j) {
            if (inserted[j]) {
                continue;
            }
            unsigned int position = 0;
            while (position < dMain_.size() && dPend_[j] > dMain_[position]) {
                ++position;
            }
            dMain_.insert(dMain_.begin() + static_cast<int>(position), dPend_[j]);
            inserted[j] = true;
        }
    }
    for (unsigned int i = 0; i < dPend_.size(); ++i) {  
        if (inserted[i]) {
            continue;
        }
        unsigned int position = 0;
        while (position < dMain_.size() && dPend_[i] > dMain_[position]) {
            ++position;
        }
        if (position == dMain_.size()) {
            dMain_.push_back(dPend_[i]);
        } else {
            dMain_.insert(dMain_.begin() + static_cast<int>(position), dPend_[i]);
        }
        inserted[i] = true;
    }
};

void PmergeMe::deqInsertLastElement(void) {
    if (leftOverFlag_ ) {
        std::deque<unsigned int>::iterator pos = 
        std::lower_bound(dMain_.begin(), dMain_.end(), leftover_);
        dMain_.insert(pos, leftover_);
    }
};

void PmergeMe::deqMakeJacobsthalLadder(void) {
    unsigned int n = 0;
    unsigned int nbr = 0;
    while (1) {
        nbr = jacobsthal(n);
        if (nbr >= (unsigned int)dPend_.size())
            break;
        dJacLadder_.push_back(nbr);
        n++;
    }
};

void PmergeMe::deqMakePend(void) {
    unsigned int dSize = dpair_.size();
    for (unsigned int i = 1; i < dSize; i++) {  
        if (dpair_[i].second)   
            dPend_.push_back(dpair_[i].second);
    }
};

void PmergeMe::deqMakeMain(void) {    
    unsigned int dSize = dpair_.size();
    if (dSize == 0) {
        return ;        
    }
    for (unsigned int i = 0; i < dSize; ++i) {
        for (unsigned int y = 0; y < dSize; ++y) {
            sortPair(dpair_[i], dpair_[y]);
        }
    }    
    for (unsigned int i = 0; i < dSize; ++i) { 
        if (dpair_[i].first)     
            dMain_.push_back(dpair_[i].first);
    }
    if (dpair_[0].second) 
        dMain_.insert(dMain_.begin(), dpair_[0].second);
};

void PmergeMe::deqMergeMainWithPend(void) {    
    deqMergeJacob();   
    deqInsertLastElement();    
};

void PmergeMe::deqReplaceDeqWithMain(void) {
    this->deque_.clear();
    this->deque_.insert(this->deque_.begin(), this->dMain_.begin(), this->dMain_.end());
    this->dMain_.clear();
    this->dPend_.clear();
    this->dJacLadder_.clear();
    this->dpair_.clear();    
};

void PmergeMe::getDeqTimes(void) {
    std::cout << "Time to process a range of " 
    << this->deque_.size() << " elements with std::deque  : " 
    << this->deqTime_ << " µs" << std::endl;
};

void PmergeMe::deqMakePairs(void) {
    unsigned int size = this->deque_.size();
    this->leftover_ = 0;
    this->leftOverFlag_ = false;
    
    if (size %2 != 0) {
        if (!deque_.empty()) {
            this->leftover_ = this->deque_[size - 1];
            this->deque_.pop_back();
            leftOverFlag_ = true;
        }
    }
    size = this->vector_.size();
    for (std::deque<unsigned int>::iterator it = 
        deque_.begin(); it != deque_.end(); it++) {
        dpair_.push_back(std::make_pair(*it, *(++it)));
    }    
    unsigned int dSize = dpair_.size();
    for (unsigned int i = 0; i < dSize; i++)
        sortPair(dpair_[i].first, dpair_[i].second);
};
    
/**
* HELPER FUNCTIONS
**/

static unsigned int countDigitsString(unsigned int num) {
    std::ostringstream oss;
    oss << num; // Convert number to string
    return oss.str().size();
}

static unsigned int jacobsthal(unsigned int n) {
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
        throw std::runtime_error("Error: input int too big");
    return ((unsigned int)number);
}

void PmergeMe::deqSetValues(std::string &inputStr) {
    std::istringstream inStringStream(inputStr);
    std::string strNumber;
    unsigned int number = 0;

    while (inStringStream >> strNumber) {
        number = stringToUnsignedInt(strNumber);
        if (number == 0)
            throw std::runtime_error("Error: Not positive integer");
        this->deque_.push_back(number);
    }
};

/** 
* OUTILS DEBUG
**/

template <typename T>
void PmergeMe::displayContainer(T &container) {
            
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
