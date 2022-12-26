#ifndef CODE_ACCOUNT_HPP
#define CODE_ACCOUNT_HPP
#include <fstream>
//#include "linklist_.h"
#include<cstring>
#include"error.h"
using namespace std;
struct userID {
    char userid[32];
    userID(){};
    userID(std::string &in){
        for(int i=0;i<in.size();i++){
            userid[i]=in[i];
        }
        userid[in.size()]='\0';
    }
    bool operator==(userID other)const{
        return (!strcmp(userid,other.userid));
    }
    bool operator <(userID other)const{
        return (strcmp(userid,other.userid)<0);
    }
    bool operator <=(userID other)const{
        return ((strcmp(userid,other.userid)<0)||(!strcmp(userid,other.userid)));
    }
};

class Account {
public:
    int privilege=-1;
    char password[32];
    char username[32];
    userID ID;
    //bool condition;
    Account(){};
    bool operator<(const Account &other)const {
        return ID<other.ID;
    }
    bool operator==(const Account &other)const{
        return ID==other.ID;
    }
    bool operator >=(const Account &other)const{
        return (!(ID<other.ID));
    }
    bool operator <=(const Account &other)const{
        return (ID<other.ID||ID==other.ID);
    }
    Account(std::string ID_, std::string pass, std::string name, int privi):ID(ID_){
        privilege=privi;
        for(int i=0;i<pass.size();i++){
            password[i]=pass[i];
        }
        password[pass.size()]='\0';
        for(int i=0;i<name.size();i++){
            username[i]=name[i];
        }
        username[name.size()]='\0';
    };

    ~Account(){};

    void change_password(std::string new_pass){
        for(int i=0;i<new_pass.size();i++){
            password[i]=new_pass[i];
        }
        password[new_pass.size()]='\0';
    };
};
struct block {
    int next = -1;
    Account mini, maxi;
    int size = 0;
    Account ele[2001];
    int place;
};
class All_Account {
public:

    const int maxsize = 2000, minsize = 1000;
    int total = 0;
    fstream inout;
    const string filename="Account";
    //block tp;

    All_Account() {
//        filename=file;
        inout.open(filename);
        if (!inout) {
            block tmp;
            ofstream out;
            out.open(filename);
            total = 0;
            //string s="root";
            Account ac("root","sjtu","",7);
            tmp.ele[0]=ac;
            tmp.size=1;
            tmp.mini=tmp.maxi=ac;
            tmp.place=0;
            out.write(reinterpret_cast<char *>(&total), sizeof(total));
            out.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            out.close();
            inout.open(filename);
            return;
        }
        inout.seekg(0);
        inout.read(reinterpret_cast<char *>(&total), sizeof(total));
    }

