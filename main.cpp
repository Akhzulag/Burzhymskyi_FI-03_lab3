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
        //1000100000100000000000001000101000101010001000100010001010101000100010100010001000001000100010110100001010111010010111101000101101111101001011101000000011100111110101101100001
        //GF2 tmp = (a*b);
        //6625df7cdb83c2802a8fdaa81550c669c2a4527b9c4a9 bug with power
//        std::string resMUL2 =(b*b).convert64bitToHex();
//        std::cout<<resMUL2<<' ';
//        std::string resP2 = b.power2().convert64bitToHex();
//        std::cout<<resP2+'\n';
        //std::cout<<b.Trace()<<'\n';
        if(b.Trace() == b.TraceMUL())
            std::cout<<'t';
        else
            std::cout<<'f';
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
