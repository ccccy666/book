
#ifndef CODE_TOKENSCANNER_HPP
#define CODE_TOKENSCANNER_HPP

#include <cctype>
#include "error.h"
#include <string>
#include <sstream>

class Token_scanner{
public:
    std::string line;
    int position=0;

    Token_scanner(){};
    ~Token_scanner(){};

    void setInput(std::string &line_){
        line=line_;
        position=0;
    }

    std::string nextToken (){
        bool flag=0;
        for(int j=0;j<line.length();j++){
            if(line[j]!=' '){
                flag=1;
                break;
            }
        }
        if(!flag){
            return " ";
        }
        if(!hasMoreTokens())error("Invalid");
        int i=0;

        std::string ss;

        while(line[position]==' '){
            position++;
        }
        while(line[position]!=' '&&line[position]!='\0'){
            if(line[position]<32||line[position]==127)error("Invalid");
            ss+=line[position];
            position++;
            i++;
        }
        return ss;
    }

    bool hasMoreTokens(){
        int k=position;
        while(line[k]==' '){
            k++;
        }
        if(line[k]=='\0')return false;
        return true;
    }
};

#endif //CODE_TOKENSCANNER_HPP
