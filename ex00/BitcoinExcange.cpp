/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExcange.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:44:08 by tursescu          #+#    #+#             */
/*   Updated: 2025/04/17 16:45:45 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    //map is automatically initialized, handling memory on its own
    std::cout << CYAN << "Default constructor called" << RESET << std::endl;
}
BitcoinExchange::~BitcoinExchange() {
    std::cout << RED << "Destructor called" << RESET << std::endl;
}

bool BitcoinExchange::isValidDate(const std::string &date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        std::cout << RED << "Error : bad input => " << date << RESET << std::endl;
        return false;
    }
    //extrtacting year, month and day
    std::istringstream dateStream(date);
    int year, month, day;
    char dash1, dash2;
    dateStream >> year >> dash1 >> month >> dash2 >> day;
    if (dateStream.fail() || dash1 != '-' || dash2 != '-') {
        std::cout << RED << "Error: bad input => " << date << RESET << std::endl;
        return false;  
    }
    
    //check if ranges are good
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        std::cout << RED << "Error: bad input => " << date << RESET << std::endl;
        return false;   
    }
    
    //check days in month
    int daysInMonth;
    if (month == 4 || month == 6  || month == 9 || month == 11) {
        daysInMonth = 30;
    }
    else if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        daysInMonth = isLeapYear ? 29 : 28;
        //Exlanation : If an year is divisible by 4 , it is a leap year(feb has 29 days, not 28)
        // - if the year is also divisible by 100, then it is not a leap year(1900)
        // - but if an year is divisible by 400 , then it is a leap year(2000 was a leap year)
        // we have true on leap year, then we have 29 days in feb, if not , 28.
    }
    else
        daysInMonth = 31;

    if (day > daysInMonth) {
        std::cout << RED << "Error: bad input => " << date << RESET << std::endl;
        return false;
    }
    return true;
}

bool BitcoinExchange::isValidValue(const float value) {
    if (value < 0) {
        std::cout << RED << "Error: not a positive number." << RESET << std::endl;
        return false;
    }
    else if (value >= 1000) {
        std::cout << RED << "Error: too large a number." << RESET << std::endl;
        return false; 
    }
    else {
        return true;
    }
}

std::string BitcoinExchange::findClosestDate(const std::string &date) {
    //lower bound finds the given key value(date), and if not, it finds the first iteration after it(bigger value)   lower_bound : >= date
    std::map<std::string, float>::iterator it = data.lower_bound(date);
    
    if (it != data.end() && it->first == date) {
        return it->first;// if the iterator holds the date, return it
        //also the check for .end(), if there is no key with that value, and all the other values are less than the given one, the lower_bound return data.end()
    }
    if (it == data.begin() && it->first != date) {
        return "";//if the map doesn't contain that exact date, and the next biggest value is the firs in the container,
        //that means that not only there is no key with the same value as the date passed, but there is also no date lower than that. 
    }
    if (it != data.begin() && it->first != date) {
        --it;// if the key's value is not equal to the date, and also the iterator is not pointing to the first element of the map
        //it means that we have it in the map, but it is pointing to a higer than the date key val, so we decrement one, thus pointing to the next lesser key value then what the date value was
    }
    return it->first; // return the key value. the first element of the iterator is the key value, and the second one is the "value" value
}

void BitcoinExchange::loadDataBase(const std::string &filename) {
    std::ifstream file(filename.c_str());//c_str() needed to convert std::string into char *(c++98 way); it also opens the file
    if (!file.is_open()) {
        std::cout << RED << "Error: could not open database file." << RESET << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);//skip the first line/ header line
    while(std::getline(file, line)) { //loop over each line of the file
        std::stringstream ss(line); // wraps the line into a stringstream to easily split it
        std::string date; // to parse the date
        std::string valueStr; // the raw string after comma
        float value; // the float parsed from valueStr

        if (std::getline(ss, date, ',') && std::getline(ss, valueStr)) { // splits the line by coma : 2024-04-17, 42.4242 -> "2024-04-17" and "42.4242"
            std::stringstream valueStream(valueStr);// wraps the value string in another stringstream to parse as float
            if (valueStream >> value) {//if it succeeds
                data[date] = value;// adds a new entry to the data(map) using `date` as the key and the `value` at the value
            }
        }
    }
    file.close(); // closes the file(technically not needed bcs it is handled by the destructor)..still it's good form
}

float BitcoinExchange::convertValue(const std::string &date, float value) {    
}
void processInputFile(const std::string &filename);