/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:11:57 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/09/21 16:13:23 by thibaultgir      ###   ########.fr       */
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
		if (!this->checkDate(date))
			std::cout << "Error: bad input => " << date << std::endl;
		else if (pos == std::string::npos)
			std::cout << "Error: no value." << std::endl;
		else
		{
			value = line.substr(pos + 2, line.size() - pos);
			// it = this->_data_map.find(date);
			d_value = strtod(value.c_str(), NULL);
			if (d_value >= 2147483648)
				std::cout << "Error: too large a number." << std::endl;
			else if (d_value < 0)
				std::cout << "Error: not a positive number." << std::endl;
			else 
			{
				std::cout << date;
				it = this->_data_map.find(date);
				while (it == this->_data_map.end())
				{
					this->decreaseDate(date);
					it = this->_data_map.find(date);
				}
				std::cout << " => " << d_value << " = " << std::setprecision(7) << it->second * d_value << std::endl;
			}
		}
	}
	infile.close();
}

void    BitcoinExchange::printMap( std::map<std::string, double> &m ) const {
	for (std::map<std::string, double>::iterator it = m.begin(); it != m.end(); ++it)
        std::cout << '[' << it->first << "] " << std::setprecision(7) << it->second << std::endl;
}

void	BitcoinExchange::decreaseDate( std::string &date ) {
	int		dates[3];
	std::string year;
	std::string month;
	std::string day;
	size_t	pos;
	
	for(int i = 0; i < 3; i++)
	{
		pos = date.find("-");
		dates[i] = strtol(date.substr(0, pos).c_str(), NULL, 10);
		date.erase(0, pos + 1);
	}
	if (dates[2] == 1)
	{
		dates[2] = 31;
		if (dates[1] == 1)
		{
			dates[1] = 12;
			dates[0]--;
		}
		else
			dates[1]--;
	}
	else
		dates[2]--;
	std::stringstream stream0;
	std::stringstream stream1;
	std::stringstream stream2;
	stream0 << dates[0];
	stream0 >> year;
	stream1 << dates[1];
	stream1 >> month;
	stream2 << dates[2];
	stream2 >> day;
	if (day.size() == 1)
		day = "0" + day;
	if (month.size() == 1)
		month = "0" + month;
	date = year + "-" + month + "-" + day;
}

bool BitcoinExchange::checkDate( std::string date ) {
	int		dates[3];
	size_t	pos;
	
	for(int i = 0; i < 3; i++)
	{
		pos = date.find("-");
		dates[i] = strtol(date.substr(0, pos).c_str(), NULL, 10);
		date.erase(0, pos + 1);
	}
	if (!dates[0] || !dates[1] || !dates[2])
		return (false);
	if (dates[0] > 2022 || dates[0] < 2009 || dates[1] > 12 || dates[1] < 1 || dates[2] < 1 || dates[2] > 31)
		return (false);
	if (dates[0] <= 2009 && dates[1] < 2 && dates[2] < 2)
		return (false);
	return (true);
}