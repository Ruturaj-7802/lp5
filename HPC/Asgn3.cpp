#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <omp.h>
#include <time.h>
using namespace std;

template <typename T>
T parallelMin(const vector<T> &arr){
    T result = arr[0];
#pragma omp parallel for reduction(min : result)
    for (int i = 0; i<arr.size(); i++){
        result = min(result, arr[i]);
    }
    return result;
}

template <typename T>
T parallelMax(const vector<T> &arr){
    T result = arr[0];
#pragma omp parallel for reduction(max : result)
    for(int i = 0; i<arr.size(); i++){
        result = max(result, arr[i]);
    }
    return result;
}

template <typename T>
T parallelSum(const vector<T> &arr){
    T result = arr[0];
#pragma omp parallel for reduction(+ : result)
    for(int i = 0; i<arr.size(); i++){
        result += arr[i];
    }
    return result;
}

template <typename T>
T parallelAverage(const vector<T> &arr){
    T sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}

int main(){
    const int size = 10;
    vector<int> arr(size);
    srand(time(0));
    for(int i=0; i<size; i++){
        arr[i] = rand()%10000;
        cout << arr[i] << " ";
    }
    cout << endl;

    int minVal = parallelMin(arr);
    int maxVal = parallelMax(arr);
    int sum = parallelSum(arr);
    double average = parallelAverage(arr);

    cout << minVal << " " << maxVal << " " << sum << " ";
    cout << fixed << setprecision(2) << average << endl;
    return 0;
}
