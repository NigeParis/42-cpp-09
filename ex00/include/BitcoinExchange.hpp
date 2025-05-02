/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:55:47 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/02 10:59:53 by nige42           ###   ########.fr       */
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
#define VALUELIMIT 1000
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define GREY "\033[30m"
#define YELLOW "\033[33m"
#define LIGHTBLUE "\033[36m"
#define PINK "\033[35m"
#define RESET "\033[0m"

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
    private:
        Date(Date &copy);
        Date &operator=(Date &copy);
};

class BitcoinExchange: public Date {

    public:

        BitcoinExchange();
        BitcoinExchange(BitcoinExchange &copy);
        BitcoinExchange &operator=(BitcoinExchange &copy);
        ~BitcoinExchange(void);

        void getAndCheckData(void);
        void getAndCheckData(char *argv);
        void getInputFile(char *argv);
        int findKeyOrNearest(int key);
  
        private:
        
        std::map<int, std::string> data_;
        std::map<int, std::string> Line_;
        std::map<int, unsigned int> Year_;
        std::map<int, unsigned int> Month_;
        std::map<int, unsigned int> Day_;
        std::map<int, float> Rate_;
        
        void getDateValue(std::string &line);
        void getDateLong(void);
        void cleanLine(std::string &line);
        void swapComma(std::string &line);

        
    };