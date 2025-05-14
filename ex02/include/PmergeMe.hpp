/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:53:41 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/14 16:05:08 by nrobinso         ###   ########.fr       */
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
        template <typename T>
        void sortPair(T &a, T &b);
        template <typename T>
        void sort(T &a, T &b);
        template <typename T>
        void displayContainer(T &container);
        template <typename T>
        void displayContainerPairs(T &container);

    private:

        std::vector<unsigned long> vector_;
        std::vector<unsigned long> main_;
        std::vector<unsigned long> pend_;
        std::deque <unsigned long> deque_;
        std::vector<std::pair<unsigned long, unsigned long> > vpair_;


        unsigned long leftover_;
        bool leftOverFlag_;

};