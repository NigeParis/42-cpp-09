/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:56:33 by nrobinso          #+#    #+#             */
/*   Updated: 2025/05/02 13:54:52 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

Date::Date(): datelong_(0), year_(0), month_(0), day_(0), rate_(0) {};
Date::Date(Date &copy) {*this = copy;};
Date &Date::operator=(Date &copy) {
    if(this != &copy) {
        this->datelong_ = copy.datelong_;
        this->year_ = copy.year_;
        this->month_ = copy.month_;
        this->day_ = copy.day_;
        this->rate_ = copy.rate_;
    }
    return(*this);
};
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

static void isDigitsInput(std::string &line) {
    std::string allowed_chars = "0123456789-.| ";
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

static void isRateValid(std::string &line, float &value) {
    (void)line;
    std::string msg = "Error: not a positive number.";
    std::string msg2 = "Error: too large a number.";
    if (value < 0)
        throw std::out_of_range(msg);    
    if (value > RATELIMIT)
        throw std::out_of_range(msg2);
};

static void isValueValid(std::string &line, float &value) {
    (void)line;
    std::string msg = "Error: not a positive number.";
    std::string msg2 = "Error: too large a number.";
    if (value <= 0)
        throw std::out_of_range(msg);    
    if (value >= VALUELIMIT)
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

static size_t findNbOfrCommas(std::string &line) {

    size_t commapos = 0;  

    for (std::string::const_iterator itc = line.begin(); itc != line.end(); ++itc) {    
        if (*itc == ',')   
            commapos++;
    }
    return (commapos); 
};

int BitcoinExchange::findKeyOrNearest(int key) {

    // std::cout << "Find Key: from database input" << std::endl;
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
    return (Key);
};

void BitcoinExchange::getDateValue(std::string &line) {

    int dashone = 0;
    int dashtwo = 0;
    int comma = 0;
    std::string msg = "Error: bad input => " + line.substr(0);    
          
    dashone = findDashOne(line);
    dashtwo = findDashTwo(line);
    comma = findComma(line);
    if (comma == 0)
        throw std::out_of_range(msg);
    if ((line.size() == 11) || (findNbOfrCommas(line) > 1))
        throw std::out_of_range(msg);   

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
    //std::cout << "getAndCheckData() called" << std::endl;
    
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
            if (line.empty())
                    continue;
            try {
                errorsFound++;
                cleanLine(line);   
                isDigits(line);
                isCommasDashDataCheck(line);
                isYearFormatDataCheck(line);
                getDateValue(line);
                getDateLong();
                isValidDate(line, this->year_, this->month_, this->day_);
                float safeRate = static_cast<float>(rate_);
                isRateValid(line, safeRate);
                errorsFound--;
                
            }
            catch(std::out_of_range &e ) {
                if (errorsFound == 1)
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
    inputdatafile.close();
};

void BitcoinExchange::getAndCheckData(char *str) {
    //std::cout << "getAndCheckData() called" << std::endl;
    (void)str;
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
                if (line.empty()) {
                    throw std::out_of_range("Empty: bad input => Empty line");
                }
                cleanLine(line);   
                isDigits(line);
                isCommasDashDataCheck(line);
                isYearFormatDataCheck(line);
                getDateValue(line);
                getDateLong();
                isValidDate(line, this->year_, this->month_, this->day_);
                float safeRate = static_cast<float>(rate_);
                isRateValid(line, safeRate);
                errorsFound--;
            }
            catch(std::out_of_range &e ) {
                if (errorsFound == 1)
                    std::cout << RED << "List of all errors in dataBase found" << RESET << std::endl;
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
    if (errorsFound)
        std::cout << "        -----------" << std::endl;
    
    inputdatafile.close();
};

void BitcoinExchange::cleanLine(std::string &line) {
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    std::replace(line.begin(), line.end(), '|', ',');
    
};

void BitcoinExchange::swapComma(std::string &line) {
    std::replace(line.begin(), line.end(), ',', '|');
    
};

void BitcoinExchange::getInputFile(char *str) {

    std::ifstream inputfile; 
    std::string line;
    Date dataInput;
    float result = 0;
    float rate = 0;
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
            
            if (inputfile.fail() && !inputfile.eof()) { // Check for errors other than EOF
                throw std::runtime_error("Error: could not read file.");        
                
            }
            if (count > 0) {   
                if (line.empty())
                    continue;
                try {
                    isDigitsInput(line);
                    cleanLine(line);   
                    isCommasDashDataCheck(line);
                    isYearFormatDataCheck(line);
                    getDateValue(line);
                    getDateLong();    
                    float safeRate = static_cast<float>(rate_);
                    isValidDate(line, this->year_, this->month_, this->day_);
                    isValueValid(line, safeRate);
                    swapComma(line);
                    rate  = BitcoinExchange::Rate_[findKeyOrNearest(datelong_)];   
                    result = rate_ * rate;   
                    std::cout << line.substr(0, 10) << " => " << rate_ << " = " << result <<  std::endl;   
                }
                catch(std::out_of_range &e ) {
                    std::cerr << e.what() << std::endl;
                    continue ;   
                }              
                
                
                
            
        // std::cout << BitcoinExchange::Rate_[findKeyOrNearest(datelong_)] << std::endl;
          
            }
            count++;
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    inputfile.close();
}

BitcoinExchange::BitcoinExchange(): data_(), Line_(), Year_(), Month_(), Day_(), Rate_() {
    //std::cout << "default BitcoinExchange constructor" << std::endl;
};

BitcoinExchange::BitcoinExchange(BitcoinExchange &copy) {*this = copy;};

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &copy) {

    if (this != &copy) {

        this->data_ = copy.data_;
        this->Line_ = copy.Line_;
        this->Year_ = copy.Year_;
        this->Month_ = copy.Month_;
        this->Day_ = copy.Day_;
        this->Rate_ = copy.Rate_;
    }
    return (*this);
};

BitcoinExchange::~BitcoinExchange() {
    //std::cout << "default destructor" << std::endl;
};

