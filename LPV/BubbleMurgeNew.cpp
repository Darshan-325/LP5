{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <omp.h>\
\
using namespace std;\
\
// ================= MERGE FUNCTION =================\
void merge(int a[], int left, int mid, int right)\
\{\
    int n1 = mid - left + 1;\
    int n2 = right - mid;\
\
    int L[n1], R[n2];\
\
    // Copy data\
    for(int i = 0; i < n1; i++)\
        L[i] = a[left + i];\
\
    for(int j = 0; j < n2; j++)\
        R[j] = a[mid + 1 + j];\
\
    int i = 0;\
    int j = 0;\
    int k = left;\
\
    // Merge arrays\
    while(i < n1 && j < n2)\
    \{\
        if(L[i] <= R[j])\
        \{\
            a[k] = L[i];\
            i++;\
        \}\
        else\
        \{\
            a[k] = R[j];\
            j++;\
        \}\
        k++;\
    \}\
\
    // Remaining elements\
    while(i < n1)\
    \{\
        a[k] = L[i];\
        i++;\
        k++;\
    \}\
\
    while(j < n2)\
    \{\
        a[k] = R[j];\
        j++;\
        k++;\
    \}\
\}\
\
// ================= PARALLEL MERGE SORT =================\
void mergeSort(int a[], int left, int right)\
\{\
    if(left < right)\
    \{\
        int mid = (left + right) / 2;\
\
        // Parallel sections\
        #pragma omp parallel sections\
        \{\
            #pragma omp section\
            mergeSort(a, left, mid);\
\
            #pragma omp section\
            mergeSort(a, mid + 1, right);\
        \}\
\
        merge(a, left, mid, right);\
    \}\
\}\
\
// ================= MAIN FUNCTION =================\
int main()\
\{\
    int n;\
\
    cout << "Enter number of elements: ";\
    cin >> n;\
\
    int a[n];\
\
    cout << "Enter elements:\\n";\
\
    for(int i = 0; i < n; i++)\
        cin >> a[i];\
\
    mergeSort(a, 0, n - 1);\
\
    cout << "Sorted array:\\n";\
\
    for(int i = 0; i < n; i++)\
        cout << a[i] << " ";\
\
    return 0;\
\}}