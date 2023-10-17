/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:23:11 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/10/17 12:38:15 by tgiraudo         ###   ########.fr       */
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
			result = numbers[1] * numbers[0];
			if (result > 2147483647 || result < -2147483648)
				throw(std::runtime_error("Error: overflow"));
			return (result);
		}
		case '/': {
			if (numbers[1] == 0)
				throw(std::runtime_error("Error: division by 0"));
			if (numbers[0] == 0)
				return (0);
			result = numbers[1] / numbers[0];
			if (result > 2147483647 || result < -2147483648)
				throw(std::runtime_error("Error: overflow"));
			return (result);
		}
		case '+': {
			result = numbers[1] + numbers[0];
			if (result > 2147483647 || result < -2147483648)
				throw(std::runtime_error("Error: overflow"));
			return (result);
		}
		case '-': {
			result = numbers[1] - numbers[0];
			if (result > 2147483647 || result < -2147483648)
				throw(std::runtime_error("Error: overflow"));
			return (result);
		}
	}
	return (0);
}

void	parseNumber( std::string str ) {
	std::istringstream	iss(str);
	std::stack<double>	s;
	std::string 		value;

	while (getline(iss, value, ' '))
	{
		if (value == "+" || value == "-" || value == "*" || value == "/")
			s.push(calculate(s, value[0]));
		else
		{
			for (int i = 0; value[i]; i++)
			{
				if (!isdigit(value[i]))
					throw(std::runtime_error("Error: non numeric character"));
			s.push(std::strtol(value.c_str(), NULL, 10));
			if (s.top() > 9)
				throw(std::runtime_error("Error: number should not be supperior to 9"));
			}
		}
	}
	if (s.size() > 1)
		throw(std::runtime_error("Error"));
	std::cout << s.top() << std::endl;
}