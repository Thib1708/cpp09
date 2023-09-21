/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:22:38 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/09/21 12:59:12 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cout << "Error: Wrong amount of argument\nusage: ./btc <infile>" << std::endl, 1);
	else
	{
		BitcoinExchange btc;
		try
		{
			btc.openFile("data.csv");
			btc.parseFile(argv[1]);
		}
		catch(std::exception &e)
		{
			std::cout << "Can't open file" << std::endl;
			return (1);
		}
	}
	return (0);
}