#include <iostream>

void first(int arr[10], int n);
void second(int* arr, int n);
void third(int arr[], int n);
void fourth(int* arr, int n);

using namespace std;

int main(void)
{
    int static_array[10] = {};
    int* pda = new int [10];
    
    first(static_array, 10);
    second(static_array, 10);
    third(pda, 10);
    fourth(pda, 10);
    delete pda;
    return 0;
}

void first(int arr[], int n)
{
    for (int i = 0; i < n; i++){
        arr[i] = i*i;
    }
    for (int i = 0; i < n; i++){
        cout << arr[i] << endl;
    }
    cout << endl;
};

void second(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        *(arr + i) = i * i;
    }
    for (int i = 0; i < n; i++)
    {
       cout << *(arr + i) << endl;
    }
    cout << endl;
    return;
}

void third(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i * i;
    }
    for (int i = 0; i < n; i++)
    {
       cout << arr[i] << endl;
    }
    cout << endl;
    return;
}

void fourth(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        *(arr + i) = i * i;
    }
    for (int i = 0; i < n; i++)
    {
       cout << *(arr + i) << endl;
    }
    cout << endl;
    return;
}
