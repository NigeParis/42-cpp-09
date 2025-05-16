/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:53:41 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/16 09:09:53 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <exception>
#include <string>
#include <limits>
#include <algorithm>
#include <utility>
#include <ctime>
#include <time.h>
#include <unistd.h>
#define DISPLAYLIMIT 30

class PmergeMe  {

    public:

        PmergeMe(void);
        PmergeMe(PmergeMe &copy);
        PmergeMe &operator=(PmergeMe &other);
        ~PmergeMe(void);
        
        void getBeforeValues(void);
        void getAfterValues(void);
        void vecSetValues(std::string &inputStr);
        void vecMakePairs(void);
        void vecMakeMain(void);
        void vecMakePend(void);
        void vecMakeJacobsthalLadder(void);
        void vecMergeJacob(void);
        void vecMergeMainWithPend(void);
        void vecInsertLastElement(void);
        void getVecTimes(void);
        void vecReplaceVecWithMain(void);        
        void deqSetValues(std::string &inputStr);
        void deqMakePairs(void);
        void deqMakeMain(void);
        void deqMakePend(void);
        void deqMakeJacobsthalLadder(void);
        void deqMergeJacob(void);
        void deqMergeMainWithPend(void);
        void deqInsertLastElement(void);
        void deqReplaceDeqWithMain(void);
        void getDeqTimes(void);
        template <typename T>
        void sortPair(T &a, T &b);
        template <typename T>
        void displayContainer(T &container);
        template <typename T>
        void displayContainerPairs(T &container);
        double vecTime_;
        double deqTime_;
        
    private:

        std::vector<unsigned int> vector_;
        std::vector<std::pair<unsigned int, unsigned int> > vpair_;
        std::vector<unsigned int> vMain_;
        std::vector<unsigned int> vPend_;
        std::vector<unsigned int> vJacLadder_;
        std::deque <unsigned int> deque_;
        std::deque<std::pair<unsigned int, unsigned int> > dpair_;
        std::deque<unsigned int> dMain_;
        std::deque<unsigned int> dPend_;
        std::deque<unsigned int> dJacLadder_;
        unsigned int leftover_;
        bool leftOverFlag_;
};
