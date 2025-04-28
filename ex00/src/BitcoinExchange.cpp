/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:56:33 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/28 17:41:58 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

static bool isYearFormatDataCheck(std::string line) {
    std::string year;
    year = line.substr(0, line.find('-')).c_str();
    if (year.size() != 4)
        return false;
    for (size_t i = 0; i < year.size(); i++) {

        if(year[i] < '0' || year[i] > '9')
            return false;   
    }
    return true;
};

static bool isCommasDashDataCheck(std::string line) {

    int count = 0;
    int comma = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '-')
            count++;
        if (line[i] == ',')
            comma++;
    }
        if (count == 2 && comma == 1)
            return true;
    return false;
};

static size_t findDashOne(std::string line) {

    size_t dashpos1 = 0;    
    dashpos1 = line.find('-');    
    return (dashpos1);  
};

static size_t findDashTwo(std::string line) {

    size_t dashpos1 = 0;
    size_t dashpos2 = 0;
    
    dashpos1 = line.find('-');    
    if (dashpos1 != std::string::npos) {
        dashpos2 = line.find('-', dashpos1 + 1);                
    } 
    return (dashpos2);  
};

static size_t findComma(std::string line) {

    size_t commapos = 0;  
    commapos = line.find(',');    
    return (commapos);  
};

void DateAndRate::getDate(std::string line) {

    int dashone = 0;
    int dashtwo = 0;
    int comma = 0;
              
    dashone = findDashOne(line);
    dashtwo = findDashTwo(line);
    comma = findComma(line);    
    this->year_ = atoi(line.substr(0, dashone).c_str());
    this->month_ = atoi(line.substr(5, dashtwo - 5).c_str());
    this->day_ = atoi(line.substr(dashtwo + 1, 2).c_str());
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
        data[lineNumber] = line; // Add the line to the map with the current line number as the key
        if (lineNumber < 198 && lineNumber > 0) {
                
            if (!isCommasDashDataCheck(line)) {
                std::cout << "Error: data format [xxxx-xx-xx,x] " << line << std::endl;
                return ;
            }
            if(!isYearFormatDataCheck(line)) {
                std::cout << "Error: format year [XXXX] " << line << std::endl;
                return ;
            }
        
            getDate(line);
            getDateLong();
    
         
        
            std::cout << "datelong: " << datelong_ << std::endl; // Output: "20130101"
                 
            std::cout << "Key: " << lineNumber << ", Value: " << line << " Y: " << data[lineNumber].substr(0,4) 
            << " M: "<< data[lineNumber].substr(5,2) << " D: "<< data[lineNumber].substr(8,2) 
            << std::endl;
                
                
                
            std::cout << "year: " << year_;
            std::cout << " month: " << month_;
            std::cout << " day: " << day_ << std::endl;
        }
        ++lineNumber;
    }
    // Add file processing logic here if needed

    
    inputdatafile.close();
}




DateAndRate::~DateAndRate() {

};