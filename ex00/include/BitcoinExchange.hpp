/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:55:47 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/28 17:36:48 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <sstream> // Required for std::ostringstream in C++98

class Date {

    public:


    protected:

        unsigned int  datelong_;
        unsigned int  year_;
        unsigned int  month_;
        unsigned int  day_;

};

class DateAndRate: public Date {

    public:

        DateAndRate();
        ~DateAndRate(void);
        
        void getDate(std::string line);
        void getDateLong(void);



    private:
    
        std::map<int, std::string> data;
    
};