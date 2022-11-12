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

    for(int i = tmp->size - 1; i >= 0; --i)//TODO check size chages;
    {
        if(tmp->elementGF[i] == 0)
            --tmp->size;
        else
            break;
    }
    return *tmp;
}


GF2& GF2::shiftBitToHigh(int k)
{
    int sizeG = 0;
    int shift64 = k/64;
    int shiftBit = k - shift64*64;

    if (shiftBit > 12)
        sizeG = shift64 + 3 + 1;
    else
        sizeG = shift64 + 3;
    GF2 *tmp = new GF2(sizeG);

    for(int i = shift64+2; i >= shift64; --i)
    {
        tmp->elementGF[i] = this->generator[i - shift64];
    }

    ull carry = 0;
    if(shiftBit!=0)
        for(int i = 0; i < sizeG; ++i)
        {
            ull tmp1 =  tmp->elementGF[i] >> (64 - shiftBit);
            tmp->elementGF[i] = ( tmp->elementGF[i] << shiftBit) | carry;
            carry = tmp1;
        }

    return *tmp;
}

void GF2::copy(const GF2& copy)
{
    this->hex = copy.hex;
    this->size = copy.size;
    if(elementGF != nullptr)
        delete[] this->elementGF;
    this->elementGF = new ull[size];

    for(int i = 0; i < size; ++i)
    {
        this->elementGF[i] = copy.elementGF[i];
    }

}

GF2::GF2(ull *arr, int size)
{
    this->size = size;
    elementGF = new ull[size];
    for(int i = 0; i < size; ++i)
    {
        this->elementGF[i] = arr[i];
    }
}

int GF2::compare(const GF2 &left,const GF2 &right)
{
    int i = std::max(left.size, right.size) - 1;

    while(left.elementGF[i] == right.elementGF[i] && i > -1)
        --i;

    if(i == -1)
        return 1; // left = right or left >= right
    if(left.elementGF[i] > right.elementGF[i])
        return 1;
    return 0;
}



GF2& GF2::modGenerator(const GF2 &A)
{
    GF2* R = new GF2("1");
    R->copy(A);
    ull generator[3] {23,0,2251799813685248};//needed check
    GF2 B(generator,3);
    std::cout<<B.convert64bitToHex()+'\n';
    int k = 180;
    GF2* tmp = nullptr;
    while(compare(*R,B) == 1)
    {
        int t = 64*(R->size-1) + int(log2(R->elementGF[R->size-1]))+1;
        GF2 C = B.shiftBitToHigh(t-k);//проблема тут
        int r = 64*(C.size-1) + int(log2(C.elementGF[C.size-1])) + 1;
        if(compare(*R,B) == 0)
        {
            --t;
            C = shiftBitToHigh(k-t);
        }
        tmp = &(*R + C);
        delete R;
        R = tmp;
        tmp = nullptr;
    }

    return *R;
}



