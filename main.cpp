#include <iostream>
#include "GF2.h"

class integer
{
public:


    int* i;
    integer(const int& k)
    {
        i = new int(k);
    }

    ~integer()
    {
        std::cout<<"integer deleted\n";
        delete i;
    }
};


integer& h()
{
    integer *i = new integer(1);
    std::cout<<"g adress"<<i<<'\n';
    return *i;
}

integer& g()
{
    integer i(1);
    std::cout<<"g adress"<<&i<<'\n';
    return i;
}


int main()
{
    integer *n = new integer('2');

    for(unsigned  long long i =0 ;i<INT_MAX;++i)
    {
        std::string a,b;
        std::cin>>a>>b;
        GF2 a1(a),a2(b);
        GF2 res = (a1+a2);
        std::cout<<res.convert64bitToHex()<<' ';
    }

    return 0;
}
