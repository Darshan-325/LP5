#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int a[n];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
        cin >> a[i];

    int sum = 0, min = a[0], max = a[0];

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
        sum += a[i];

    #pragma omp parallel for reduction(min:min)
    for(int i = 0; i < n; i++)
        if(a[i] < min)
            min = a[i];

    #pragma omp parallel for reduction(max:max)
    for(int i = 0; i < n; i++)
        if(a[i] > max)
            max = a[i];

    float avg = (float)sum / n;

    cout << "\nSum = " << sum;
    cout << "\nMinimum = " << min;
    cout << "\nMaximum = " << max;
    cout << "\nAverage = " << avg;

    return 0;
}

