//
// Created by walid on 5/27/20.
//

#include <utility>

#include "bits/stdc++.h"

using namespace std;

#ifndef ASSEMBLER_DATATYPESHANDLER_H
#define ASSEMBLER_DATATYPESHANDLER_H

#endif //ASSEMBLER_DATATYPESHANDLER_H

string decToHexa2(int n) {
    // char array to store hexadecimal number
    string hexaDeciNum = "";

    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;

        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum += temp + 48;
            i++;
        } else {
            hexaDeciNum += temp + 55;
            i++;
        }

        n = n / 16;
    }

    // printing hexadecimal number array in reverse order
    reverse(hexaDeciNum.begin(), hexaDeciNum.end());
    return hexaDeciNum;
}

class dataTypesHandler {
public:
    unordered_map<string, string> symbolicTable;

    pair<string, int> handleDataType(vector<string> line, string location) {
        symbolicTable[line[0]] = std::move(location);
        int length;
        string result;
        bool wordOrByte = true;
        if (line[1] == "word") {
            result = decToHexa2(stoi(line[2]));
            length = 6;
        } else if (line[1] == "resw") {
            length = 6 * stoi(line[2]);
            wordOrByte = false;
        } else if (line[1] == "byte") {
            if (line[2][0] == 'c') {
                char c = line[2][2];
                result = to_string((int) c);
            } else if (line[2][0] == 'x') {
                for (int i = 2; line[2][i] != '\''; ++i) {
                    result += line[2][i];
                }
            } else {
                result = decToHexa2(stoi(line[2]));
            }
            length = 2;
        } else {
            length = 2 * stoi(line[2]);
            wordOrByte = false;
        }
        while (result.size() < length && wordOrByte) {
            result.insert(0, "0");
        }
        pair<string, int> out(result, length / 2);
        return out;
    }
};
