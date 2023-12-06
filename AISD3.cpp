#include <iostream>
#include <vector>
#include <random>
#define SIZE 1000

using namespace std;

struct stats
{
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

stats operator+(const stats& left, const stats& right)
{
    stats stats;
    stats.comparison_count = left.comparison_count + right.comparison_count;
    stats.copy_count = left.copy_count + right.copy_count;
    return stats;
}

vector<int> generate_sorted_vector(const int n)
{
    vector<int> result;
    for (int i = 0; i < n; ++i)
    {
        result.push_back(i);
    }
    return result;
}

vector<int> generate_inverted_vector(const int n)
{
    vector<int> result;
    for (int i = n - 1; i >= 0; --i)
    {
        result.push_back(i);
    }
    return result;
}

vector<int> generate_random_vector(const int n)
{
    vector<int> result;
    for (int i = 0; i < n; ++i)
    {
        result.push_back(rand() % n);
    }
    return result;
}

stats bubble_sort(std::vector<int>& arr)
{
    stats stats;

    size_t length = arr.size();
    for (size_t i = 0; i < length - 1; i++)
    {
        for (size_t j = 0; j < length - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j + 1], arr[j]);
                stats.copy_count += 1;
            }
            stats.comparison_count++;
        }
    }
    return stats;
}


stats shell_sort(std::vector<int>& arr)
{
    stats stats;
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int key = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > key; j -= gap)
            {
                arr[j] = arr[j - gap];
                stats.copy_count += 1;
                stats.comparison_count += 1;
            }

            arr[j] = key;
            stats.comparison_count += 1;
        }
    }

    return stats;
}

void heapify(std::vector<int>& arr, int size, int i, stats& stats)
{
    size_t largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[largest])
    {
        largest = left;
        stats.comparison_count++;
    }

    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
        stats.comparison_count++;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        stats.copy_count += 1;
        heapify(arr, size, largest, stats);
    }
}

stats heap_sort(std::vector<int>& arr)
{
    stats stats;
    int size = arr.size();

    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i, stats);

    for (int i = size - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        stats.copy_count += 1;
        heapify(arr, i, 0, stats);
    }

    return stats;
}

int main()
{
    vector<int> vector_testing1{ 0, 1, 553, 522, 4, 52, 8 };
    vector<int> vector_testing2{ 0, 1, 553, 522, 4, 52, 8 };
    vector<int> vector_testing3{ 0, 1, 553, 522, 4, 52, 8 };
    bubble_sort(vector_testing1);
    shell_sort(vector_testing2);
    heap_sort(vector_testing3);
    for (int i = 0; i < vector_testing1.size(); ++i) {
        cout << vector_testing1[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < vector_testing2.size(); ++i) {
        cout << vector_testing2[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < vector_testing3.size(); ++i) {
        cout << vector_testing3[i] << " ";
    }
    cout << "\n";

    vector<int> vector;
    cout << "------SORTED ARRAY------" << endl;

    size_t sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_sorted_vector(SIZE);
        stats tmp;
        tmp = bubble_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Bubble sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        srand(i);
        vector = generate_sorted_vector(SIZE);
        stats tmp = shell_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Shell sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        srand(i);
        vector = generate_sorted_vector(SIZE);
        stats tmp = heap_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Heap sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;


    cout << "------INVERTED ARRAY------" << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_inverted_vector(SIZE);
        stats tmp = bubble_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Bubble\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_inverted_vector(SIZE);
        stats tmp = shell_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Shell sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_inverted_vector(SIZE);
        stats tmp = heap_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Heap sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;


    cout << "------RANDOM ARRAY------" << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_random_vector(SIZE);
        stats tmp = bubble_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Bubble\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_random_vector(SIZE);
        stats tmp = shell_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Shell sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_random_vector(SIZE);
        stats tmp = heap_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Heap sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    return 0;
}
