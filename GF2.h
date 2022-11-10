//
// Created by Ростислав Буржимський on 9/11/2022.
//

#ifndef BURZHYMSKYI_FI_03_LAB3_GF2_H
#define BURZHYMSKYI_FI_03_LAB3_GF2_H

#include <iostream>
#include <cmath>
#include <sstream>

#define ull unsigned long long

class GF2
{
private:
    std::string hex;
    ull* elementGF = nullptr;
    int size = 0;
    int maxSize = 6
    ull generator[3] {23,0,2251799813685248};//needed check
public:
    GF2(std::string);
    GF2(int );
    ~GF2();
    ull hexCharToNumber(char&);
    void convertHexTo64Bit();
    std::string convert64bitToHex();
    

    friend GF2& operator + (const GF2 &, const GF2 &);
    friend GF2& operator % (const GF2 &, const GF2 &);
};


#endif //BURZHYMSKYI_FI_03_LAB3_GF2_H
