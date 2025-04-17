/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:10:34 by tursescu          #+#    #+#             */
/*   Updated: 2025/04/17 14:34:17 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <iomanip>
# include <cmath>
# include <string>
# include <limits.h>
# include <limits>
# include <algorithm>
# include <fstream>
# include <sstream>
# include <map>

# define RED "\033[31m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define PINK "\033[38;5;205m"
# define TEAL "\033[38;5;30m"
# define LAVENDER "\033[38;5;183m"
# define CYAN "\033[38;5;51m"
# define LIGHT_YELLOW "\033[38;5;229m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

class BitcoinExchange
{
private:
    std::map<std::string, float> data;
    bool isValidDate(const std::string& date);
    bool isValidValue(const float value);
    std::string findClosestDate(const std::string& date);
public:
    BitcoinExchange();
    ~BitcoinExchange();
    void loadDataBase(const std::string& filename);
    void processInputFile(const std::string& filename);
    float convertValue(const std::string& date, float value);
};

#endif