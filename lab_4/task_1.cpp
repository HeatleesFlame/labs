#include <iostream>
#include <random>

using namespace std;

void compress(int* arr, int* new_parts, int n, int left, int right);
int* decompress(int* parts, int* arr, int n, int left, int right);
int search(int* arr, int target, int n);

int main(void)
{
    cout << "enter left" << endl; 
    int left;
    cin >> left;
    cout << "enter right" << endl;
    int right;
    cin >> right;

    int * parts = new int [right-left+1] {};
    int n = {};
    for (int i = left; i <= right; i++)
    {
        //random length generator
        random_device r;
        minstd_rand0 e1(r());
        uniform_int_distribution<int> uniform_dist(1, 6);
        parts[i-left] = uniform_dist(e1);
        n += parts[i-left];
    }

    //function calls
    int * arr = new int[n]{};
    arr = decompress(parts, arr, n, left, right);
    // don't forget delete arr if no need in it

    int* new_parts = new int[right-left+1];
    compress(arr, new_parts, n, left, right);
    // validate
    for (int i = 0; i < left-right+1; i++)
    {
        if (parts[i] != new_parts[i])
        {
            cout << "incorrect: " << i + left << endl; 
        }
    }
    delete arr;
    delete new_parts;
    delete parts;
    cout << "success" << endl;
    return 0;
}

int search(int* arr, int target, int n)
{
    int l = 0;
    int r = n;
    while (l < r)
    {
        int mid = (l+r)/2;
        if (arr[mid] > target) r = mid;
        else l = mid + 1;
    }
    r--;
    if (arr[r] == target) return r;
    else return -1;
}

void compress(int* arr, int* new_parts, int n, int left, int right)
{
    int i = left + 1;
    int pos = 0;
    int temp = 0;
    while (i < right)
    {
        pos = search(arr, i, n);
        int j = i + 1;
        while (pos == -1 && j <= right)
        {
            pos = search(arr, j, n);
            j++;
        }
        new_parts[i-left-1] = pos - temp;
        temp = pos;
        i = j;
    }
     new_parts[i-left-1] = n - pos;
    return;
   // for (0; n-1)
   // new_parts[arr[i]]++;
}

int* decompress(int* parts, int* arr,  int n, int left, int right)
{
    int index = 0;
    for(int i = left; i <= right; i++)
    {
        int j = 0;
        while (j < parts[i-left])
        {
            arr[index+j] = i;
            j++;
        }
        index += j;
    }
    return arr;
}

