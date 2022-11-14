#include "GF2.h"

GF2::~GF2()
{
    countDelete++;

}

void GF2::allocGF2()
{
    countCreated++;
    for(int i = 0; i < 8; ++i)
    {
        elementGF[i] = 0;
    }
}

GF2::GF2(std::string hex)
{
    this->size = ceil(double(hex.size())/16);

    this->allocGF2();

    for(int i = hex.size() - 1; i < size*16 - 1; ++i)
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
    allocGF2();
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




GF2& GF2::operator += (const GF2 &right)
{
    this->size = std::max(right.size, this->size);
    for(int i = 0; i < this->size; ++i)
    {
        this->elementGF[i] = this->elementGF[i] ^ right.elementGF[i];
    }

    for(int i = this->size - 1; i >= 0; --i)
    {
        if(this->elementGF[i] == 0)
            --this->size;
        else
            break;
    }

    return *this;
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

    this->allocGF2();
    for(int i = 0; i < size; ++i)
    {
        this->elementGF[i] = copy.elementGF[i];
    }

}

GF2::GF2(ull *arr, int size)
{

    this->size = size;
    allocGF2();
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
        return 1;
    if(left.elementGF[i] > right.elementGF[i])
        return 1;
    return 0;
}

int GF2::bitSize() const
{
    return 64*(this->size-1) + int(log2(this->elementGF[this->size-1])) + 1;
}

GF2& GF2::modGenerator()
{
    GF2 B(this->generator,3);

    int k = 180;

    while(compare(*this,B) == 1)
    {
        int t = this->bitSize();
        GF2 C = B.shiftBitToHigh(t-k);

        if(compare(*this,B) == 0)
        {
            --t;
            C.~GF2();
            C = B.shiftBitToHigh(k-t);
        }

        *this += C;
    }

    return *this;
}

int GF2::countCreated = 0;
int GF2::countDelete = 0;

GF2& operator << (const GF2 &right, int k)
{
    int sizeG = 0;
    int shift64 = k/64;
    int shiftBit = k - shift64*64;

    if( (int)log2(right.elementGF[right.size - 1]) + shiftBit > 63)
        sizeG = right.size + 1 + shift64;
    else
        sizeG = right.size + shift64;

    GF2 *tmp = new GF2(sizeG);
    if(k == 0)
    {
        tmp->copy(right);
        return *tmp;
    }

    for(int i = shift64+right.size - 1; i >= shift64; --i)
    {
        tmp->elementGF[i] = right.elementGF[i - shift64];
    }

    ull carry = 0;
    if(shiftBit!=0)
        for(int i = 0; i < sizeG; ++i)
        {
            ull tmpCarry =  tmp->elementGF[i] >> (64 - shiftBit);
            tmp->elementGF[i] = ( tmp->elementGF[i] << shiftBit) | carry;
            carry = tmpCarry;
        }

    return *tmp;
}


GF2& operator * (const GF2 &left, const GF2 &right)
{
    GF2* result = new GF2(1);

    int bitSize = right.bitSize();
    int j = -1;
    ull mask;

    for(int i = 0; i < bitSize; ++i)
    {
        if(i % 64 == 0)
        {
            ++j;
            mask = 1;
        }

        if((right.elementGF[j] & mask) != 0)
        {
            GF2 shifted = (left << i);
            *result += shifted;
            result->modGenerator();
        }

        mask = (mask << 1);

    }

    return *result;
}

GF2& GF2::power2()
{
    int bitSize = this->bitSize()*2+1;
    int size64 = 0;
    size64 =ceil(double(bitSize)/double (64));
    GF2* res = new GF2(size64);
    int k = 0;
    ull tmp;
    for(int i = 0; i < this->size; ++i)
    {
        tmp = this->elementGF[i];
        for(int j = 0; j < 128; j+=2)
        {
            res->elementGF[k] = res->elementGF[k] | ((tmp & 1) << j);
            tmp = tmp >> 1;
            if(j == 62 || j == 126)
                ++k;
        }
    }
    for(int i = res->size - 1; i >= 0; --i)
    {
        if(res->elementGF[i] == 0)
            --res->size;
        else
            break;
    }
    res->modGenerator();
    return *res;
}

ull GF2::Trace()
{

    *this = this->power2();

    GF2 res(1) ;
    res.copy(*this);
    for(int i = 1; i < 179; ++i)
    {
        GF2 tmp = *this;
        *this = this->power2();
        res += *this;
    }

    return (ull)res.elementGF[0];
}

GF2& operator ^ (const GF2& left, const GF2& right)
{
    GF2 *C = new GF2("1");
    int bitSizeRight = right.bitSize();
    int k = 0;
    uint64_t mask = 0x8000000000000000;
    for(int i = right.size - 1; i >= 0; --i)
    {
        while (mask!=0)
        {
            if((right.elementGF[i] & mask) >> ((int)log2(mask)) == 1)
            {
                GF2 tmp = *C;
                *C = *C * left;
            }

            if(i == 0 && mask == 1)
                break;

            GF2 tmp = *C;
            *C = C->power2();
            mask >>= 1;
        }
        mask = 0x8000000000000000;
    }

    return *C;
}

GF2& GF2::inverseGF()
{
    GF2 power("7fffffffffffffffffffffffffffffffffffffffffffe");
    return *this^power;
}