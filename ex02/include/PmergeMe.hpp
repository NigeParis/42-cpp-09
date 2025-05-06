/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:53:41 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/06 11:50:55 by nrobinso         ###   ########.fr       */
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


    private:

        std::vector<unsigned int> vector_;
        std::deque <unsigned int> deque_;

    
};