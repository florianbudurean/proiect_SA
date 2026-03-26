#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

/////////////////////////////////////////////////////////////
void bubbleSort(int* a, int n)
{
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-i-1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp=a[j];
                a[j]=a[j + 1];
                a[j + 1]=temp;
            }
        }
    }
}

//////////////////////////////////////////////
void insertionSort(int* a, int n)
{
    for (int i=1; i<n; i++)
    {
        int k= a[i];
        int j= i - 1;
        while (j>=0 and a[j]>k)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=k;
    }
}

//////////////////////////////////////////////////////////////
void countingStep(int* a, int n, int exp)
{
    int* out=new int[n];
    int c[10]={0};

    for (int i=0; i < n; i++)
        c[(a[i]/exp) % 10]++;

    for (int i=1; i < 10; i++)
        c[i] += c[i - 1];

    for (int i=n - 1; i >= 0; i--)
    {
        out[c[(a[i] / exp) % 10] - 1]=a[i];
        c[(a[i] / exp) % 10]--;
    }

    for (int i=0; i < n; i++)
        a[i]=out[i];

    delete[] out;
}

void radixSort(int* a, int n)
{
    int m=a[0];
    for (int i=1; i < n; i++)
        if (a[i] > m) m=a[i];

    for (int exp=1; m / exp > 0; exp *= 10)
        countingStep(a, n, exp);
}

//////////////////////////////////////////////////////////////
void merge(int* a, int l, int m, int r)
{
    int n1=m-l+1;
    int n2=r-m;

    int* L=new int[n1];
    int* R=new int[n2];

    for (int i=0; i<n1; i++) L[i]=a[l+i];
    for (int i=0; i<n2; i++) R[i]=a[m+i+1];

    int i=0, j=0, k=l;

    while (i<n1 and j<n2)
    {
        if (L[i] <= R[j]) a[k++]=L[i++];
        else a[k++]=R[j++];
    }

    while (i<n1) a[k++]=L[i++];
    while (j<n2) a[k++]=R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int* a, int l, int r)
{
    if (l<r)
    {
        int m=(l+r)/2;
        mergeSort(a, l, m);
        mergeSort(a, m+1, r);
        merge(a, l, m, r);
    }
}

//////////////////////////////////////////////////////////////
int partition(int* a, int low, int high)
{
    int pivot=a[high];
    int i=low-1;

    for (int j=low; j<high; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }

    int temp=a[i + 1];
    a[i+1]=a[high];
    a[high]=temp;

    return i + 1;
}

void quickSort(int* a, int low, int high)
{
    if (low<high)
    {
        int pi=partition(a, low, high);
        quickSort(a,low,pi-1);
        quickSort(a,pi+1,high);
    }
}

//////////////////////////////////////////////////////////////
int main()
{
    srand(time(0));

    int opt;
    inceput:
    cout<<"Bun venit la programul de sortare al matusii Glaia!"<<endl;
    cout<<"Selectati tipul de lista de generat:"<<endl;
    cout<<"1. Sortata"<<endl;
    cout<<"2. Nesortata"<<endl;
    cout<<"3. Lista plata"<<endl;
    cout<<"4. Utilizeaza lista precedenta"<<endl;

    cin>>opt;
    switch (opt)
    {
    case 1: ///lista sortata
    {
        int l;

        cout<<"Introduceti lungimea sirului de generat: ";
        cin>>l;

        ofstream g_out("in.txt");
        g_out<<l<<" ";
        int pas=rand()%100;
        while (pas==0) pas=rand()%10; ///in caz ca se genereaza prima oara 0
        for (int i=0 ; i < l; i++, pas+= rand()%10 )
        {
            g_out<<pas;
            if (i < l - 1) g_out<<" ";
        }
        g_out.close();

        break;
    }
    case 2: ///lista nesortata
    {
        int l;

        cout<<"Introduceti lungimea sirului de generat: ";
        cin>>l;

        ofstream g_out("in.txt");
        g_out<<l<<" ";
        for (int i=0; i < l; i++)
        {

            int r=rand();
            g_out<<r;
            if (i < l - 1) g_out<<" ";
        }
        g_out.close();

        break;
    }
    case 3: ///lista plata
    {
        int l;

        cout<<"Introduceti lungimea sirului de generat: ";
        cin>>l;

        ofstream g_out("in.txt");
        g_out<<l<<" ";
        int pas=rand()%10;
        while (pas==0) pas=rand()%10; ///in caz ca se genereaza prima oara 0
        for (int i=0 ; i < l; i++, pas+= rand()%2 )
        {
            g_out<<pas;
            if (i < l - 1) g_out<<" ";
        }
        g_out.close();

        break;
        break;
    }

    case 4:
        {
            break;
        }
    default:
    {
        cout<<"Nu ati ales o optiune valida!";
        return 1;
    }

    }



    ifstream fin("in.txt");
    if (!fin.is_open())
    {
        cout<<"Eroare: in.txt nu a fost gasit."<<endl;
        return 1;
    }

    int n;
    fin>>n;

    int* arr=new int[n];
    for (int i=0; i < n; i++)
        fin>>arr[i];
    fin.close();

    cout<<"Selectati algoritmul de sortare:"<<endl;
    cout<<"1. Bubble Sort"<<endl;
    cout<<"2. Insertion Sort"<<endl;
    cout<<"3. Radix Sort"<<endl;
    cout<<"4. Merge Sort"<<endl;
    cout<<"5. Quick Sort"<<endl;
    cout<<"Optiunea: ";


    cin>>opt;

    if (opt < 1 or opt > 7)
    {
        cout<<"Optiune invalida."<<endl;
        delete[] arr;
        return 1;
    }

    switch (opt)
    {

    case 1:
    {
        clock_t start=clock();
        bubbleSort(arr, n);
        clock_t stop=clock();
        cout<<"Timpul utilizat pentru sortare: "<<(int)(stop-start)<<endl;
        break;
    }
    case 2:
    {
        clock_t start=clock();
        insertionSort(arr, n);
        clock_t stop=clock();
        cout<<"Timpul utilizat pentru sortare: "<<(int)(stop-start)<<endl;
        break;
    }
    case 3:
    {
        clock_t start=clock();
        radixSort(arr, n);
        clock_t stop=clock();
        cout<<"Timpul utilizat pentru sortare: "<<(int)(stop-start)<<endl;
        break;
    }
    case 4:
    {
        clock_t start=clock();
        mergeSort(arr, 0, n - 1);
        clock_t stop=clock();
        cout<<"Timpul utilizat pentru sortare: "<<(int)(stop-start)<<endl;
        break;
    }
    case 5:
    {
        clock_t start=clock();
        quickSort(arr, 0, n - 1);
        clock_t stop=clock();
        cout<<"Timpul utilizat pentru sortare: "<<(int)(stop-start)<<endl;
        break;
    }

    }
    ofstream fout("out.txt");
    for (int i=0; i < n; i++)
    {
        fout<<arr[i];
        if (i < n - 1) fout<<" ";
    }
    fout.close();

    delete[] arr;
    printf("Apasati Enter pentru a continua...");
    while(getchar() != '\n');
    getchar();
    system("cls");
    goto inceput;
    return 0;
}
