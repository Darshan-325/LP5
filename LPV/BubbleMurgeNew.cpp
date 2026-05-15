#include <iostream>
#include <omp.h>

using namespace std;

// ======================================================
// PARALLEL BUBBLE SORT
// ======================================================
void parallelBubbleSort(int a[], int n)
{
    for(int i = 0; i < n; i++)
    {
        // Even phase
        #pragma omp parallel for
        for(int j = 0; j < n - 1; j += 2)
        {
            if(a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }

        // Odd phase
        #pragma omp parallel for
        for(int j = 1; j < n - 1; j += 2)
        {
            if(a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// ======================================================
// MERGE FUNCTION
// ======================================================
void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for(int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}

// ======================================================
// PARALLEL MERGE SORT
// ======================================================
void parallelMergeSort(int a[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(a, left, mid);

            #pragma omp section
            parallelMergeSort(a, mid + 1, right);
        }

        merge(a, left, mid, right);
    }
}

// ======================================================
// PRINT ARRAY
// ======================================================
void printArray(int a[], int n)
{
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}

// ======================================================
// MAIN FUNCTION
// ======================================================
int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int a[n], b[n];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }

    // ================= BUBBLE SORT =================
    parallelBubbleSort(a, n);

    cout << "\nParallel Bubble Sort:\n";
    printArray(a, n);

    // ================= MERGE SORT =================
    parallelMergeSort(b, 0, n - 1);

    cout << "\nParallel Merge Sort:\n";
    printArray(b, n);

    return 0;
}
