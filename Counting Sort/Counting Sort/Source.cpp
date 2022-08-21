#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <numeric>

const int REPETITIONS = 10;
const int SAMPLES = 100;

double time_it(std::vector<int>*);
double average_value(const std::vector<double> data);
double std_dev(std::vector<double> data);
void counting_sort(std::vector<int>* arr);
void display_array(std::vector<int>::iterator, std::vector<int>::iterator);

int main()
{
	const int DATA_SIZE = 500000;

	srand(time(NULL));
	std::vector<int>* arr = new std::vector<int>();
	std::vector<double> period(SAMPLES);

	for (int i = 0; i < (DATA_SIZE * REPETITIONS); i++)
	{
		int number = rand() % (DATA_SIZE * REPETITIONS);
		arr->push_back(number);
	}

	std::ofstream os;
	os.open("counting_sort.data", std::ios::out | std::ios::app);
	os << "N\t" << "T[ms]\t" << "dev[ms]\t" << "Samples\n";

	for (int iter = 1; iter <= REPETITIONS; iter++)
	{
		for (int i = 0; i < SAMPLES; i++)
		{
			// run it
			period[i] = time_it(arr);
		}
		os << DATA_SIZE * iter << "\t" << average_value(period) << "\t" << std_dev(period) << "\t" << SAMPLES << '\n';
	}
	os.close();

	display_array(arr->begin(), arr->end());

	return 0;
}

void counting_sort(std::vector<int>* arr)
{
	std::vector<int> output(arr->size() + 1);
	int max = *(std::max_element(arr->begin(), arr->end()));
	std::vector<int> count(max + 1);

	for (int i = 0; i <= max; ++i)
	{
		count[i] = 0;
	}

	for (int i = 0; i < arr->size(); i++)
	{
		count[arr->at(i)]++;
	}

	for (int i = 1; i <= max; i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = arr->size() - 1; i >= 0; i--)
	{
		output[count[arr->at(i)] - 1] = arr->at(i);
		count[arr->at(i)]--;
	}

	for (int i = 0; i < arr->size(); i++)
	{
		arr->at(i) = output[i];
	}
}

void display_array(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	for (auto itr = first; itr != last; itr++)
	{
		std::cout << *itr << '\n';
	}
}

double time_it(std::vector<int>* arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	counting_sort(arr);
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> total = (stop - start);
	return total.count();
}

double average_value(const std::vector<double> data)
{
	double sum = std::accumulate(data.begin(),
		data.end(),
		0.0);
	const size_t N = data.size();
	double avg = sum / N;

	return avg;
}

double std_dev(std::vector<double> data)
{
	const size_t N = data.size();
	double avg_val = average_value(data);
	double dev_square = 0;

	for (std::vector<double>::iterator itr = data.begin(); itr != data.end(); itr++) {
		dev_square += pow((*itr - avg_val), 2);
	}

	return std::sqrt(dev_square * (1.0 / (N - 1)));
}