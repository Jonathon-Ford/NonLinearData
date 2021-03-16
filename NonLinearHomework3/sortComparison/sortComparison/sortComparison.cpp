/*
Jonathon Ford
Proffesor: Dr Xu
Nonlinear Data Structures

This program will will compare the speed of diferent sorts and display how long each took
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

vector<int> randomVector(int size) {
    vector<int> random;

    for (int i = 0; i < size; i++) {
        int randomNum = rand() % 1000;
        random.push_back(randomNum);
    }
    return random;
}

void insertionSort(vector<int>& numbers) {

    auto start = chrono::system_clock::now();

    for (int i = 1; i < numbers.size(); ++i) {
        int j = i;
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }

    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Time taken for insertion Sort:" << elapsed_seconds.count() << endl;
}

void bucketSort(std::vector<int>& numbers, int numBuckets) {

    auto start = chrono::system_clock::now();

    if (numbers.size() < 1) {
        return;
    }

    vector<vector<int>> buckets(numBuckets);

   int maxValue = numbers[0];
   for (int i = 1; i < numbers.size(); i++) {
       if (numbers[i] > maxValue) {
           maxValue = numbers[i];
       }
   }

   for (int i = 0; i < numbers.size(); i++) {
       int index = floor((numbers[i] * numBuckets) / (maxValue + 1));
       buckets[index].push_back(numbers[i]);
   }

   for (int i = 0; i < buckets.size(); i++) {
       sort(buckets[i].begin(), buckets[i].end());
   }

   int index = 0;
   for (int i = 0; i < buckets.size(); i++) {
       for (int j = 0; j < buckets[i].size(); j++) {
           numbers[index] = buckets[i][j];
           index++;
       }
   }

   auto end = chrono::system_clock::now();

   chrono::duration<double> elapsed_seconds = end - start;
   cout << "Time taken for bucket Sort:" << elapsed_seconds.count() << endl;

}

void radixSort(std::vector<int>& numbers) {

    auto start = chrono::system_clock::now();

    vector<vector<int>> digitBuckets(10);

    int maxDigits = 0;

    //Find max number of digits by dividing by 10 adding 1 to the number of digits for each time dividing by ten
    for (int i = 0; i < numbers.size(); i++) {
        int test = numbers[i];
        int digitCount = 0;
        while (test != 0) {
            digitCount++;
            test /= 10;
            if (digitCount > maxDigits) {
                maxDigits = digitCount;
            }
        }
    }

    int pow10 = 1;

    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
        for (int i = 0; i < numbers.size(); i++) {
            int bucketIndex = abs(numbers[i] / pow10) % 10;
            digitBuckets[bucketIndex].push_back(numbers[i]);
        }
        int arrayIndex = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < digitBuckets[i].size(); j++) {
                numbers[arrayIndex++] = digitBuckets[i][j];
            }
        }
        pow10 *= 10;

        //Clear the buckets
        for (int i = 0; i < 10; i++) {
            digitBuckets[i].clear();
        }
    }

    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Time taken for radix Sort:" << elapsed_seconds.count() << endl;
}

int main()
{
    cout << "Test for N = 10" << endl;
    for (int i = 1; i <= 10; i++) {
        vector<int> test(randomVector(10));

        insertionSort(test);
        bucketSort(test, 10);
        radixSort(test);
        cout << endl;
    }

    cout << "Test for N = 100" << endl;
    for (int i = 1; i <= 10; i++) {
        vector<int> test(randomVector(100));

        insertionSort(test);
        bucketSort(test, 10);
        radixSort(test);
        cout << endl;
    }

    cout << "Test for N = 1000" << endl;
    for (int i = 1; i <= 10; i++) {
        vector<int> test(randomVector(1000));

        insertionSort(test);
        bucketSort(test, 10);
        radixSort(test);
        cout << endl;
    }

    cout << "Test for N = 10000" << endl;
    for (int i = 1; i <= 10; i++) {
        vector<int> test(randomVector(10000));

        insertionSort(test);
        bucketSort(test, 10);
        radixSort(test);
        cout << endl;
    }
}