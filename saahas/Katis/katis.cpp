#include<iostream>
using namespace std;
int main()
{
    int greatest = 0;
    int least=1000000;
    int count;
    cin >> count;
    int num;
    do
    {
        cin >> num;
        count--;
        if (greatest < num) { greatest = num; }
        if (least > num) { least = num; }
    } while (count>0);
    cout << "largest number is : " << greatest << endl;
    cout << "smallest number is : " << least<<endl;
    cout << "range is : " << greatest-least<<endl;
}