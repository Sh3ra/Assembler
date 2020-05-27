#include <iostream>
#include "bits/stdc++.h"
#include "objectCodeTable.h"

using namespace std;


void convertLowerCaseReplaceTabsAndSpacesBySingleSpace(string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '\'') {
            i++;
            while (str[i] != '\'') i++;
        }
        if (str[i] == '\t') str[i] = ' ';
    }
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
        if (str[i] == '\'') {
            i++;
            while (str[i] != '\'') i++;
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
    if (str[0] == ' ') str.erase(str.begin());
    if (str[str.length() - 1] == '\r') str.erase(str.end() - 1);

    if (str[str.length() - 1] == ' ')str.erase(str.end() - 1);
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
    regex access(R"(([a-z]\w*\s)?\+?(st|ld)(x|a|b|s|t|ch)\s(\*|@?[a-z]\w*(,[a-z]\w*)?|#(\d{1,4}|\w*)))");
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
void decToHexa(int n) 
{    
    // char array to store hexadecimal number 
    char hexaDeciNum[100]; 
      
    // counter for hexadecimal number array 
    int i = 0; 
    while(n!=0) 
    {    
        // temporary variable to store remainder 
        int temp  = 0;
          
        // storing remainder in temp variable. 
        temp = n % 16; 
          
        // check if temp < 10 
        if(temp < 10) 
        { 
            hexaDeciNum[i] = temp + 48; 
            i++; 
        } 
        else
        { 
            hexaDeciNum[i] = temp + 55; 
            i++; 
        } 
          
        n = n/16; 
    } 
      
    // printing hexadecimal number array in reverse order 
    for(int j=i-1; j>=0; j--) 
        cout << hexaDeciNum[j]; 
} 
void writeobjCode(vector<vector<string>>code)
{
    objectCodeTable table;
    freopen("objcode.txt","w",stdout);
    string temp=code[0][0];
    while (code[0][0].size()<5)
    {
        code[0][0]+=" ";
    }
    cout<<"H"<<code[0][0]<<"^"<<code[0][2]<<"^";
    decToHexa(code.size());
}

int main() {
    vector<regex> regexVector = initializeRegexVector();
    vector<string> code = readFile("1.txt");
    for (int i = 0; i < code.size(); i++) {
        bool found = false;
        convertLowerCaseReplaceTabsAndSpacesBySingleSpace(code[i]);
        for (auto &j : regexVector) {
            if (regex_match(code[i], j)) {
                found = true;
            }
        }
        if (!found) cout << "Unmatched " << i << " " << code[i] << endl;
    }
    return 0;
}
