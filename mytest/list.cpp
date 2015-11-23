/*************************************************************************
	> File Name: list.cpp
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 18 Nov 2015 02:54:57 AM EST
 ************************************************************************/

#include<iostream>
#include<list>

int main()
{
    std::list<int> ll;
    std::list<int>::iterator ptr;
    for(int i = 0; i < 1; i++)
        ll.push_back(i);

    for(ptr = ll.begin(); ptr != ll.end(); ptr++)
        std::cout << *ptr << " ";
    std::cout << std::endl;


    ptr = ll.begin();
    ll.erase(ptr);
    ll.pop_back();
    std::cout << "after earse head:" << std::endl; 
    for(ptr = ll.begin(); ptr != ll.end(); ptr++)
        std::cout << *ptr << " ";
    std::cout << std::endl;

    return 0;
}