    ~All_Account() {
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.close();
    }
    void getin(int coord, block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(block) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&(node.next)), sizeof(node.next));
        inout.read(reinterpret_cast<char *>(&(node.mini)), sizeof(node.mini));
        inout.read(reinterpret_cast<char *>(&(node.maxi)), sizeof(node.maxi));
        inout.read(reinterpret_cast<char *>(&(node.size)), sizeof(node.size));
    }
    void myread(int coord, block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(block) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }
    void mywrite(int coord, block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekp(coord * sizeof(block) + sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));
    }

    void split(int coord, block &node) {
        total++;
        block new_;
        for (int i = minsize; i < node.size; ++i) {
            new_.ele[i - minsize] = node.ele[i];
        }
        new_.size = minsize + 1;
        new_.place=total;
        new_.next = node.next;
        node.next = total;
        node.size = minsize;
        node.maxi = node.ele[node.size - 1];
        node.mini = node.ele[0];
        new_.maxi = new_.ele[node.size];
        new_.mini = new_.ele[0];
        mywrite(coord, node);
        mywrite(total, new_);
    }

    void insert_sort(int coord, const Account &ele) {
        block new_;
        if (total == -1) {
            ++total;
            new_.size = 1;
            new_.mini = new_.maxi = ele;
            new_.ele[0] = ele;
            mywrite(total, new_);
            return;
        }
        myread(coord, new_);
        int tmp = 0;
        for (int i = 0; i < new_.size; ++i) {
            if (ele < new_.ele[i]) {
                break;
            }
            tmp++;
        }
        for (int i = new_.size; i > tmp; --i) {
            new_.ele[i] = new_.ele[i - 1];
        }
        new_.ele[tmp] = ele;
        ++new_.size;
        if (new_.size > maxsize) {
            split(coord, new_);
        } else {
            new_.mini = new_.ele[0];
            new_.maxi = new_.ele[new_.size - 1];
            mywrite(coord, new_);
        }
    }

    void insert(const Account &ele) {
        block new_;
        getin(0, new_);
        if (new_.size == 0 || ele < new_.mini) {
            insert_sort(0, ele);
            return;
        }
        block nx;
        int i = 0;
        while (true) {
            if (new_.next == -1) {
                break;
            }
            getin(new_.next, nx);
            if (ele >= new_.mini && ele < nx.mini) {

                insert_sort(i, ele);
                return;
            }
            i = new_.next;
            new_ = nx;
        }
        insert_sort(i, ele);
    }
    block getblock(const userID inde){
        block new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.ID <= inde) && (inde <= new_.maxi.ID)) {
                myread(i, new_);
                return new_;
            } else if (inde < new_.mini.ID) {
                break;
            }
            i = new_.next;
        }
        error("Invalid");
    }
    Account find(const userID &inde) {
        block new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.ID <= inde) && (inde <= new_.maxi.ID)) {
                myread(i, new_);
                for (int k = 0; k < new_.size; ++k) {
                    if (new_.ele[k].ID == inde) {
                        //fin = true;
                        return new_.ele[k];
                    }
                }
            } else if (inde < new_.mini.ID) {
                break;
            }
            i = new_.next;
        }
        error("Invalid");
    }
    void merge(int coord, block &node) {
        int nx1 = node.next;
        if (nx1 == -1) {
            mywrite(coord, node);
            return;
        }
        block nx;
        myread(nx1, nx);
        if (node.size + nx.size <= maxsize) {
            for (int i = node.size; i < node.size + nx.size; ++i) {
                node.ele[i] = nx.ele[i - node.size];
            }
            node.size += nx.size;
            node.next = nx.next;
            node.mini = node.ele[0];
            node.maxi = node.ele[node.size - 1];
        } else if (nx.size > minsize) {
            node.maxi = node.ele[node.size] = nx.ele[0];
            node.size++;
            nx.mini = nx.ele[1];
            for (int i = 1; i < nx.size; i++) {
                nx.ele[i - 1] = nx.ele[i];
            }
            nx.size--;
            mywrite(node.next, nx);
        }
        mywrite(coord, node);

    }
    void delete_sort(int coord, const Account &ele) {
        block new_;
        myread(coord, new_);
        for (int i = 0; i < new_.size; ++i) {
            if (new_.ele[i] == ele) {
                for (int j = i + 1; j < new_.size; ++j) {
                    new_.ele[j - 1] = new_.ele[j];
                }
                --new_.size;
                if (!new_.size) {
                    mywrite(coord, new_);
                    break;
                }
                new_.mini = new_.ele[0];
                new_.maxi = new_.ele[new_.size - 1];
                if (new_.size < minsize) {
                    merge(coord, new_);
                } else {
                    mywrite(coord, new_);
                }
                break;
            }
        }
    }

    void del(const Account &ele) {
        block new_;
        int i = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if (new_.mini <= ele && new_.maxi >= ele) {
                delete_sort(i, ele);
                break;
            }
            if (ele < new_.mini) {
                break;
            }
            i = new_.next;
        }
    }
    bool exist(userID &inde){
        block new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.ID <= inde) && (inde <= new_.maxi.ID)) {
                myread(i, new_);
                for (int k = 0; k < new_.size; ++k) {
                    if (new_.ele[k].ID == inde) {
                        return true;
                    }
                }
            } else if (inde < new_.mini.ID) {
                break;
            }
            i = new_.next;
        }
        return false;
    };
};
#endif //CODE_ACCOUNT_HPP
