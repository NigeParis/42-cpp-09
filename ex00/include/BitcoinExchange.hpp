/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:55:47 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/28 15:40:44 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>


class Date {

    public:


    protected:

        unsigned int  year_;
        unsigned int  month_;
        unsigned int  day_;

};

class DateAndRate: public Date {

    public:

        DateAndRate();
        ~DateAndRate(void);


    private:
    
        std::map<int, std::string> data;
    
};