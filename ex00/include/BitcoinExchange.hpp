/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:11:57 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/09/21 13:10:11 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <map>
#include <limits>
#include <cmath>

class BitcoinExchange {
    private:
        std::map<std::string, double>  _data_map;
    public:
        BitcoinExchange( void );
        ~BitcoinExchange( void );
        BitcoinExchange( const BitcoinExchange & );
        BitcoinExchange& operator=( const BitcoinExchange &);

        void    openFile( std::string path );
        void    printMap( std::map<std::string, double> &map ) const;
        void    parseFile( std::string input );
};

#endif