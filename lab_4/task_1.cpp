#include <iostream>

using namespace std;

int* compress(int* arr, int n);
int* decompress(int* arr, int n);
int search(int* arr, int target, int n);
int main(void)
{
    int n;
    cin >> n;
    int* nums = new int[n]{};
    int index = 0;
    //array generation
    for(int i = 0; i <= 17; i++)
    {
        cout << "enter amount of number: " << i << endl;        
        int j = 0;
        cin >> j;
        for (int k = 0; k < j; k++)
        {
            nums[index+k] = i;
        }
        index += j;
    }
    cout << endl;
    int* parts = compress(nums, n);
    for (int i = 0; i < 18; i++)
    {
        cout << parts[i] << endl;
    }
    cout << endl;
    nums = decompress(parts, n);
    for (int k = 0; k < n; k++) cout << nums[k] << endl;
    delete nums;
    delete parts;
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

int* compress(int* arr, int n)
{
    int* parts = new int[18]{};
    int i = 1;
    int pos = 0;
    int temp = 0;
    while (i <= 17)
    {
        pos = search(arr, i, n);
        int j = i + 1;
        while (pos == -1)
        {
            pos = search(arr, j, n);
            j++;
        }
        parts[i-1] = pos - temp;
        temp = pos;
        i = j;
    }
    parts[i-1] = n - pos;
    return parts;

}

int* decompress(int* parts, int n)
{
    int index = 0;
    int* arr = new int[n] {};
    for(int i = 0; i <= 17; i++)
    {
        int j = 0;
        while (j < parts[i])
        {
            arr[index+j] = i;
            j++;
        }
        index += j;
    }
    return arr;
}