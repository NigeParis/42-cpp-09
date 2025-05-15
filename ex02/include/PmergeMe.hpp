/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:53:41 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/15 13:11:57 by nige42           ###   ########.fr       */
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
#include <utility>  // For std::pair


class PmergeMe  {

    public:

        PmergeMe(void);
        ~PmergeMe(void);
        void setValues(std::string &inputStr);
        void getValues(void);
        void makePairs(void);
        void makeMain(void);
        void makePend(void);
        template <typename T>
        void sortPair(T &a, T &b);
        template <typename T>
        void displayContainer(T &container);
        template <typename T>
        void displayContainerPairs(T &container);
        void mergeJacob(void);
        void makeJacobsthalLadder(void);
        void mergeMainWithPend(void);
        template <typename T>
        void insertLastElement(T &container);

    private:

        std::vector<unsigned int> vector_;
        std::vector<unsigned int> vMain_;
        std::vector<unsigned int> vPend_;
        std::deque <unsigned int> deque_;
        std::vector<unsigned int> dMain_;
        std::vector<unsigned int> dPend_;
        std::vector<std::pair<unsigned int, unsigned int> > vpair_;
        std::vector<unsigned int> jacLadder_;


        unsigned int leftover_;
        bool leftOverFlag_;

};