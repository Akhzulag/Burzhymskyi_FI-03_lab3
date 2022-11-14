//
// Created by Ростислав Буржимський on 9/11/2022.
//

#ifndef BURZHYMSKYI_FI_03_LAB3_GF2_H
#define BURZHYMSKYI_FI_03_LAB3_GF2_H

#include <iostream>
#include <cmath>
#include <sstream>
#include <memory>

#define ull unsigned long long

class GF2
{
private:
    std::string hex;
    ull elementGF[8];
    ull numberHex[8];

    int size = 0;
    ull generator[3] {23,0,2251799813685248};//needed check
    int bitSizeGen = 178;
public:
    static int countDelete;
    static int countCreated;

    GF2(std::string);
    GF2(int );
    GF2(ull *,int size);
    ~GF2();
    ull hexCharToNumber(char&);
    void convertHexTo64Bit();
    std::string convert64bitToHex();

    void copy(const GF2& );
    void allocGF2();
    GF2& shiftBitToHigh(int);
    GF2& power2();
    GF2& inversGF();
    int compare(const GF2 &,const GF2 &);
    GF2& modGenerator ();
    int bitSize() const;

    ull Trace();

    friend GF2& operator * (const GF2 &, const GF2 &);
    friend GF2& operator << (const GF2 &, int);
    friend GF2& operator ^ (const GF2 &, const GF2 &);
    GF2& operator += (const GF2 &);

};


#endif //BURZHYMSKYI_FI_03_LAB3_GF2_H
