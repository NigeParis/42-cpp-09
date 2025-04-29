/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:56:33 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/29 17:47:26 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

void  printMap(std::map<int, std::string> &data) {
    for (std::map<int, std::string>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }    
};

Date::Date() {};
Date::~Date(void) {};

static bool isYearFormatDataCheck(std::string &line) {
    std::string year;
    year = line.substr(0, line.find('-')).c_str();
    if (year.size() != 4)
        throw std::out_of_range("Error: bad input => ");
    for (size_t i = 0; i < year.size(); i++) {
        if(year[i] < '0' || year[i] > '9')
            throw std::out_of_range("Error: bad input => ");
    }
    return true;
};

static bool isCommasDashDataCheck(std::string &line) {

    int count = 0;
    int comma = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '-' && i < 9)
            count++;
        if (line[i] == ',')
            comma++;
        if (comma > 1)
            throw std::out_of_range("Error: bad input => ");
    }
    if (count == 2 && comma == 1) {
        return true;
    }
    throw std::out_of_range("Error: bad input => ");
};

static size_t findDashOne(std::string &line) {

    size_t dashpos1 = 0;    
    dashpos1 = line.find('-');    
    return (dashpos1);
};

static size_t findDashTwo(std::string &line) {

    size_t dashpos1 = 0;
    size_t dashpos2 = 0;
  
    dashpos1 = line.find('-');    
    if (dashpos1 != std::string::npos) {
        dashpos2 = line.find('-', dashpos1 + 1);                
    }
    return (dashpos2);  
};

static size_t findComma(std::string &line) {

    size_t commapos = 0;  
    commapos = line.find(',');    
    return (commapos); 
};

void DateAndRate::getDateValue(std::string &line) {

    int dashone = 0;
    int dashtwo = 0;
    int comma = 0;
              
    dashone = findDashOne(line);
    dashtwo = findDashTwo(line);
    comma = findComma(line);    
    this->year_ = atoi(line.substr(0, dashone).c_str());
    this->month_ = atoi(line.substr(5, dashtwo - 5).c_str());
    this->day_ = atoi(line.substr(dashtwo + 1, 2).c_str());
    this->rate_ = atof(line.substr(comma + 1).c_str());
};

void DateAndRate::getDateLong(void) {
    
    std::ostringstream datecode_;
    std::string temp;
    
    datecode_ << year_;
    if (month_ < 10)
        datecode_ << 0 << month_;
    else     
        datecode_ << month_;
    if (day_ < 10)
        datecode_ << 0 << day_;
    else     
        datecode_ << day_;
    temp = datecode_.str();
    this->datelong_ = atoi(temp.c_str());
};

void isDigits(std::string &line) {
    std::string allowed_chars = "0123456789-.,";    
    if (line.find_first_not_of(allowed_chars) != std::string::npos) {
        throw std::out_of_range("Error: bad input => ");
    }    
};


DateAndRate::DateAndRate() {
    std::cout << "default constructor" << std::endl;

    std::ifstream inputdatafile;
    
    inputdatafile.open("data.csv");    
    if (!inputdatafile.is_open()) {
        std::cerr << "Error: file not open" << std::endl;
        return;
    }
    
    std::string line;
    int lineNumber = 0;
 
    while (std::getline(inputdatafile, line)) {
        if (lineNumber < 201 && lineNumber > 190) {

            try {
                isDigits(line);
                isCommasDashDataCheck(line);
                isYearFormatDataCheck(line);
            }
            catch(std::out_of_range &e ) {
                std::cerr << e.what() << line << std::endl
                << std::endl;
                continue ;   
            }
            
            getDateValue(line);
            getDateLong();
           // printDebug(datelong_, line);
            data[datelong_] = line; // Add the line to the map with the current line number as the key
            
    
        }
        ++lineNumber;
    }
    // Add file processing logic here if needed

    printMap(data);
    inputdatafile.close();
};



void DateAndRate::printDebug(int lineNumber, std::string &line) {

    
    std::cout << "datelong: " << datelong_ // Output: "20130101"
    << " Key: " << lineNumber << " line: " << line << " Y: " << line.substr(0,4) 
    << " M: "<< line.substr(5,2) << " D: "<< line.substr(8,2) 
    << std::endl;
        
        
        
    std::cout << "year: " << year_;
    std::cout << " month: " << month_;
    std::cout << " day: " << day_;
    std::cout << " rate: " << rate_ 
    << std::endl << std::endl;
    
};


DateAndRate::~DateAndRate() {};