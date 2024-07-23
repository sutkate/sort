#include "sort_class.hpp"
using namespace std;
Array::Array(const size_t _size, int _range, string _data_filename, string _result_filename) : 
	size(_size), 
	range(_range), 
	data_filename(_data_filename), 
	result_filename(_result_filename)
{
	arr = new int[size];
	fout.open(result_filename, fstream::out);
	random();
}
void Array::start()
{
	//bubble_sort
	_DURATION t1 = bubble_sort(); random();
	_DURATION t2 = bubble_sort(); random();
	_DURATION t3 = bubble_sort(); random();

	print(t1, t2, t3, "BUBBLE SORT");
	
	t1 = merge_sort(0, size - 1); random();
	t2 = merge_sort(0, size - 1); random();
	t3 = merge_sort(0, size - 1); random();

	print(t1, t2, t3, "MERGE SORT");

	t1 = count_sort(); random();
	t2 = count_sort(); random();
	t3 = count_sort(); random();
	
	print(t1, t2, t3, "COUNT SORT");

	t1 = insertion_sort(); random();
	t2 = insertion_sort(); random();
	t3 = insertion_sort(); random();

	print(t1, t2, t3, "INSERTION SORT");

	t1 = selection_sort(); random();
	t2 = selection_sort(); random();
	t3 = selection_sort(); random();

	print(t1, t2, t3, "SELECTION SORT");

	t1 = tim_sort(); random();
	t2 = tim_sort(); random();
	t3 = tim_sort(); random();

	print(t1, t2, t3, "TIMSORT SORT");

	t1 = radix_sort(); random();
	t2 = radix_sort(); random();
	t3 = radix_sort(); random();

	print(t1, t2, t3, "RADIX SORT");

	t1 = bucket_sort(); random();
	t2 = bucket_sort(); random();
	t3 = bucket_sort(); random();

	print(t1, t2, t3, "BUCKET SORT");

	t1 = quick_sort(0, size); random();
	t2 = quick_sort(0, size); random();
	t3 = quick_sort(0, size); random();

	print(t1, t2, t3, "QUICK SORT");
}
void Array::random()
{
	srand(time(nullptr));
	for (int i = 0; i < size; i++)
		arr[i] = rand() % range;
	write();
}
void Array::write()
{
	fstream fs(data_filename);
	fs.open(data_filename, fstream::out);
	if (fs.is_open()) // проверяем, что файл успешно открыт
	{
		fs << size << '\n';  // записываем размер массива
		for (int i = 0; i < size; i++) fs << arr[i] << ' '; // записываем значения через пробел
		
		fs << '\n';

		fs.close(); // закрываем файл
	}
}
void Array::swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int Array::partition(int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}

	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

int Array::get_max()
{
	int max = arr[0];
	for (int i = 1; i < size; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}
int Array::get_exp(int value)
{
	int exp = 1;
	while (value > 10)
	{
		value /= 10;
		exp *= 10;
	}
	return exp;
}
void Array::count_sort_arr(int* arr, size_t n)
{
	if (!n)
		return;

	int max = arr[0];
	for (int i = 1; i < size; i++)
		if (arr[i] > max)
			max = arr[i];

	int* output = new int[n];
	int* count = new int[max + 1];

	for (int i = 0; i < max + 1; i++)
		count[i] = 0;

	for (int i = 0; i < n; i++)
		count[arr[i]]++;

	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];

	delete[] output;
	delete[] count;
}
void Array::count_sort_radix(int* arr, size_t n, int exp)
{
	int* output = new int[n];
	int count[10] = { 0 };

	for (int i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];

	delete[] output;
}
void Array::insertion_sort_tim_sort(int* arr, int l, int r)
{
	for (int i = l + 1; i <= r; i++)
	{
		int key = arr[i];
		int j = i - 1;

		while (j >= l && arr[j] > key)
			arr[j + 1] = arr[j--];

		arr[j + 1] = key;
	}
}
void Array::merge(int* arr, int l, int m, int r)
{
	int nl = m - l + 1;
	int nr = r - m;

	int* left = new int[nl];
	int* right = new int[nr];

	for (int i = 0; i < nl; i++)
		left[i] = arr[l + i];
	for (int j = 0; j < nr; j++)
		right[j] = arr[m + 1 + j];

	int i = 0, j = 0;
	int k = l;

	while (i < nl && j < nr)
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];

	while (i < nl)
		arr[k++] = left[i++];

	while (j < nr)
		arr[k++] = right[j++];

	delete[] left;
	delete[] right;
}
void Array::merge_sort(int* arr, int l, int r)
{
	if (l >= r)
		return;

	int m = (l + r - 1) / 2;

	merge_sort(arr, l, m);
	merge_sort(arr, m + 1, r);
	merge(arr, l, m, r);
}

