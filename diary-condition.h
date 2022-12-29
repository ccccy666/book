#ifndef CODE_DIARY_HPP
#define CODE_DIARY_HPP
#include"Account.h"
#include "Book.h"
//#include"condition.h"

//struct financediary{
//    double sum;
//    bool postive;
//
//};
class diary{

public:
    //int quantity=0;
    double sum=0;
    bool postive=1;
    //userID ID;
};

class diaryGroup {
public:
    //std::fstream log;
    fstream inout;
    //std::fstream fiannce_log;
    const string filename="log";
    int total=-1;

    diaryGroup(){
        inout.open(filename);
        if (!inout) {
            diary tmp;
            ofstream out;
            out.open(filename);
            total = -1;
            out.write(reinterpret_cast<char *>(&total), sizeof(total));
            out.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            out.close();
            inout.open(filename);
            return;
        }
        inout.seekg(0);
        inout.read(reinterpret_cast<char *>(&total), sizeof(total));
    }

    ~diaryGroup(){
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.close();
    };
    void myread(int coord, diary &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(diary) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }
    void mywrite(int coord, diary &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekp(coord * sizeof(diary) + sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));
    }


    void show(int count){
        diary mid;
        if(count==0){
            cout<<'\n';
            return;
        }
        double pos=0,neg=0;
        for(int i=0;i<count;i++){
            myread(total-i,mid);
            if(mid.postive){
                pos+=mid.sum;
            }else if(!mid.postive){
                neg+=mid.sum;
            }
        }
        string ss1= to_string(pos),s1= to_string(int(pos));
        string ss2= to_string(neg),s2= to_string(int(neg));
        cout<<"+ ";
        for(int g=0;g<s1.size()+3;g++){
            cout<<ss1[g];
        }
        cout<<" - ";
        for(int g=0;g<s2.size()+3;g++){
            cout<<ss2[g];
        }
        cout<<'\n';
        //cout<<"+ "<<pos<<" - "<<neg<<'\n';
    }

    void add_log(diary new_){
        ++total;
        mywrite(total,new_);
    };

};


struct log{
    char description[400];
    log(){};
    log(string &s){
        for(int i=0;i<s.size();i++){
            description[i]=s[i];
        }
    }
};

class all_Log{
public:
    fstream inout;
    const string filename="all_log";
    int total=-1;
    all_Log(){
        inout.open(filename);
        if (!inout) {
            log tmp;
            ofstream out;
            out.open(filename);
            total = -1;
            out.write(reinterpret_cast<char *>(&total), sizeof(total));
            out.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            out.close();
            inout.open(filename);
            return;
        }
        inout.seekg(0);
        inout.read(reinterpret_cast<char *>(&total), sizeof(total));
    }
    ~all_Log(){
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.close();
    }
    void myread(int coord, log &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(diary) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }
    void mywrite(int coord, log &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekp(coord * sizeof(diary) + sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));
    }
    void add_logs(log &node){
        ++total;
        mywrite(total,node);
    }
    void show_logs(){
        log a_log;
        for(int i=0;i<=total;i++){
            myread(i,a_log);
            string s;
            int k=0;
            while(a_log.description[k]!='\0'){
                s+=a_log.description[k];
            }
            cout<<s<<'\n';
        }
    }
};

struct _block{
    Account account;
    ISBN isbn;
    bool selected=0;
};
class condition{
public:
    fstream inout;
    const string filename="condition";
    int total=-1;
    ISBN book_id;
    bool is_selected=0;
    condition(){
        inout.open(filename,fstream::trunc);
        if (!inout) {
            _block tmp;
            ofstream out;
            out.open(filename);
            total = -1;
            out.write(reinterpret_cast<char *>(&total), sizeof(total));
            out.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            out.close();
            inout.open(filename);
            return;
        }
        _block tmp;
        total=-1;
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
//        inout.seekg(0);
//        inout.read(reinterpret_cast<char *>(&total), sizeof(total));
    }

    ~condition(){
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.close();
    };
    void myread(int coord, _block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(_block) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }
    void mywrite(int coord, _block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekp(coord * sizeof(_block) + sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));
    }
    Account get(){
        _block mid;
        //Account now;
        if(total<0)error("Invalid");
        myread(total,mid);

        return mid.account;
    }
    void login(Account an_Account){
        ++total;
        //ISBN isb;
        _block blk;
        blk.account=an_Account;
        //.isbn=isb;
        mywrite(total,blk);
    };

    void logout(){
        --total;
    };
    bool exist(const userID id){
        if(total<0)error("Invalid");
        _block node;
        for(int i=0;i<=total;i++){
            myread(i,node);
            if(node.account.ID==id)return true;
        }
        return false;
    }
    _block getblock(){
        if(total<0)error("Invalid");
        _block tmp;
        myread(total,tmp);
        return tmp;
    };
    void select (ISBN book_){
        _block mid,pro;
        myread(total,mid);
        mid.isbn=book_;
        mid.selected=1;
//        for(int i=0;i<total;i++){
//            myread(i,pro);
//            if(pro.account.ID==mid.account.ID){
//                pro.isbn=book_;
//                pro.selected=1;
//                mywrite(i,pro);
//            }
//        }
        mywrite(total,mid);
    };
};
#endif //CODE_DIARY_HPP
