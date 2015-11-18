/*************************************************************************
	> File Name: functor.cpp
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 18 Nov 2015 03:16:22 AM EST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class cmp
{
public:
    template <class T>
    bool operator()(const T& a, const T& b)
    {
        return a < b;
    }
};

int main()
{
    vector<int> vec;
    for(int i =0; i < 10; i++)
        vec.push_back(rand()%30);
    sort(vec.begin(), vec.end(), cmp());

    for(int i =0; i < 10; i++)
        cout << vec[i] << " ";
    cout << endl;

    return 0;
}
