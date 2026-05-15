#include <iostream>
#include <omp.h>

using namespace std;

// ================= MERGE FUNCTION =================
void merge(int a[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;

    int temp[100];

    while(i <= mid && j <= right)
    {
        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= mid)
        temp[k++] = a[i++];

    while(j <= right)
        temp[k++] = a[j++];

    for(i = left, k = 0; i <= right; i++, k++)
        a[i] = temp[k];
}

// ================= PARALLEL MERGE SORT =================
void mergeSort(int a[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(a, left, mid);

            #pragma omp section
            mergeSort(a, mid + 1, right);
        }

        merge(a, left, mid, right);
    }
}

// ================= PARALLEL BUBBLE SORT =================
void bubbleSort(int a[], int n)
{
    for(int i = 0; i < n; i++)
    {
        #pragma omp parallel for
        for(int j = 0; j < n - 1; j++)
        {
            if(a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
        }
    }
}

// ================= MAIN FUNCTION =================
int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int a[100], b[100];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }

    // Bubble Sort
    bubbleSort(a, n);

    cout << "\nParallel Bubble Sort:\n";

    for(int i = 0; i < n; i++)
        cout << a[i] << " ";

    // Merge Sort
    mergeSort(b, 0, n - 1);

    cout << "\n\nParallel Merge Sort:\n";

    for(int i = 0; i < n; i++)
        cout << b[i] << " ";

    return 0;
}
