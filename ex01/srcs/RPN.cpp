/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:23:11 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/09/27 12:30:24 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int		calculate( std::stack<double> &s, char	expr) {
	double numbers[2];
	double result;

	if (s.size() < 2)
		return (std::cout << "Error" << std::endl, -1);
	numbers[0] = s.top();
	s.pop();
	numbers[1] = s.top();
	s.pop();
	switch(expr) {
		case '*': {
			result = numbers[0] * numbers[1];
			if (result > 2147483647 || result < -2147483648)
				return (std::cout << "Error: overflow" << std::endl, -1);
			return (result);
		}
		case '/': {
			result = numbers[1] / numbers[0];
			if (result > 2147483647 || result < -2147483648)
				return (std::cout << "Error: overflow" << std::endl, -1);
			if (numbers[1] == 0)
				return (std::cout << "Error: division by 0" << std::endl, -1);
			return (result);
		}
		case '+': {
			result = numbers[0] + numbers[1];
			if (result > 2147483647 || result < -2147483648)
				return (std::cout << "Error: overflow" << std::endl, -1);
			return (result);
		}
		case '-': {
			result = numbers[0] - numbers[1];
			if (result > 2147483647 || result < -2147483648)
				return (std::cout << "Error: overflow" << std::endl, -1);
			return (result);
		}
	}
	return (-1);
}

void	parseNumber( std::string str ) {
	std::istringstream	iss(str);
	std::stack<double>	s;
	std::string 		value;

	while (getline(iss, value, ' '))
	{
		if (value == "+" || value == "-" || value == "*" || value == "/")
		{
			s.push(calculate(s, value[0]));
			if (s.top() == -1)
				return ;
		}
		else
		{
			for (int i = 0; value[i]; i++)
			{
				if (!isdigit(value[i]))
				{
					std::cout << "Error: non numeric character" << std::endl;
					return ;
				}
			}
			s.push(std::strtol(value.c_str(), NULL, 10));
			if (s.top() > 9)
			{
				std::cout << "Error: number should not be supperior to 9" << std::endl;
				return ;
			}
		}
	}
	std::cout << s.top() << std::endl;
}