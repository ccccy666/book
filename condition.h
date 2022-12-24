#ifndef CODE_CONDITION_HPP
#define CODE_CONDITION_HPP
#include<cstring>
#include"Account.h"
#include"Book.h"

//using namespace std;
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
        Account now;
        if(total<0)error("Invalid");
        myread(total,mid);
        now=mid.account;
        return now;
    }
    void login(Account an_Account){
        ++total;
        ISBN isb;
        _block blk;
        blk.account=an_Account;
        blk.isbn=isb;
        mywrite(total,blk);
    };

    void logout(){
        --total;
    };
    _block getblock(){
        _block tmp;
        myread(total,tmp);
        return tmp;
    };
    void select (ISBN book_){
        _block mid;
        myread(total,mid);
        mid.isbn=book_;
        mid.selected=1;
        mywrite(total,mid);
    };
};
#endif //CODE_CONDITION_HPP
