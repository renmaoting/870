/*************************************************************************
	> File Name: leek.cpp
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 18 Nov 2015 03:37:03 AM EST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

typedef struct Node
{
    int a;
    int b;
}Node;
int main()
{
    vector<Node*> vec;
    for(int i =0; i< 10; i++)
        vec.push_back(new Node());

    for(unsigned int i =0; i< vec.size(); i++)
        delete vec[i];
    return 0;
}
