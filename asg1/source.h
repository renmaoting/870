/*************************************************************************
	> File Name: source.h
	> Author: 
	> Mail: 
	> Created Time: Wed 09 Sep 2015 12:33:37 AM EDT
 ************************************************************************/

#ifndef _SOURCE_H
#define _SOURCE_H

class Source
{
public:
    static Source* getInstance()
    {
        if(instance != 0)
        {
            instance = new Source();
        }
        return instance;
    }

    int getValue();
private:
    Source(){}
    Source& operator=(const Source& Source){}
    class Trash
    {
    public:
        ~Trash()
        {
            if(Source::instance)
                delete Source::instance;
        }
    };
    static Trash trash;
    static Source* instance;
    Source(){}
};
#endif
