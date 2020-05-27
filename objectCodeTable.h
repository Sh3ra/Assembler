//
// Created by walid on 5/27/20.
//

#include "bits/stdc++.h"

using namespace std;

#ifndef ASSEMBLER_OBJECTCODETABLE_H
#define ASSEMBLER_OBJECTCODETABLE_H


class objectCodeTable {
public:
    unordered_map<string, pair<int,string>> table;
    objectCodeTable() {
        table["add"] = make_pair(3, "18");
        table["+add"] = make_pair(3, "18");
        table["addr"] = make_pair(2, "90");
        table["addf"] = make_pair(3, "58");
        table["+addf"] = make_pair(4, "58");
        table["and"] = make_pair(3, "40");
        table["+and"] = make_pair(4, "40");
        table["clear"] = make_pair(2, "B4");
        table["comp"] = make_pair(3, "28");
        table["+comp"] = make_pair(4, "28");
        table["compf"] = make_pair(3, "88");
        table["+compf"] = make_pair(4, "88");
        table["compr"] = make_pair(2, "A0");
        table["div"] = make_pair(3, "24");
        table["+div"] = make_pair(4, "24");
        table["divf"] = make_pair(3, "64");
        table["+divf"] = make_pair(4, "64");
        table["divr"] = make_pair(2, "9C");
        table["fix"] = make_pair(1, "C0");
        table["float"] = make_pair(1, "C4");
        table["hio"] = make_pair(1, "F4");
        table["j"] = make_pair(3, "3C");
        table["+j"] = make_pair(4, "3C");
        table["jeq"] = make_pair(3, "30");
        table["+jeq"] = make_pair(4, "30");
        table["jgt"] = make_pair(3, "34");
        table["+jgt"] = make_pair(4, "34");
        table["jlt"] = make_pair(3, "38");
        table["+jlt"] = make_pair(4, "38");
        table["jsub"] = make_pair(3, "48");
        table["+jsub"] = make_pair(4, "48");
        table["lda"] = make_pair(3, "00");
        table["+lda"] = make_pair(4, "00");
        table["ldb"] = make_pair(3, "68");
        table["+ldb"] = make_pair(4, "68");
        table["ldch"] = make_pair(3, "50");
        table["+ldch"] = make_pair(4, "50");
        table["ldf"] = make_pair(3, "70");
        table["+ldf"] = make_pair(4, "70");
        table["ldl"] = make_pair(3, "08");
        table["+ldl"] = make_pair(4, "08");
        table["lds"] = make_pair(3, "6C");
        table["+lds"] = make_pair(4, "6C");
        table["ldt"] = make_pair(3, "74");
        table["+ldt"] = make_pair(4, "74");
        table["ldx"] = make_pair(3, "04");
        table["+ldx"] = make_pair(4, "04");
        table["lps"] = make_pair(3, "D0");
        table["+lps"] = make_pair(4, "D0");
        table["mul"] = make_pair(3, "20");
        table["+mul"] = make_pair(4, "20");
        table["mulf"] = make_pair(3, "60");
        table["+mulf"] = make_pair(4, "60");
        table["mulr"] = make_pair(2, "98");
        table["or"] = make_pair(3, "44");
        table["+or"] = make_pair(4, "44");
        table["rd"] = make_pair(3, "D8");
        table["+rd"] = make_pair(4, "D8");
        table["norm"] = make_pair(1, "C8");
        table["rmo"] = make_pair(2, "AC");
        table["rsub"] = make_pair(3, "4C");
        table["+rsub"] = make_pair(4, "4C");
        table["shiftl"] = make_pair(2, "A4");
        table["shiftr"] = make_pair(2, "A8");
        table["sio"] = make_pair(1, "F0");
        table["ssk"] = make_pair(3, "EC");
        table["+ssk"] = make_pair(4, "EC");
        table["sta"] = make_pair(3, "0C");
        table["+sta"] = make_pair(4, "0C");
        table["stb"] = make_pair(3, "78");
        table["+stb"] = make_pair(4, "78");
        table["stch"] = make_pair(3, "54");
        table["+stch"] = make_pair(4, "54");
        table["stf"] = make_pair(3, "80");
        table["+stf"] = make_pair(4, "80");
        table["sti"] = make_pair(3, "D4");
        table["+sti"] = make_pair(4, "D4");
        table["stl"] = make_pair(3, "14");
        table["+stl"] = make_pair(4, "14");
        table["sts"] = make_pair(3, "7C");
        table["+sts"] = make_pair(4, "7C");
        table["stsw"] = make_pair(3, "E8");
        table["+stsw"] = make_pair(4, "E8");
        table["stt"] = make_pair(3, "84");
        table["+stt"] = make_pair(4, "84");
        table["stx"] = make_pair(3, "10");
        table["+stx"] = make_pair(4, "10");
        table["sub"] = make_pair(3, "1C");
        table["+sub"] = make_pair(4, "1C");
        table["subf"] = make_pair(3, "5C");
        table["+subf"] = make_pair(4, "5C");
        table["td"] = make_pair(3, "E0");
        table["+td"] = make_pair(4, "E0");
        table["tix"] = make_pair(3, "2C");
        table["+tix"] = make_pair(4, "2C");
        table["wd"] = make_pair(3, "DC");
        table["+wd"] = make_pair(4, "DC");
        table["subr"] = make_pair(2, "94");
        table["svc"] = make_pair(2, "B0");
        table["tio"] = make_pair(1, "F8");
        table["tixr"] = make_pair(2, "B8");
    }
};


#endif //ASSEMBLER_OBJECTCODETABLE_H
