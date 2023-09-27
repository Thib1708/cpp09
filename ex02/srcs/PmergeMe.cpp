/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 09:21:48 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/09/27 10:42:14 by tgiraudo         ###   ########.fr       */
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

bool    PmergeMe( char ** argv ) {
	std::vector<int>    vec;
	std::vector<int>	sorted_vec;
	std::string         str;
	long                number;
	struct timeval start, end;

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
	}
	std::cout << "Before:  ";
	print_vec(vec);
    gettimeofday(&start, 0);
	sorted_vec = recurseSort_vec(vec);
	gettimeofday(&end, 0);
    long micro = end.tv_usec - start.tv_usec;
	std::cout << "After:   ";
	print_vec(sorted_vec);
	std::cout << "Time to process a range of  " << vec.size() << " elements with std::vector : " << micro << "µs" << std::endl;
	return (true);
}