/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 09:21:48 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/09/27 12:29:21 by tgiraudo         ###   ########.fr       */
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

std::vector<int> merge_vec( std::vector<int> a, std::vector<int> b) {
	std::vector<int> 	merged_vec;

	while (a.size() && b.size())
	{
		if (a[0] < b[0])
		{
			merged_vec.push_back(a[0]);
			a.erase(a.begin());
		}
		else
		{
			merged_vec.push_back(b[0]);
			b.erase(b.begin());
		}
	}
	while (a.size())
	{
		merged_vec.push_back(a[0]);
		a.erase(a.begin());
	}
	while (b.size())
	{
		merged_vec.push_back(b[0]);
		b.erase(b.begin());
	}
	return (merged_vec);
}

std::vector<int> recurseSort_vec( std::vector<int> vec ) {
	std::vector<int> a;
	std::vector<int> b;

	if (vec.size() == 1)
		return vec;
	for (size_t i = 0; i < vec.size() / 2; i++)
		a.push_back(vec[i]);
	for (size_t i = vec.size() / 2; i < vec.size(); i++)
		b.push_back(vec[i]);
	a = recurseSort_vec(a);
	b = recurseSort_vec(b);
	return (merge_vec(a, b));
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

std::deque<int> merge_deq( std::deque<int> a, std::deque<int> b) {
	std::deque<int> 	merged_deq;

	while (a.size() && b.size())
	{
		if (a[0] < b[0])
		{
			merged_deq.push_back(a[0]);
			a.erase(a.begin());
		}
		else
		{
			merged_deq.push_back(b[0]);
			b.erase(b.begin());
		}
	}
	while (a.size())
	{
		merged_deq.push_back(a[0]);
		a.erase(a.begin());
	}
	while (b.size())
	{
		merged_deq.push_back(b[0]);
		b.erase(b.begin());
	}
	return (merged_deq);
}

std::deque<int> recurseSort_deq( std::deque<int> deq ) {
	std::deque<int> a;
	std::deque<int> b;

	if (deq.size() == 1)
		return deq;
	for (size_t i = 0; i < deq.size() / 2; i++)
		a.push_back(deq[i]);
	for (size_t i = deq.size() / 2; i < deq.size(); i++)
		b.push_back(deq[i]);
	a = recurseSort_deq(a);
	b = recurseSort_deq(b);
	return (merge_deq(a, b));
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
	sorted_vec = recurseSort_vec(vec);
	end_vec = clock();
    long micro_vec = ((double)end_vec - (double)start_vec) / CLOCKS_PER_SEC * 1000000;
	
    start_deq = clock();
	sorted_deq = recurseSort_deq(deq);
	end_deq = clock();
    long micro_deq = ((double)end_deq - (double)start_deq) / CLOCKS_PER_SEC * 1000000;
	
	std::cout << "After:   ";
	print_vec(sorted_vec);
	
	std::cout << "Time to process a range of   " << vec.size()
	<< " elements with std::vector : " << micro_vec << "µs" << std::endl;
	std::cout << "Time to process a range of   " << deq.size()
	<< " elements with std::deque  : " << micro_deq << "µs" << std::endl;
	return (true);
}