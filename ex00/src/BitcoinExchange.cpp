/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:56:33 by nrobinso          #+#    #+#             */
/*   Updated: 2025/04/30 18:35:47 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

Date::Date() {};
Date::~Date(void) {};

static void isDigits(std::string &line) {
    std::string allowed_chars = "0123456789-.,";
    std::size_t pos = line.find(',');
    std::string msg = "Error: bad input => " + line.substr(0, pos);    
    std::string msg2 = "Error: bad input => " + line.substr(0);    
    if (line.find_first_not_of(allowed_chars) != std::string::npos) {
        if (line.find_first_not_of(allowed_chars) < 11)
            throw std::out_of_range(msg);
        else
            throw std::out_of_range(msg2);
    }    
};

static void isValidDate(std::string &line, unsigned int &year, unsigned int &month, unsigned int &day) {

    std::size_t pos = line.find(',');
    std::string msg = "Error: bad input => " + line.substr(0, pos);
    bool leapYear = false;

    if (year < 1000 || month < 1 || month > 12 || day < 1 || day > 31) {
        throw std::out_of_range(msg);
    }
    if ((year / 4) == 0)
        leapYear = true;
    if (!leapYear && month == 2 && day > 28) { 
    throw std::out_of_range(msg);
    }
    if (leapYear && month == 2 && day > 29){ 
        throw std::out_of_range(msg);
        }
    if (month == 2)
        return ;
    if ((month == 4 || month == 6 || month ==9 || month ==11) && day > 30) { 
        throw std::out_of_range(msg);
    }
};

static void isRateValid(std::string &line, ssize_t &value) {
    (void)line;
    std::string msg = "Error: not a positive number.";
    std::string msg2 = "Error: too large a number.";
    if (value < 0)
        throw std::out_of_range(msg);    
    if (value >= RATELIMIT)
        throw std::out_of_range(msg2);
};

static bool isYearFormatDataCheck(std::string &line) {
    std::string year;
    std::size_t pos = line.find(',');
    std::string msg = "Error: bad input => " + line.substr(0, pos);
    
    year = line.substr(0, line.find('-')).c_str();
    if (year.size() != 4)
        throw std::out_of_range(msg);
    for (size_t i = 0; i < year.size(); i++) {
        if(year[i] < '0' || year[i] > '9')
            throw std::out_of_range(msg);
    }
    return true;
};

static bool isCommasDashDataCheck(std::string &line) {

    int count = 0;
    int comma = 0;
    std::string msg = "Error: bad input => " + line;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '-' && i < 9)
            count++;
        if (line[i] == ',')
            comma++;
        if (comma > 1)
            throw std::out_of_range(msg);
    }
    if (count == 2 && comma == 1) {
        return true;
    }
    throw std::out_of_range(msg);
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

int BitcoinExchange::findKeyOrNearest(int key) {

    std::cout << "Find Key: from database input" << std::endl;
    int Key = 0;

    if (key < 10000000 || key > 99999999) 
        throw std::out_of_range("Error: database key invalid");
    
    for (std::map<int,  std::string>::const_iterator itc = data_.begin(); itc != data_.end(); ++itc) {    
        Key = itc->first;
        std::map<int,  std::string>::const_iterator itp = data_.begin();
        if (key < itp->first ) {
            throw std::out_of_range("Error: not found in database");
        }
        if (Key == 0)
            throw std::out_of_range("Error: empty database ");
        if (Key == key) {
            Key = itc->first;
            break;
        }
        if (Key > key) {
            --itc;
            Key = itc->first;
            break;  
        }
    }    
    if (Key == 0)
        throw std::out_of_range("Error: empty database");    
    return (key);
};

void BitcoinExchange::getDateValue(std::string &line) {

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

void BitcoinExchange::getDateLong(void) {
    
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

static  std::ifstream openfile(std::string const &file) {

    std::ifstream inputdatafile;
    inputdatafile.open(file);
    
    if (!inputdatafile.is_open()) {
        throw std::out_of_range("Error: could not open file.");        
    };
    return (inputdatafile);
};

void BitcoinExchange::getAndCheckData(void) {
    std::cout << "getAndCheckData() called" << std::endl;
    
    std::string line;
    int lineNumber = 0;
    std::ifstream inputdatafile;
    int errorsFound = 0;
        
    try {
        inputdatafile = openfile(DATABASE);
    }
    catch(std::exception &e) {
        std::cerr << e.what() << line << std::endl;
        return;
    }
    while (std::getline(inputdatafile, line)) {
        if (lineNumber > 0) {       
            try {
                errorsFound++;
                isDigits(line);
                isCommasDashDataCheck(line);
                isYearFormatDataCheck(line);
                errorsFound--;
                
            }
            catch(std::out_of_range &e ) {
                if (errorsFound == 1)
                    std::cout << "Liste des errors in dataBase found" << std::endl;
                std::cerr << e.what() << std::endl;
                continue ;   
            }
            getDateValue(line);
            getDateLong();
            try {
                errorsFound++;
                isValidDate(line, this->year_, this->month_, this->day_);
                ssize_t safeRate = static_cast<ssize_t>(rate_);
                isRateValid(line, safeRate);
                errorsFound--;
            }
            catch(std::out_of_range &e ) {
                if (errorsFound == 1)
                    std::cout << "Liste des errors in dataBase found" << std::endl;
                std::cerr << e.what() << std::endl;
                continue ;   
            }
            data_[datelong_] = line; // Add the line to the map with the current line number as the key
            Line_[datelong_] = line; // Add the line to the map with the current line number as the key
            Year_[datelong_] = year_;
            Month_[datelong_] = month_;
            Day_[datelong_] = day_;
            Rate_[datelong_] = rate_;
        }
        ++lineNumber;
    }
    try {
        std::cout << std::endl;
        //print();
        //print(20100102);
        //std::cout << BitcoinExchange::Rate_[findKeyOrNearest(20100102)] << std::endl;
    }
    catch(std::out_of_range &e ) {
        std::cerr << e.what() << line << std::endl;
    }
    inputdatafile.close();
};

;


void BitcoinExchange::cleanLine(std::string &line) {


    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    std::replace(line.begin(), line.end(), '|', ',');
    
};





void BitcoinExchange::getInputFile(char *str) {

    std::ifstream inputfile; 
    std::string line;
    Date data;
    unsigned int count = 0;

    try {
        inputfile = openfile(str);
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    try {
      
        while (std::getline(inputfile, line)) {

            if (count > 0) {   
                cleanLine(line);   
                try {
                    isDigits(line);
                    isCommasDashDataCheck(line);
                    isYearFormatDataCheck(line);
                
                }
                catch(std::out_of_range &e ) {
                    std::cerr << e.what() << std::endl;
                    continue ;   
                }

            
                getDateValue(line);
                getDateLong();    

                try {
                    ssize_t safeRate = static_cast<ssize_t>(rate_);
                    isValidDate(line, this->year_, this->month_, this->day_);
                    isRateValid(line, safeRate);
                }
                catch(std::out_of_range &e ) {
                    std::cerr << e.what() << std::endl;
                    continue ;   
                }   



                std::cout << line << " => " << rate_ << " datelong: " << datelong_ << std::endl;   
            }
            count++;
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    
    inputfile.close();
}


















BitcoinExchange::BitcoinExchange() {std::cout << "default BitcoinExchange constructor" << std::endl;};
BitcoinExchange::~BitcoinExchange() {std::cout << "default destructor" << std::endl;};


//DEBUG FUNCTIONS
void BitcoinExchange::printDebug(int lineNumber, std::string &line) {
    
    
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

void  BitcoinExchange::print(void) {
    
    std::cout << "Display all valid: database inputs" << std::endl;
    for (std::map<int,  std::string>::const_iterator it = data_.begin(); it != data_.end(); ++it) {
        std::cout << "key [ "<< it->first << " ] -> " << std::left << std::setw(20) << it->second 
        << " => " << Year_[it->first];
        if(Month_ [it->first]< 10)
            std::cout << "-0" << std::setw(1) << Month_[it->first];
        else
            std::cout << "-" << std::setw(2) << Month_[it->first];
        if(Day_ [it->first]< 10)
            std::cout << "-0" << std::setw(1) << Day_[it->first];
        else
            std::cout << "-" << std::setw(2) << Day_[it->first];

        std::cout << " => Rate: " << std::setw(-8)  << Rate_[it->first];

        std::cout << std::endl;
    }    
};

void BitcoinExchange::print(int key) {

    std::cout << "Display a valid: database input" << std::endl;
    int Key = 0;
    
    for (std::map<int,  std::string>::const_iterator itc = data_.begin(); itc != data_.end(); ++itc) {    
        Key = itc->first;
        std::map<int,  std::string>::const_iterator itp = data_.begin();
        if (key < itp->first ) {
            throw std::out_of_range("Error: not found in database");
        }
        if (Key == 0)
            throw std::out_of_range("Error: empty database");
        if (Key == key) {
            Key = itc->first;
            break;
        }
        if (Key > key) {
            --itc;
            Key = itc->first;
            break;  
        }
        
    }    
    if (Key == 0)
        throw std::out_of_range("Error: empty database");    
    std::cout << "key [ "<< Key << " ] -> " << std::left << std::setw(20) << Line_ [Key]
    << " => " << Year_[Key];
    if(Month_ [Key]< 10)
        std::cout << "-0" << std::setw(1) << Month_[Key];
    else
        std::cout << "-" << std::setw(2) << Month_[Key];
    if(Day_ [Key]< 10)
        std::cout << "-0" << std::setw(1) << Day_[Key];
    else
        std::cout << "-" << std::setw(2) << Day_[Key];
        std::cout << " => Rate: " << std::setw(-8)  << Rate_[Key];
        std::cout << std::endl;
};

