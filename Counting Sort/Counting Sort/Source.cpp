#include <iostream>
#include <vector>

const int AMOUNT = 1000;

void count_sort(std::vector<int>::iterator first, std::vector<int>::iterator last);
void print_vector(std::vector<int>::iterator first, std::vector<int>::iterator last);
void get_random_numbers(std::vector<int>&);

int main()
{
	srand(time(NULL));

	std::vector<int> vector_to_be_sorted;
	get_random_numbers(vector_to_be_sorted);

	count_sort(vector_to_be_sorted.begin(), vector_to_be_sorted.end());

	return 0;
}

void count_sort(std::vector<int>::iterator first, std::vector<int>::iterator last)
{

}

void get_random_numbers(std::vector<int>& vec)
{
	for (int i = 0; i < AMOUNT; i++)
	{
		int random_number = rand();
		vec.push_back(random_number);
	}
}

void print_vector(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	for (auto itr = first; itr != last; itr++)
	{
		std::cout << *itr << std::endl;
	}
}