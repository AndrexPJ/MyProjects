#include <specialFunctions.h>
float floatRandom(void)
{
    return ((float)rand()/(float)RAND_MAX);
}

float floatRandom(float a,float b)
{
    return a + (b - a) * (floatRandom());
}


bool listElem(int e,std::list<int> l)
{
    for(list <int>::iterator it = l.begin();it!=l.end();it++)
    {
        if(*it == e) return true;
    }
    return false;
}
