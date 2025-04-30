/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:55:47 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/30 16:05:18 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <sstream> // Required for std::ostringstream in C++98
#include <iomanip>
#include <cstdlib> // for ssize_t on POSIX systems

#define DATABASE "data.csv"
#define RATELIMIT 16777216

class Date {

    public:

    Date();
    ~Date(void);
    
    
    protected:
    
    unsigned int  datelong_;
    unsigned int  year_;
    unsigned int  month_;
    unsigned int  day_;
    float rate_;
    
};

class BitcoinExchange: public Date {

    public:

        BitcoinExchange();
        ~BitcoinExchange(void);

        void getAndCheckData(void);
        void getInputFile(char *argv);

        int findKeyOrNearest(int key);
        
        
        void printDebug(int lineNumber, std::string &line);
        void print(void);
        void print(int key);
        
        private:
        
        std::map<int, std::string> data_;
        std::map<int, std::string> Line_;
        std::map<int, unsigned int> Year_;
        std::map<int, unsigned int> Month_;
        std::map<int, unsigned int> Day_;
        std::map<int, float> Rate_;
        
        void getDateValue(std::string &line);
        void getDateLong(void);
        
    };