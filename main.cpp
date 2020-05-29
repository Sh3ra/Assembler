#include <iostream>
#include <bits/stdc++.h>
#include "objectCodeTable.h"
#include "dataTypesHandler.h"

using namespace std;

void convertLowerCaseReplaceTabsAndSpacesBySingleSpace(string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '\'') {
            i++;
            while (str[i] != '\'')
                i++;
        }
        if (str[i] == '\t')
            str[i] = ' ';
    }
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        if (str[i] == '\'') {
            i++;
            while (str[i] != '\'')
                i++;
        }
        if (i + 1 < str.length()) {
            if (str[i] == ' ' && (str[i + 1] == ' ' || str[i + 1] == ',')) {
                str.erase(str.begin() + i);
                i--;
            } else if (str[i] == ',' && str[i + 1] == ' ') {
                str.erase(str.begin() + i + 1);
                i--;
            }
        }
    }
    if (str[0] == ' ')
        str.erase(str.begin());
    if (str[str.length() - 1] == '\r')
        str.erase(str.end() - 1);
    if (str[str.length() - 1] == ' ')
        str.erase(str.end() - 1);
}

vector<vector<string>> convertToLabels(vector<string> code) {
    vector<vector<string>> instructions(code.size());
    for (int i = 0; i < code.size(); i++) {
        std::string s = code[i];
        std::string delimiter = " ";
        s += " ";
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            instructions[i].push_back(token);
            s.erase(0, pos + delimiter.length());
        }
    }
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i].size() < 3) {
            if (instructions[i].size() == 2) {
                vector<string> v;
                v.push_back("");
                v.push_back(instructions[i][0]);
                v.push_back(instructions[i][1]);
                instructions[i] = v;
            }
            if (instructions[i].size() == 1) {
                vector<string> v;
                v.push_back("");
                v.push_back(instructions[i][0]);
                v.push_back("");
                instructions[i] = v;
            }
        }
    }
    return instructions;
}

vector<string> readFile(const string &filename) {
    vector<string> answer;
    std::ifstream file(filename);
    std::string str;
    while (std::getline(file, str)) {
        answer.push_back(str);
    }
    return answer;
}

vector<regex> initializeRegexVector() {
    vector<regex> regexVector;
    string declarationRes = R"([a-z]\w*\s(resb|resw)\s\d{1,4})";
    string declarationByte = R"([a-z]\w*\s(byte)\s(x'([a-f0-9]{0,14})'|c'(\D|\S){0,15}'))";
    string declarationWord = R"([a-z]\w*\s(word)\s-?\d{1,4})";
    regex declaration("(" + declarationWord + "|" + declarationByte + "|" + declarationRes + ")");
    regexVector.push_back(declaration);
    regex access(R"(([a-z]\w*\s)?\+?(st|ld)(x|a|b|s|t|ch)\s(\*|(#|@)?([a-z]\w*|\d{1,4})(,([a-z]\w*|\d{1,4}))?))");
    regexVector.push_back(access);
    regex jump(R"(([a-z]\w*\s)?(td|rd|wd|jeq|jlt|jle|jge|j|jgt|jsub|tixr)\s(\*|[a-z]\w*))");
    regexVector.push_back(jump);
    regex rsub("rsub");
    regexVector.push_back(rsub);
    regex commentLine(R"(\.(\W|\S)*)");
    regexVector.push_back(commentLine);
    regex emptyLine("");
    regexVector.push_back(emptyLine);
    return regexVector;
}

bool base = false;
int baseR = 0;

bool contain_comma(string s) {
    for (char x : s) {
        if (x == ',')
            return true;
    }
    return false;
}

string toUpperCase(string x) {
    for (int i = 0; i < x.size(); ++i) {
        if (x[i] >= 97 && x[i] <= 122)
            x[i] = x[i] - 32;
    }
    return x;
}

string decToHexa(int num) {
    map<int, char> m;

    char digit = '0';
    char c = 'a';
    for (int i = 0; i <= 15; i++) {
        if (i < 10) {
            m[i] = digit++;
        } else {
            m[i] = c++;
        }
    }
    string res = "";
    if (!num) {
        return "0";
    }
    if (num > 0) {
        while (num) {
            res = m[num % 16] + res;
            num /= 16;
        }
    } else {
        u_int n = num;
        while (n) {
            res = m[n % 16] + res;
            n /= 16;
        }
    }
    return res;
}

