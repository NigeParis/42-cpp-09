/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:55:47 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/29 23:55:24 by nige42           ###   ########.fr       */
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
    float rate_;
    
    Date();
    ~Date(void);
};

class DateAndRate: public Date {

    public:

        DateAndRate();
        ~DateAndRate(void);
        
        void getDateValue(std::string &line);
        void getDateLong(void);


        void printDebug(int lineNumber, std::string &line);

    private:
    
        std::map<int, std::string> data_;
        std::map<int, unsigned int> Year_;
        std::map<int, unsigned int> Month_;
        std::map<int, unsigned int> Day_;
        std::map<int, float> Rate_;
    
};