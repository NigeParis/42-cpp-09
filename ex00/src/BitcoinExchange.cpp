/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:56:33 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/28 16:55:35 by nrobinso         ###   ########.fr       */
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
    int dashone = 0;
    int dashtwo = 0;
    int comma = 0;
        
    while (std::getline(inputdatafile, line)) {
        data[lineNumber] = line; // Add the line to the map with the current line number as the key
        if (lineNumber == 198) {
                
            if (!isCommasDashDataCheck(line)) {
                std::cout << "Error: data format [xxxx-xx-xx,x] " << line << std::endl;
                return ;
            }
            if(!isYearFormatDataCheck(line)) {
                std::cout << "Error: format year [XXXX] " << line << std::endl;
                return ;
            }
                
            dashone = findDashOne(data[lineNumber]);
            dashtwo = findDashTwo(data[lineNumber]);
            comma = findComma(data[lineNumber]);
            
                
            this->year_ = atoi(data[lineNumber].substr(0, dashone).c_str());
            this->month_ = atoi(data[lineNumber].substr(5, dashtwo - 5).c_str());
            this->day_ = atoi(data[lineNumber].substr(dashtwo + 1, 2).c_str());

                
            std::cout << "Key: " << lineNumber << ", Value: " << line << " Y: " << data[lineNumber].substr(0,4) 
            << " M: "<< data[lineNumber].substr(5,2) << " D: "<< data[lineNumber].substr(8,2) 
            << " dash1: " <<  dashone
            << " dash2: " <<  dashtwo
            << " comma: " <<  comma << std::endl;
                
                
                
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