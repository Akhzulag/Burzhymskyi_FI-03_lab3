//
// Created by Ростислав Буржимський on 9/11/2022.
//

#include "GF2.h"

GF2::~GF2()
{
    std::cout<<"\nd\n";
    delete[] elementGF;
}

GF2::GF2(std::string hex)
{
    this->size = ceil(double(hex.size())/16);
    elementGF = new ull[this->size];

    for(int i = 0; i < size; ++i)
    {
        elementGF[i] = 0;
    }

    for(int i = hex.size() - 1; i < size*16 - 1; ++i)//was size*16
    {
        hex = '0' + hex;
    }

    std::transform(hex.begin(), hex.end(), hex.begin(), ::toupper);

    this->hex = hex;
    convertHexTo64Bit();
    convert64bitToHex();
}

GF2::GF2(int size)
{
    this->size = size;
    elementGF = new ull[size];

    for(int i = 0; i < size; ++i)
    {
        elementGF[i] = 0;
    }
}


ull GF2::hexCharToNumber(char& hex)
{
    switch (hex)
    {
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            if(hex > '0' && hex <= '9')
                return hex - '0';
            return 0;
    }
}
void GF2::convertHexTo64Bit()
{
    std::reverse(hex.begin(), hex.end());

    for(int i = 0; i < size; ++i)
        for(int k = 0; k < 16; ++k)
            elementGF[i] |= (hexCharToNumber(hex[16 * i + k]) << k*4);

}

std::string GF2::convert64bitToHex()
{
    char numHex[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    std::ostringstream stream ;
    for(int i = 0; i < size; ++i)
        for(int k = 0; k < 16; ++k)
            stream << numHex[(elementGF[i] >> k*4) & 15];

    std::string tmpHex = stream.str();

    std::reverse(tmpHex.begin(), tmpHex.end());
    hex = '0';
    for(int i=0; i<tmpHex.size(); ++i)
    {
        if(tmpHex[i] != '0')
        {
            hex = tmpHex.substr(i);
            break;
        }
    }

    std::transform(this->hex.begin(), this->hex.end(), this->hex.begin(), ::tolower);
    return hex;
}




GF2& operator + (const GF2& left, const GF2& right)
{
    GF2 *tmp = new GF2(std::max(left.size, right.size));

    for(int i = 0; i < tmp->size; ++i)
    {
        tmp->elementGF[i] = left.elementGF[i] ^ right.elementGF[i];
    }

    return *tmp;
}

GF2& operator %  (const GF2& left, const GF2& right)
{


}



