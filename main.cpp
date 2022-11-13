#include <iostream>
#include "GF2.h"
#include <cmath>
#include <stdint.h>
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

integer g()
{
    integer i(1);
    std::cout<<"g adress"<<&i<<'\n';
    return i;
}

int main()
{
    while(true)
    {
        std::string c,d;
        //acacacacacacacacacacacacacacacacacacacacafffffffaaaaaacccceeeecececececeecececececeecececececeecef
        //10101100101011001010110010101100101011001010110010101100101011001010110010101100101011001010110010101100101011001010110010101100101011001010110010101100101011001010111111111111111111111111111110101010101010101010101011001100110011001110111011101110110011101100111011001110110011101100111011101100111011001110110011101100111011001110111011001110110011101100111011001110110011101110110011101111
        std::cin>>c;
        //c="6ea32dc8d103aab22d2718a3e85a53fb6ea32dc8d103aab22d2718a3e85a53fb";
        GF2 b(c),a(c);
        //a.countCreated= 0;
        //a.countDelete = 0;

        //GF2 tmp = (a*b);
        //6625df7cdb83c2802a8fdaa81550c669c2a4527b9c4a9 bug with power
        std::cout<<b.power2().convert64bitToHex()<<(b*b).convert64bitToHex()<<'\n';
        std::cout<<b.Trace()<<'\n';
        //<<;
        //std::cout<<f+'\n';
        std::cout<<' '<<a.countDelete-a.countCreated<<'\n';
//        if(G->convert64bitToHex() != tmp.convert64bitToHex())
//        {
//            std::cout<<G->convert64bitToHex() <<' '+ tmp.convert64bitToHex();
//            break;
//        }
      // delete tmp;
    }
    return 0;
}
