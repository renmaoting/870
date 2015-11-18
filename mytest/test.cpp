/*************************************************************************
	> File Name: testStrSteam.cpp
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 18 Nov 2015 12:30:40 AM EST
 ************************************************************************/

#include<iostream>
#include <sstream>
using namespace std;

int test_sstream(int bug)
{
    stringstream stream;
    stream<<"abc";
    int n;
    stream>>n;

    //here we should use both clear() and str("")
    //otherwise we will not get correct result and s will equal to "" or "abcdef" 
    if(bug == 0)
    {
        stream.clear();//clear error flag
        stream.str("");//clear content
    }
    if (bug == 1)
    {
        stream.clear();//clear error flag
    }
    else if (bug == 2)
    {
        stream.str("");//clear content
    }
    
    stream << "def";
    string s;
    stream>>s;
    cout << "BUG=" << bug << " DEF = " << s <<endl;
    
    return 0;
}
    
int main()
{
    test_sstream(0);
    test_sstream(1);
    test_sstream(2);
    
    return 0;
}
