/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:22:43 by tursescu          #+#    #+#             */
/*   Updated: 2025/04/20 16:48:26 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cout << RED << "Error: could not open file" << RESET << std::endl;
        std::cout << BLUE << "Usage: ./btc <input_file>" << RESET << std::endl; 
        return 1;
    }
    BitcoinExchange btc; //instanciate the BitcoinExchange object
    btc.loadDataBase("data.csv");// load the database from CSV file
    btc.processInputFile(av[1]);// process the input file provided as an argument
    return 0;
}