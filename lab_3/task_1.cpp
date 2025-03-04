#include <iostream>
#include <cstring>

using namespace std;

int main(void)
{
    char s1 [10] = "tier";
    char s2 [10] = "jauar";
    char s3 [10];
    // string contacenation
    cout << strcat(s1, s2);
    cout << endl;
    // copy symbol arrays
    strcpy(s3, s1);
    cout << s3;
    cout << endl;
    // get string length
    cout << strlen(s3);
    cout << endl;
    return 0;
}