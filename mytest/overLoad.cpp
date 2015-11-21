/*************************************************************************
	> File Name: overLoad.cpp
	> Author:Maoting Ren 
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 18 Nov 2015 02:29:38 PM EST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<list>

class Node
{
    public:
        int getX()const { return x;}
        Node(int k):x(k){}
    private:
        int x;
};
        std::ostream& operator<<(std::ostream& os, const Node& node)
        {
            return os << node.getX();
        }
bool operator<(const Node& lhs, const Node& rhs)
{
    return lhs.getX() < rhs.getX();
}

int main()
{
    std::list<Node> vec;
    for(int i =0; i < 10; i++)
    {
        Node node(10-i);
        vec.push_back(node);
    }
    vec.sort();
    std::list<Node>::iterator it;
    for(it = vec.begin(); it != vec.end(); it++)
        std::cout << it->getX()<< " ";
    return 0;
}