int getHex(string hexstr) {
    return (int) strtol(hexstr.c_str(), 0, 16);
}

vector<string> TRecords;
int Tindex = -1;

void makeNewT(string s) {
    Tindex++;
    TRecords.push_back("T");
    TRecords[Tindex] += s + "^";
}

bool is_int(string op) {
    for (char x : op) {
        if (x < 48 || x > 57)
            return false;
    }
    return true;
}

string HexToBin(string hexdec) {
    long int i = 0;
    string res = "";
    while (hexdec[i]) {
        switch (hexdec[i]) {
            case '0':
                res += "0000";
                break;
            case '1':
                res += "0001";
                break;
            case '2':
                res += "0010";
                break;
            case '3':
                res += "0011";
                break;
            case '4':
                res += "0100";
                break;
            case '5':
                res += "0101";
                break;
            case '6':
                res += "0110";
                break;
            case '7':
                res += "0111";
                break;
            case '8':
                res += "1000";
                break;
            case '9':
                res += "1001";
                break;
            case 'A':
            case 'a':
                res += "1010";
                break;
            case 'B':
            case 'b':
                res += "1011";
                break;
            case 'C':
            case 'c':
                res += "1100";
                break;
            case 'D':
            case 'd':
                res += "1101";
                break;
            case 'E':
            case 'e':
                res += "1110";
                break;
            case 'F':
            case 'f':
                res += "1111";
                break;
        }
        i++;
    }
    return res;
}

void createMap(unordered_map<string, char> *um) {
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'A';
    (*um)["1011"] = 'B';
    (*um)["1100"] = 'C';
    (*um)["1101"] = 'D';
    (*um)["1110"] = 'E';
    (*um)["1111"] = 'F';
}

string binToHex(string bin) {
    int l = bin.size();
    int t = bin.find_first_of('.');
    int len_left = t != -1 ? t : l;
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;
    if (t != -1) {
        int len_right = l - len_left - 1;
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }
    unordered_map<string, char> bin_hex_map;
    createMap(&bin_hex_map);
    int i = 0;
    string hex = "";
    while (1) {
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;
        if (bin.at(i) == '.') {
            hex += '.';
            i++;
        }
    }
    return hex;
}

int get_TA(string op, dataTypesHandler zattout) {
    if (op[0] == '#' || op[0] == '@') {
        op = op.substr(1, op.size());
    }
    if (is_int(op)) {
        return stoi(op);
    } else {
        if (zattout.symbolicTable.find(op) == zattout.symbolicTable.end() || zattout.symbolicTable[op] == "*") {
            zattout.symbolicTable[op] = "*";
            return 0;
        } else {
            return getHex(zattout.symbolicTable[op]);
        }
    }
}

string get_address(string op, string opernad, objectCodeTable table, dataTypesHandler zattout, int lctr) {
    string disp = "";
    string bin = HexToBin(table.table[op].second);
    bin.pop_back();
    bin.pop_back();
    if (opernad[0] == '#') {
        bin += "01";
    } else if (opernad[0] == '@') {
        bin += "10";
    } else
        bin += "11";
    if (contain_comma(opernad)) {
        bin += "1";
    } else
        bin += "0";
    int d = 0;
    d = get_TA(opernad, zattout);
    if (op[0] == '+' && d > 1048575) {
        d = get_TA(opernad, zattout) - lctr;
        if (d < -524288 || d > 524287) {
            if (base) {
                bin += "10";
                d = get_TA(opernad, zattout) - baseR;
            }
            if (bin.size() == 9)
                bin += "01";
        }
    } else if (d > 2047) {
        d = get_TA(opernad, zattout) - lctr;
        if (d < -2048 || d > 2047) {
            if (base) {
                bin += "10";
                d = get_TA(opernad, zattout) - baseR;
            }
            if (bin.size() == 9)
                bin += "01";
        }
    }
    if (bin.size() == 9)
        bin += "00";
    disp += decToHexa(d);
    if (op[0] == '+') {
        bin += "1";
        while (disp.size() < 5) {
            disp = "0" + disp;
        }
        disp = disp.substr(disp.size() - 5, 5);
    } else {
        bin += "0";
        while (disp.size() < 3) {
            disp = "0" + disp;
        }
        disp = disp.substr(disp.size() - 3, 3);
    }
    return binToHex(bin) + disp;
}

