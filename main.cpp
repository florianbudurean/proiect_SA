#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////
void bubbleSort(int* a, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

/////////////////////////////////////////////////////////////
void insertionSort(int* a, int n)
{
    for (int i = 1; i < n; i++)
    {
        int k = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > k)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = k;
    }
}

/////////////////////////////////////////////////////////////
void countingStep(int* a, int n, int exp)
{
    int* out = new int[n];
    int c[10] = {0};

    for (int i = 0; i < n; i++)
        c[(a[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        c[i] += c[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        out[c[(a[i] / exp) % 10] - 1] = a[i];
        c[(a[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = out[i];

    delete[] out;
}

void radixSort(int* a, int n)
{
    int m = a[0];

    for (int i = 1; i < n; i++)
        if (a[i] > m)
            m = a[i];

    for (int exp = 1; m / exp > 0; exp *= 10)
        countingStep(a, n, exp);
}

/////////////////////////////////////////////////////////////
void merge(int* a, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];

    for (int i = 0; i < n2; i++)
        R[i] = a[m + i + 1];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int* a, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

/////////////////////////////////////////////////////////////
int partitionArray(int* a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(int* a, int low, int high)
{
    if (low < high)
    {
        int pi = partitionArray(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

/////////////////////////////////////////////////////////////
void mergeWrapper(int* a, int n)
{
    mergeSort(a, 0, n - 1);
}

void quickWrapper(int* a, int n)
{
    quickSort(a, 0, n - 1);
}

/////////////////////////////////////////////////////////////
double benchmark(void (*sortFunc)(int*, int), int* original, int n, int runs)
{
    using namespace std::chrono;

    double total = 0.0;

    for (int i = 0; i < runs; i++)
    {
        int* copy = new int[n];

        for (int j = 0; j < n; j++)
            copy[j] = original[j];

        auto start = high_resolution_clock::now();
        sortFunc(copy, n);
        auto stop = high_resolution_clock::now();

        duration<double> elapsed = stop - start;
        total += elapsed.count();

        delete[] copy;
    }

    return total / runs;
}

/////////////////////////////////////////////////////////////
void generateListToFile(const string& fileName, int n, int type)
{
    ofstream fout(fileName.c_str());

    fout << n << " ";

    if (type == 1) // sortata
    {
        int val = rand() % 10;
        for (int i = 0; i < n; i++)
        {
            fout << val << " ";
            val += rand() % 10;
        }
    }
    else if (type == 2) // nesortata
    {
        for (int i = 0; i < n; i++)
            fout << rand() << " ";
    }
    else if (type == 3) // plata
    {
        int val = rand() % 10;
        for (int i = 0; i < n; i++)
        {
            fout << val << " ";
            val += rand() % 2;
        }
    }

    fout.close();
}

int* readListFromFile(const string& fileName, int& n)
{
    ifstream fin(fileName.c_str());

    fin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        fin >> arr[i];

    fin.close();
    return arr;
}

/////////////////////////////////////////////////////////////
int main()
{
    srand((unsigned)time(0));

    const string inputFile = "in.txt";

    while (true)
    {
        int opt;
        cout << "Selectati tipul de lista:\n";
        cout << "1. Sortata\n";
        cout << "2. Nesortata\n";
        cout << "3. Lista plata\n";
        cout << "4. Lista precedenta\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";
        cin >> opt;
        ///opt = 2;
        if (opt == 0)
            break;

        if (opt < 0 || opt > 4)
        {
            cout << "Alegeti o optiune valida.\n\n";
            continue;
        }

        if (opt != 4)
        {
            int l;
            cout << "Introduceti lungimea sirului: ";
            cin >> l;

            if (l <= 0)
            {
                cout << "Lungimea trebuie sa fie pozitiva.\n\n";
                continue;
            }

            generateListToFile(inputFile, l, opt);
        }

        int n;
        int* arr = readListFromFile(inputFile, n);

        int runs;
        cout << "De cate ori sa ruleze fiecare algoritm: ";
        cin >> runs;

        if (runs <= 0)
        {
            cout << "Numarul de rulari trebuie sa fie pozitiv.\n\n";
            delete[] arr;
            continue;
        }

        cout << "\nRezultate medii pentru n = " << n << ":\n";

        if (n < 10000)
            cout << "Bubble:    " << benchmark(bubbleSort, arr, n, runs) << " sec\n";
        else
            cout << "Bubble:    netestat, prea multe date\n";

        if (n <= 75000)
            cout << "Insertion: " << benchmark(insertionSort, arr, n, runs) << " sec\n";
        else
            cout << "Insertion: netestat, prea multe date\n";

        cout << "Merge:     " << benchmark(mergeWrapper, arr, n, runs) << " sec\n";
        if ((opt == 1 and n >= 100000) or (opt == 3 and n >= 100000)) cout << "Quick: netestat, anomalie!\n";
        else cout << "Quick:     " << benchmark(quickWrapper, arr, n, runs) << " sec\n";
        cout << "Radix:     " << benchmark(radixSort, arr, n, runs) << " sec\n";

        delete[] arr;
        cout << "\n";
        cout<<"Apasati Enter pentru a continua...";
        while(getchar() != '\n');
        getchar();
        system("cls");
    }

    return 0;
}
