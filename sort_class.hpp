#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#define _DURATION chrono::duration <double> 
using namespace std;
class Array
{
private:
	int* arr;
	size_t size;
	unsigned int range;
	string result_filename;
	string data_filename;
	fstream fout;
	
	struct bucket { int count; int* data; };
	const int min(const int a, const int b) { return (b < a) ? b : a; }
	void random();
	void write();
	void swap(int* a, int* b);
	int partition(int low, int high);
	int get_max();
	int get_exp(int value);


	void count_sort_arr(int* arr, size_t n);
	void count_sort_radix(int* arr, size_t n, int exp);
	void insertion_sort_tim_sort(int* arr, int l, int r);
	void merge(int* arr, int l, int m, int r);
	void merge_sort(int* arr, int l, int r);
	_DURATION bubble_sort();
	_DURATION merge_sort(int l, int r);
	_DURATION count_sort();
	_DURATION insertion_sort();
	_DURATION selection_sort();
	_DURATION tim_sort();
	_DURATION radix_sort();
	_DURATION bucket_sort();
	_DURATION quick_sort(int low, int high);

	void print(
		_DURATION t1,
		_DURATION t2,
		_DURATION t3,
		string text
	);
public:
	Array(const size_t _size = 0, 
		  int _range = 1, 
		  string _data_filename = "data.txt",
		  string _result_filename = "result.txt"
	);
	~Array() { delete[] arr; }
	
	void start();
};