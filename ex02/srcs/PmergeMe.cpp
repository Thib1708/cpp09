/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 09:21:48 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/09/28 09:46:55 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	print_vec( std::vector<int> vec ) {
	std::vector<int>::iterator 	it;
	int							i = 0;
	
	for (it = vec.begin(); it != vec.end(); it++)
	{
		if (i++ > 4)
			break ;
		std::cout << *it << " ";
	}
	if (it != vec.end())
		std::cout << "[...]";
	std::cout << std::endl;
}

std::vector<int>	insertionSort_vec( std::vector<int> vec) {
	int key;
	int j;
	for (size_t i = 1; i < vec.size(); i++)
	{
		key = vec[i];
		j = i - 1;
		while (j >= 0 && vec[j] > key)
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = key;
	}
	return vec;
}

std::deque<int>	insertionSort_deq( std::deque<int> deq) {
	int key;
	int j;
	for (size_t i = 1; i < deq.size(); i++)
	{
		key = deq[i];
		j = i - 1;
		while (j >= 0 && deq[j] > key)
		{
			deq[j + 1] = deq[j];
			j--;
		}
		deq[j + 1] = key;
	}
	return deq;
}

void	print_deq( std::deque<int> deq ) {
	std::deque<int>::iterator 	it;
	int							i = 0;
	for (it = deq.begin(); it != deq.end(); it++)
	{
		if (i++ > 4)
			break ;
		std::cout << *it << " ";
	}
	if (it != deq.end())
		std::cout << "[...]";
	std::cout << std::endl;
}

bool    PmergeMe( char ** argv ) {
	std::vector<int>    vec;
	std::vector<int>	sorted_vec;
	std::deque<int>   	deq;
	std::deque<int>		sorted_deq;
	std::string         str;
	long                number;
	clock_t 			start_vec, end_vec;
	clock_t 			start_deq, end_deq;

	for (int j = 1; argv[j]; j++)
	{
		for (int i = 0; argv[j][i]; i++)
		{
			if (!std::isdigit(argv[j][i]))
			{
				if (argv[j][i] == '-')
					return (std::cout << "Error: negative integer" << std::endl, false);
				return (std::cout << "Error: non digit character" << std::endl, false);
			}
		}
		number = std::strtol(argv[j], NULL, 10);
		str = argv[j];
		if (number > 2147483647 || str.size() > 10)
			return (std::cout << "Error: overflow" << std::endl, false);
		vec.push_back(number);
		deq.push_back(number);
	}
	std::cout << "Before:  ";
	print_vec(vec);
	
    start_vec = clock();
	sorted_vec = insertionSort_vec(vec);
	end_vec = clock();
    long micro_vec = ((double)end_vec - (double)start_vec) / CLOCKS_PER_SEC * 1000000;
	std::cout << "After:   ";
	print_vec(sorted_vec);
	
    start_deq = clock();
	sorted_deq = insertionSort_deq(deq);
	end_deq = clock();
    long micro_deq = ((double)end_deq - (double)start_deq) / CLOCKS_PER_SEC * 1000000;
	
	
	std::cout << "Time to process a range of   " << vec.size()
	<< " elements with std::vector : " << micro_vec << "µs" << std::endl;
	std::cout << "Time to process a range of   " << deq.size()
	<< " elements with std::deque  : " << micro_deq << "µs" << std::endl;
	return (true);
}