/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:12:53 by nige42            #+#    #+#             */
/*   Updated: 2025/05/16 08:50:07 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

void checkInput(std::string &inputStr);
void removeExtraSpaces(std::string &inputStr);
bool isUnique(const std::vector<std::string> &vec, const std::string &value);
double calTimeDiff(clock_t &startTime, clock_t &endTime);
std::string removeDuplicates(const std::string &inputStr);

int main(int argc, char *argv[]) {

    PmergeMe data;
    std::stringstream lineOfArgs;
    std::string inputStr = "";
    clock_t parsingStartTime;
    clock_t parsingEndTime;
    clock_t vecStartTime;
    clock_t vecEndTime;
    clock_t deqStartTime;
    clock_t deqEndTime;

    if (argc < 2) {
        std::cout << "./PmergeMe \"[NUM] [NUM] etc..." << std::endl;
        return -1;
    }
    try {
        
        for (int i = 1; i < argc; i++) {
            lineOfArgs << argv[i];
            if (i < argc - 1)
            lineOfArgs << " ";
        }
        parsingStartTime = clock();
        std::getline(lineOfArgs, inputStr);
        checkInput(inputStr);
        removeExtraSpaces(inputStr);
        inputStr = removeDuplicates(inputStr);
        parsingEndTime = clock();
        data.vecTime_ = calTimeDiff(parsingStartTime, parsingEndTime);
        data.deqTime_ = calTimeDiff(parsingStartTime, parsingEndTime);
        vecStartTime = clock();
        data.vecSetValues(inputStr);
        data.vecMakePairs();
        data.vecMakeMain();
        data.vecMakePend();
        data.vecMergeMainWithPend();
        vecEndTime = clock();
        data.vecTime_ += calTimeDiff(vecStartTime, vecEndTime);
        deqStartTime = clock();
        data.deqSetValues(inputStr);
        data.deqMakePairs();
        data.deqMakeMain();
        data.deqMakePend();
        data.deqMergeMainWithPend();
        deqEndTime = clock();
        data.deqTime_ += calTimeDiff(deqStartTime, deqEndTime);
        data.getBeforeValues();
        vecStartTime = clock();
        data.vecReplaceVecWithMain();
        vecEndTime = clock();
        data.vecTime_ += calTimeDiff(vecStartTime, vecEndTime);
        deqStartTime = clock();
        data.deqReplaceDeqWithMain();
        deqEndTime = clock();
        data.deqTime_ += calTimeDiff(deqStartTime, deqEndTime);
        data.getAfterValues();
        data.getVecTimes();
        data.getDeqTimes();
    }
    catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }   
    return 0;
}

/**
* HELPER FUNCTIONS
**/

void checkInput(std::string &inputStr) {

    bool onlySpaces = true;
    int  count = 0;   

    for (std::string::iterator it = inputStr.begin(); it != inputStr.end(); ++it) {
        if (count > 10)
            throw std::runtime_error("Error: input int too big");
        if ((isdigit(*it))) {
            onlySpaces = false;
            count++;
            continue;
        }
        if ((isspace(*it))) {
            count = 0;
            continue;
        }
        if (!isdigit(*it))
            throw std::runtime_error("Error: Input invalide");
    }
    if (onlySpaces)
        throw std::runtime_error("Error: Input empty or only spaces");
};

void removeExtraSpaces(std::string &inputStr) {
    std::string result;
    bool lastWasSpace = false;
    for (size_t i = 0; i < inputStr.size(); ++i) {

        if (i == 0  && inputStr[0] == ' ') {
            while (inputStr[i] == ' ') {
                i++;
            }
        }
        if (inputStr[i] == ' ') {
            if (!lastWasSpace) {
                result += inputStr[i];
            }
            lastWasSpace = true;
        } else {
            result += inputStr[i];
            lastWasSpace = false;
        }
    }
    if (result[result.size() - 1] == ' ')
        inputStr = result.substr(0,result.size() - 1);
    else
        inputStr = result;
};

bool isUnique(const std::vector<std::string> &vec, const std::string &value) {
    
    std::vector<std::string>::const_iterator it;
    
    it = std::find(vec.begin(), vec.end(), value);
    if (it == vec.end())
        return (true);
    return (false);
}

std::string removeDuplicates(const std::string &inputStr) {
    
    std::istringstream inStringStream(inputStr);
    std::vector<std::string> uniqueNumbers;
    std::string number;
    std::string result;

    while (inStringStream >> number) {
        if (isUnique(uniqueNumbers, number)) {  // Check if number is already in the vector
            uniqueNumbers.push_back(number);
            if (result.empty()) {
                result += number;
            } else {
                result += " ";
                result += number;
            }
        }
    }

    return result;
}

double calTimeDiff(clock_t &startTime, clock_t &endTime) {

    return (static_cast<double>(endTime - startTime) * 1000000.0 ) / CLOCKS_PER_SEC;        
}