_DURATION Array::bubble_sort()
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
_DURATION Array::merge_sort(int l, int r)
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	int m = (l + r - 1) / 2;

	merge_sort(arr, l, m);
	merge_sort(arr, m + 1, r);
	merge(arr, l, m, r);
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
_DURATION Array::count_sort()
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	int max = get_max();
	int* output = new int[size];
	int* count = new int[max + 1];

	for (int i = 0; i < max + 1; i++)
		count[i] = 0;

	for (int i = 0; i < size; i++)
		count[arr[i]]++;

	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];

	for (int i = size - 1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}

	for (int i = 0; i < size; i++)
		arr[i] = output[i];

	delete[] output;
	delete[] count;
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
_DURATION Array::insertion_sort()
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	for (int i = 1; i < size; i++)
	{
		int key = arr[i];
		int j = i - 1;

		for (; j >= 0; j--)
			if (arr[j] > key)
				arr[j + 1] = arr[j];
			else
				break;

		arr[j + 1] = key;
	}
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;;
}
_DURATION Array::selection_sort()
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i; j < size; j++)
			if (arr[j] < arr[min])
				min = j;

		swap(&arr[i], &arr[min]);
	}
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
_DURATION Array::tim_sort()
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	const int RUN = 64;

	for (int i = 0; i < size; i += RUN)
		if ((size - RUN) > i)
			insertion_sort_tim_sort(arr, i, i + RUN - 1);
		else
			insertion_sort_tim_sort(arr, i, size - 1);

	for (int run = RUN; run < size; run = 2 * run)
		for (int left = 0; left < size; left += 2 * run)
		{
			int mid = left + run - 1;
			int right = min((left + 2 * run - 1), (size - 1));

			if (mid > right)
				mid = left;

			merge(arr, left, mid, right);
		}
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
_DURATION Array::radix_sort()
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	int m = get_max();
	int exp = 1;

	while (m > 10)
	{
		m /= 10;
		count_sort_radix(arr, size, exp);
		exp *= 10;
	}
	count_sort_radix(arr, size, exp);

	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
_DURATION Array::bucket_sort()
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	struct bucket buckets[11];
	int exp = get_exp(get_max());

	for (int i = 0; i < 11; i++)
	{
		buckets[i].count = 0;
		buckets[i].data = new int[size];
	}

	for (int i = 0; i < size; i++)
	{
		int bi = arr[i] / exp;
		buckets[bi].data[buckets[bi].count++] = arr[i];
	}

	int l = 0;
	for (int i = 0; i < 11; i++)
	{
		count_sort_arr(buckets[i].data, buckets[i].count);
		for (int j = 0; j < buckets[i].count; j++)
			arr[l++] = buckets[i].data[j];
	}

	for (int i = 0; i < 11; i++)
		delete[] buckets[i].data;
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
_DURATION Array::quick_sort(int low, int high)
{
	auto start = std::chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////
	if (low < high)
	{
		int pi = partition(low, high);

		quick_sort(low, pi - 1);
		quick_sort(pi + 1, high);
	}
	///////////////////////////////////////////////////////
	auto finish = std::chrono::high_resolution_clock::now();
	_DURATION duration = finish - start;
	return duration;
}
void Array::print(_DURATION t1, _DURATION t2, _DURATION t3, string text)
{
	cout << "\n\t" << text << endl << endl;
	cout << "time1 =        " << t1.count() << endl;
	cout << "time2 =        " << t2.count() << endl;
	cout << "time3 =        " << t3.count() << endl;
	cout << "average time = " << (t1.count() + t2.count() + t3.count()) / 3 << endl;

	cout << "\n\n\tTEST ENDED\n\n";
	if (fout.is_open())
		cout << "TEXT WRITTEN IN " << result_filename << "\n\n========================================";
	else
		cout << "TEXT DIDNT WRITTENn\n========================================";
	
	fout << "\n\t\t" << text << endl << endl;
	fout << "time1 =        " << t1.count() << endl;
	fout << "time2 =        " << t2.count() << endl;
	fout << "time3 =        " << t3.count() << endl;
	fout << "average time = " << (t1.count() + t2.count() + t3.count()) / 3 << endl;
	fout << "\n========================================";

}

