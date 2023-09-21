/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:11:57 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/09/21 13:12:15 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( void ) {
	std::cout << "[ BITCOINEXCHANGE ] Constructor called" << std::endl;
	return ;
}

BitcoinExchange::~BitcoinExchange( void ) {
	std::cout << "[ BITCOINEXCHANGE ] Destructor called" << std::endl;
	return ;
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange &copy ) {
	std::cout << "[ BITCOINEXCHANGE ] Copied" << std::endl;
	*this = copy;
	return ;
}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange &copy ) {
	std::cout << "[ BITCOINEXCHANGE ]  Assignement operator called" << std::endl;
	(void)copy;
	return *this;
}

void	BitcoinExchange::openFile( std::string path ) {
	std::ifstream infile;
	infile.open(path.c_str(), std::ios::in);
	if (infile.fail())
		throw (std::exception());

	std::string date;
	std::string value;
	while (!infile.eof())
	{

		getline(infile, date, ',');
		getline(infile, value, '\n');
		this->_data_map[date] = strtod(value.c_str(), NULL);
	}
	infile.close();
	// this->printMap(this->_data_map);
}

void	BitcoinExchange::parseFile( std::string path ) {
	std::ifstream	infile;
	std::string		line;
	std::string		date;
	std::string		value;
	double			d_value;
	std::map<std::string, double>::iterator it;
	size_t			pos = 0;
	
	infile.open(path.c_str(), std::ios::in);
	if (infile.fail())
		throw (std::exception());
	getline(infile, line);
	while (!infile.eof())
	{
		getline(infile, line);
		pos = line.find(" |");
		date = line.substr(0, pos);
		if (pos == std::string::npos)
			std::cout << "Error: no value." << std::endl;
		value = line.substr(pos + 2, line.size() - pos);
		it = this->_data_map.find(date);
		// std::cout << date << " : " << value << std::endl;
		d_value = strtod(value.c_str(), NULL);
		if (d_value >= 2147483648)
			std::cout << "Error: too large a number." << std::endl;
		else if (d_value < 0)
			std::cout << "Error: not a positive number." << std::endl;
		else if (it != this->_data_map.end())
			std::cout << date << " => " << d_value << " = " << it->second * d_value << std::endl;
	}
	infile.close();
}

void    BitcoinExchange::printMap( std::map<std::string, double> &m ) const {
	for (std::map<std::string, double>::iterator it = m.begin(); it != m.end(); ++it)
        std::cout << '[' << it->first << "] " << std::setprecision(7) << it->second << std::endl;
}