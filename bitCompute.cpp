#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

unordered_map<int, int> d;

int minDays(int n) {
        if (n <= 1)
        {
            cout << n << endl;
            return n;    
        }
        else if (d.find(n) != d.end())
        {
            cout << n << endl;
            return d[n];
        }
        else
        {
            d[n] = min(n%2+1+minDays(n/2),  // n%2是需要先吃1个的天数（只有先吃1个才能被2整除）
                       n%3+1+minDays(n/3)); // n%2是需要先吃1个的天数（只有先吃1个才能被3整除，最多先连续2天吃1个）
            cout << n << endl;
            return d[n];
        }
}

int main(){
    int day = minDays(56);

    cout << "Day:" << day << endl;
}