string register_register(string op, objectCodeTable table) {
    string res = "";
    if (!contain_comma(op)) {
        res += table.registersTable[op];
    } else {
        string f = "";
        f += op[0];
        res += table.registersTable[f];
        f = "";
        f += op[2];
        res += table.registersTable[f];
    }
    return res;
}

void writeobjCode(vector<vector<string>> code) {
    dataTypesHandler zattout;
    objectCodeTable table;
    freopen("objcode.txt", "w", stdout);
    int prog_len = 0;
    while (code[0][2].size() < 6) {
        code[0][2] = "0" + code[0][2];
    }
    string Slctr = code[0][2];
    string Slctr2 = code[0][2];
    int lctr = getHex(Slctr);
    string line = "^";
    bool done = false;
    int prev;
    for (int i = 1; i < code.size() - 1; i++) {
        if (line != "^" && !done) {
            makeNewT(Slctr);
            done = true;
        }
        if (code[i][1] == "word" || code[i][1] == "byte" || code[i][1] == "resw" || code[i][1] == "resb") {
            prev = lctr;
            pair<string, int> he5o = zattout.handleDataType(code[i], Slctr2);
            lctr += he5o.second;
            line += he5o.first;
        } else if (code[i][1] == "base" && code[i][0] == "") {
            base = true;
            baseR = getHex(zattout.symbolicTable[code[i][2]]);
        } else if (code[i][1] == "nobase" && code[i][0] == "") {
            base = false;
            baseR = 0;
        } else if (code[i][0] == "") {
            prev = lctr;
            lctr += table.table[code[i][1]].first;
            if (contain_comma(code[i][2]) && code[i][1][code[i][1].size() - 1] == 'r') {
                line += table.table[code[i][1]].second;
                line += register_register(code[i][2], table);
            } else {
                line += get_address(code[i][1], code[i][2], table, zattout, lctr);
            }
        }
        Slctr = decToHexa(prev);
        while (Slctr.size() < 6) {
            Slctr = "0" + Slctr;
        }
        Slctr2 = decToHexa(lctr);
        while (Slctr2.size() < 6) {
            Slctr2 = "0" + Slctr2;
        }
        if (line.size() >= 57) {
            string temp = decToHexa(line.size() / 2);
            while (temp.size() < 2) {
                temp = "0" + temp;
            }
            TRecords[Tindex] += temp + line;
            line = "^";
            done = false;
        }
    }
    if (line != "^") {
        string temp = decToHexa(line.size() / 2);
        while (temp.size() < 2) {
            temp = "0" + temp;
        }
        TRecords[Tindex] += temp + line;

        while (code[0][0].size() < 6) {
            code[0][0] += " ";
        }
    } else
        TRecords.pop_back();
    string Sprog_len = decToHexa(lctr - 1 - getHex(code[0][2]));

    while (Sprog_len.size() < 6) {
        Sprog_len = "0" + Sprog_len;
    }
    string HRecord = "H" + code[0][0].substr(0, 6) + "^" + code[0][2] + "^" + Sprog_len;
    cout << toUpperCase(HRecord) << endl;
    for (int i = 0; i < TRecords.size(); i++) {
        cout << toUpperCase(TRecords[i]) << endl;
    }
    cout << "E" << toUpperCase(code[0][2]);
}

int main() {
    vector<regex> regexVector = initializeRegexVector();
    vector<string> code = readFile("1.txt");

    for (int i = 0; i < code.size(); i++) {
        bool found = false;
        convertLowerCaseReplaceTabsAndSpacesBySingleSpace(code[i]);
        cout << code[i] << "\n";
        for (auto &j : regexVector) {
            if (regex_match(code[i], j)) {
                found = true;
            }
        }
        if (!found)
            cout << "Unmatched " << i << " " << code[i] << endl;
    }
    vector<vector<string>> v = convertToLabels(code);
    writeobjCode(v);
    return 0;
}
