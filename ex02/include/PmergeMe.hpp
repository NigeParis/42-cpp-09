/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:53:41 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/12 21:09:00 by nige42           ###   ########.fr       */
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


class PmergeMe  {

    public:

        PmergeMe(void);
        ~PmergeMe(void);
        void setValues(std::string &inputStr);
        void getValues(void);
        void makePairs(void);
        template <typename T>
        void swapPairs(T &a, T &b);
        template <typename T>
        void sortPair(T &a, T &b);

    private:

        std::vector<unsigned int> vector_;
        std::deque <unsigned int> deque_;
        std::vector<std::pair<unsigned int, unsigned int> > vpair_;
        unsigned int leftover_;
        bool leftOverFlag_;

};