
#include <set>
//#include"Book.h"
//#include"linklist_.h"
//#include"condition.h"
#include"diary.h"
#include "token_scanner.h"
#include"condition.h"
//#include<sstream>

using namespace std;

int main() {
    string line, operat;
    All_Books allbooks;
    All_Account allaccount;
    condition now_user;
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    while (getline(cin, line)) {
        try {
            scanner.setInput(line);
            operat = scanner.nextToken();
            if (operat == "quit"){
                exit(0);
            } else if (operat == "exit") {
                exit(0);
            } else if (operat == "su") {
                string id, word;
                Account account_;
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    id[i] = operat[i];
                }
                userID _id(id);
                if (allaccount.exist(_id) == 0) {
                    error("Invalid");
                }
                account_ = allaccount.find(id);
                if (!scanner.hasMoreTokens()) {
                    if (now_user.get().privilege <= account_.privilege) {
                        error("Invalid");
                    }
                    now_user.login(account_);
                    continue;
                }
                scanner.nextToken();
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    id[i] = operat[i];
                }
                if (account_.password != word) {
                    error("Invalid");
                }
                now_user.login(account_);
            } else if (operat == "logout") {
                if (now_user.total == -1) {
                    error("Invalid");
                }
                now_user.logout();
            } else if (operat == "register") {
                string id, pasword, nam;
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    id[i] = operat[i];
                }
                userID _id(id);
                if (allaccount.exist(_id)) {
                    error("Invalid");
                }
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    pasword[i] = operat[i];
                }
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    nam[i] = operat[i];
                }
                Account new_(id, pasword, nam, 1);
                allaccount.insert(new_);
            } else if (operat == "passwd") {
                //todo
                string id, oldpass, newpass;
                for (int i = 0; i < operat.size(); i++) {
                    id[i] = operat[i];
                }
                userID _id(id);
                if (allaccount.exist(_id) == 0 || now_user.total == -1)error("Invalid");
                operat = scanner.nextToken();
                Account tmp = now_user.get();
                block blk;
                if (!scanner.hasMoreTokens()) {
                    if (tmp.privilege < 7)error("Invalid");
                    tmp = allaccount.find(_id);
                    for (int i = 0; i < operat.size(); i++) {
                        tmp.password[i] = operat[i];
                    }
                    blk = allaccount.getblock(_id);
                    tmp.password[operat.size()] = '\0';
                    for (int i = 0; i < blk.size; i++) {
                        if (tmp.ID == blk.ele[i].ID) {
                            blk.ele[i] = tmp;
                            break;
                        }
                    }
                    allaccount.mywrite(blk.place, blk);
                    continue;
                }
                tmp = allaccount.find(_id);
                for (int i = 0; i < operat.size(); i++) {
                    oldpass[i] = operat[i];
                }
                if (tmp.password != oldpass)error("Invalid");
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    newpass[i] = operat[i];
                }
                blk = allaccount.getblock(_id);
                for (int i = 0; i < blk.size; i++) {
                    if (tmp.ID == blk.ele[i].ID) {
                        for (int k = 0; k < newpass.size(); k++) {
                            blk.ele[i].password[k] = newpass[k];
                        }
                        blk.ele[i].password[newpass.size()] = '\0';
                        break;
                    }
                }
                allaccount.mywrite(blk.place, blk);
            } else if (operat == "useradd") {
                Account tmp = now_user.get();
                if (tmp.privilege < 3) {
                    error("Invalid");
                }
                string id, pasword, nam;
                int priv;
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    id[i] = operat[i];
                }
                userID _id(id);
                if (allaccount.exist(_id)) {
                    error("Invalid");
                }
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    pasword[i] = operat[i];
                }
                operat = scanner.nextToken();
                priv = operat[0] - '0';
                if (priv >= tmp.privilege) error("Invalid");
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    nam[i] = operat[i];
                }
                Account new_(id, pasword, nam, priv);
                allaccount.insert(new_);
            } else if (operat == "delete") {
                Account tmp = now_user.get();
                if (tmp.privilege < 7) {
                    error("Invalid");
                }
                string id;
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    id[i - 1] = operat[i];
                }
                userID _id(id);
                if (allaccount.exist(_id) == 0 || tmp.ID == _id) {
                    error("Invalid");
                }
                allaccount.del(allaccount.find(_id));
            } else if (operat == "show") {
                if (scanner.hasMoreTokens() && scanner.nextToken() == "finance") {
                    //todo
                } else if (!(scanner.hasMoreTokens())) {
                    allbooks.showall();
                } else {
                    string s;
                    operat = scanner.nextToken();
                    if (operat[1] == 'I') {
                        int qua = 0;
                        if (operat.size() <= 6) {
                            error("Invalid");
                        }
                        for (int i = 6; i < operat.size(); i++) {
                            s[i - 6] = operat[i];
                        }
                        ISBN isb(s);
                        allbooks.find(isb);
                    } else if (operat[1] == 'n') {
                        if (operat.size()<=8)error("invalid");
                        for(int i=7;i<operat.size()-1;i++){
                            s[i-7]=operat[i];
                        }
                        Name nam(s);
                        allbooks.show_name(nam);
                    } else if (operat[1] == 'a') {
                        if (operat.size()<=10)error("invalid");
                        for(int i=9;i<operat.size()-1;i++){
                            s[i-9]=operat[i];
                        }
                        Author auth(s);
                        allbooks.show_author(auth);
                    } else if (operat[1] == 'k') {
                        if (operat.size()<=11)error("invalid");
                        for(int i=10;i<operat.size()-1;i++){
                            s[i-10]=operat[i];
                        }
                        Keyword key(s);
                        allbooks.show_keyword(key);
                    }
                }
            } else if (operat == "buy") {
                string is;
                int qua = 0;
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    is[i] = operat[i];
                }
                ISBN isb(is);
                Block tmp = allbooks.getblock(isb);
                operat = scanner.nextToken();
                if (operat[0] == '-') error("Invalid");
                for (int i = 0; i < operat.size(); i++) {
                    qua = qua * 10 + operat[i] - '0';
                }
                for (int k = 0; k < tmp.size; k++) {
                    if (tmp.ele[k].isbn == isb) {
                        tmp.ele[k].quantity -= qua;
                        if (tmp.ele[k].quantity < 0)error("Invalid");
                        cout << qua * tmp.ele[k].price << '\n';
                    }
                }
                allbooks.mywrite(tmp.place, tmp);

            } else if (operat == "select") {
                if (now_user.get().privilege < 3)error("Invalid");
                string is;
                operat = scanner.nextToken();
                for (int i = 0; i < operat.size(); i++) {
                    is[i] = operat[i];
                }
                ISBN isb(is);
                if (!allbooks.exist(isb)) {
                    Book book_;
                    book_.isbn = isb;
                    allbooks.insert(book_);
                }
                now_user.select(isb);
            } else if (operat == "modify") {
                bool iflag = 0, nflag = 0, aflag = 0, kflag = 0, pflag = 0;
                _block mid = now_user.getblock();
                if (!mid.selected||!scanner.hasMoreTokens())error("Invalid");
                Block tmp = allbooks.getblock(mid.isbn);
                string s;
                //int pri=0;
                while (scanner.hasMoreTokens()) {
                    operat = scanner.nextToken();
                    if (operat[1] == 'I') {
                        if (operat.size()<=6||iflag)error("invalid");
                        iflag = 1;
                        for (int i = 6; i < operat.size(); i++) {
                            s[i - 6] = operat[i];
                        }
                        ISBN isb(s);
                        if(isb==mid.isbn)error("invalid");
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                tmp.ele[i].isbn = mid.isbn = isb;
                            }
                        }
                    } else if (operat[1] == 'n') {
                        if (operat.size()<=8||nflag)error("invalid");
                        nflag = 1;
                        for (int i = 7; i < operat.size() - 1; i++) {
                            s[i - 7] = operat[i];
                        }
                        Name nam(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                tmp.ele[i].name = nam;
                            }
                        }
                    } else if (operat[1] == 'a') {
                        if (operat.size()<=10||aflag)error("invalid");
                        aflag = 1;
                        for (int i = 9; i < operat.size() - 1; i++) {
                            s[i - 9] = operat[i];
                        }
                        Author auth(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                tmp.ele[i].author = auth;
                            }
                        }
                    } else if (operat[1] == 'k') {
                        if (operat.size()<=11||kflag)error("invalid");
                        kflag = 1;
                        multiset<string>one;
                        set<string>two;
                        string word;
                        for (int i = 10; i < operat.size() - 1; i++) {
                            if(operat[i]=='|'||i==operat.size()-2){
                                one.insert(word);
                                word="";
                            }
                            word+=operat[i];
                            s[i - 10] = operat[i];
                        }
                        for(auto iter=one.begin();iter!=one.end();iter++){
                            two.insert(*iter);
                        }
                        if(one.size()!=two.size())error("Invalid");
                        Keyword key(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                tmp.ele[i].keyword = key;
                            }
                        }
                    } else {
                        if (operat.size()<=7||pflag)error("invalid");
                        pflag = 1;
                        for (int i = 7; i < operat.size(); i++) {
                            s[i - 7] = operat[i];
                        }
                        stringstream p(s);
                        double pri;
                        p >> pri;
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                tmp.ele[i].price = pri;
                            }
                        }
                    }
                    s = "";
                }
                now_user.mywrite(now_user.total, mid);
                allbooks.mywrite(tmp.place, tmp);
            } else if (operat == "import") {
                if(now_user.get().privilege<3)error("Invalid");
                _block tmp = now_user.getblock();
                if (!tmp.selected)error("Invalid");
                int qua = 0, cost;
                operat = scanner.nextToken();
                if (operat[0] == '-') error("Invalid");
                for (int i = 0; i < operat.size(); i++) {
                    qua = qua * 10 + operat[i] - '0';
                }
                operat = scanner.nextToken();
                if (operat[0] == '-') error("Invalid");
                for (int i = 0; i < operat.size(); i++) {
                    cost = cost * 10 + operat[i] - '0';
                }
                Block bok;
                bok = allbooks.getblock(tmp.isbn);
                for (int i = 0; i < bok.size; i++) {
                    if (bok.ele[i].isbn == tmp.isbn) {
                        bok.ele[i].quantity += qua;
                        bok.ele[i].total_cost = cost;
                        bok.ele[i].price = double(cost) / qua;
                    }
                }
                allbooks.mywrite(bok.place, bok);
            } else if (operat == "log") {

            }
        }
        catch (ErrorException &ex) {
            cout << ex.getMessage() << '\n';
        }
    }
    return 0;
}
