/*************************************************************************
	> File Name: maps.cpp
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 18 Nov 2015 02:13:32 AM EST
 ************************************************************************/

#include<iostream>
#include<map>

int main()
{
    std::map<std::string, int> m;
    m.insert(std::pair<std::string, int>("a", 100));
    m.insert(std::map<std::string, int>::value_type("b", 200));
    m["c"] = 300;
    
    std::map<std::string, int>::iterator it;
    for(it = m.begin(); it != m.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    it = m.find("b");
    if(it != m.end())
    {
        std::cout << "find it! " ;
        std::cout << it->first << " " << it->second << std::endl; 
    }
    else
    {
        std::cout << "can not find!" << std::endl;
    }

    m.erase("a");
    m.erase(it);
    for(it = m.begin(); it != m.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    return 0;
}
