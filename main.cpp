
#include <set>
//#include"Book.h"
//#include"linklist_.h"
//#include"condition.h"
//#include"Account.h"
#include"diary.h"
#include "token_scanner.h"
//#include"condition.h"
//#include<sstream>

using namespace std;

int main() {
    string line, operat;
    all_Log detail;
    All_Books allbooks;
    All_Account allaccount;
    condition now_user;
    TokenScanner scanner;
    diaryGroup record;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    while (getline(cin, line)) {
        operat="";
        try {
            scanner.setInput(line);
            operat = scanner.nextToken();
            if (operat == "quit") {
                exit(0);
            } else if (operat == "exit") {
                exit(0);
            } else if (operat == "su") {
                string id, word,describe;
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
                describe=id+" su";
                log alog(describe);
                detail.add_logs(alog);
                now_user.login(account_);
            } else if (operat == "logout") {
                if (now_user.total == -1) {
                    error("Invalid");
                }
                string describe;
                int i=0;
                while(now_user.get().ID.userid[i]!='\0'){
                    describe[i]=now_user.get().ID.userid[i];
                    i++;
                }
                describe+=" logout";
                log alog(describe);
                detail.add_logs(alog);
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
                string describe;
                describe=id+" register";
                log alog(describe);
                detail.add_logs(alog);
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
                    int j=0;
                    while(tmp.password[j]!='\0'){
                        oldpass[j]=tmp.password[j];
                        j++;
                    }
                    for (int i = 0; i < operat.size(); i++) {
                        tmp.password[i] = newpass[i]=operat[i];
                    }
                    blk = allaccount.getblock(_id);
                    tmp.password[operat.size()] = '\0';
                    for (int i = 0; i < blk.size; i++) {
                        if (tmp.ID == blk.ele[i].ID) {
                            blk.ele[i] = tmp;
                            break;
                        }
                    }
                    string describe;
                    describe=id+" change password from "+oldpass+" to "+newpass;
                    log alog(describe);
                    detail.add_logs(alog);
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
                string describe;
                describe=id+" change password from "+oldpass+" to "+newpass;
                log alog(describe);
                detail.add_logs(alog);
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
                string the;
                int j=0;
                while(tmp.ID.userid[j]!='\0'){
                    the[j]=tmp.ID.userid[j];
                    j++;
                }
                string describe;
                describe=the+" create "+id;
                log alog(describe);
                detail.add_logs(alog);
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
                string describe,the;
                int j=0;
                while(tmp.ID.userid[j]!='\0'){
                    the[j]=tmp.ID.userid[j];
                    j++;
                }
                describe=the+" delete "+id;
                log alog(describe);
                detail.add_logs(alog);
                allaccount.del(allaccount.find(_id));
            } else if (operat == "show") {
                if (!(scanner.hasMoreTokens())) {
                    allbooks.showall();
                } else {
                    operat = scanner.nextToken();
                    if (operat == "finance") {
                        if (!scanner.hasMoreTokens()) {
                            record.show(record.total+1);
                        } else {
                            int count = 0;
                            operat = scanner.nextToken();
                            for (int i = 0; i < operat.size(); i++) {
                                count = count * 10 + operat[i] - '0';
                            }
                            if (count > record.total+1) error("Invalid");
                            record.show(count);
                        }
                    } else {
                        string s;
                        //operat = scanner.nextToken();
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
                            if (operat.size() <= 8)error("invalid");
                            for (int i = 7; i < operat.size() - 1; i++) {
                                s[i - 7] = operat[i];
                            }
                            Name nam(s);
                            allbooks.show_name(nam);
                        } else if (operat[1] == 'a') {
                            if (operat.size() <= 10)error("invalid");
                            for (int i = 9; i < operat.size() - 1; i++) {
                                s[i - 9] = operat[i];
                            }
                            Author auth(s);
                            allbooks.show_author(auth);
                        } else if (operat[1] == 'k') {
                            if (operat.size() <= 11)error("invalid");
                            for (int i = 10; i < operat.size() - 1; i++) {
                                if (operat[i] == '|')error("invalid");
                                s[i - 10] = operat[i];
                            }
                            Keyword key(s);
                            allbooks.show_keyword(key);
                        }
                    }
                }
            } else if (operat == "buy") {
                diary diary_;
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
                double spend;
                for (int i = 0; i < operat.size(); i++) {
                    qua = qua * 10 + operat[i] - '0';
                }
                for (int k = 0; k < tmp.size; k++) {
                    if (tmp.ele[k].isbn == isb) {
                        tmp.ele[k].quantity -= qua;
                        if (tmp.ele[k].quantity < 0)error("Invalid");
                        spend = qua * tmp.ele[k].price;
                        diary_.sum = spend;
                        cout << spend << '\n';
                    }
                }
                //diary_.ID = now_user.get().ID;
                diary_.postive = 1;
                //diary_.quantity = qua;
                record.add_log(diary_);
                string describe;
                describe="sell "+operat+" book "+is+" get "+ to_string(spend);
                log alog(describe);
                detail.add_logs(alog);
                allbooks.mywrite(tmp.place, tmp);

            } else if (operat == "select") {
                Account present=now_user.get();
                if (present.privilege < 3)error("Invalid");
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
                string describe,the;
                int j=0;
                while(present.ID.userid[j]!='\0'){
                    the[j]=present.ID.userid[j];
                    j++;
                }
                describe=the+" select book "+is;
                log alog(describe);
                now_user.select(isb);
            } else if (operat == "modify") {
                bool iflag = 0, nflag = 0, aflag = 0, kflag = 0, pflag = 0;
                _block mid = now_user.getblock();
                if (!mid.selected || !scanner.hasMoreTokens())error("Invalid");
                Block tmp = allbooks.getblock(mid.isbn);
                string s,describe,the,oth;
                Account now=now_user.get();
                //int pri=0;
                while (scanner.hasMoreTokens()) {
                    operat = scanner.nextToken();
                    if (operat[1] == 'I') {
                        if (operat.size() <= 6 || iflag)error("invalid");
                        iflag = 1;
                        for (int i = 6; i < operat.size(); i++) {
                            s[i - 6] = operat[i];
                        }
                        ISBN isb(s);
                        if (isb == mid.isbn)error("invalid");
                        int j=0;
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                while(tmp.ele[i].isbn.isbn_[j]!='\0'){
                                    the[j]=tmp.ele[i].isbn.isbn_[j];
                                }
                                tmp.ele[i].isbn = mid.isbn = isb;
                            }
                        }
                        describe+=the+" is modified to "+s+' ';
                    } else if (operat[1] == 'n') {
                        if (operat.size() <= 8 || nflag)error("invalid");
                        nflag = 1;
                        for (int i = 7; i < operat.size() - 1; i++) {
                            s[i - 7] = operat[i];
                        }
                        int j=0;
                        Name nam(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                while(tmp.ele[i].isbn.isbn_[j]!='\0'){
                                    the[j]=tmp.ele[i].isbn.isbn_[j];
                                }
                                j=0;
                                //string oth;
                                while(tmp.ele[i].name.name_[j]!='\0'){
                                    oth[i]=tmp.ele[i].name.name_[j];
                                }
                                tmp.ele[i].name = nam;
                            }
                        }
                        describe+="Name of "+the+" is changed from "+oth+" to "+s+' ';
                    } else if (operat[1] == 'a') {
                        if (operat.size() <= 10 || aflag)error("invalid");
                        aflag = 1;
                        for (int i = 9; i < operat.size() - 1; i++) {
                            s[i - 9] = operat[i];
                        }
                        int j=0;
                        Author auth(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                while(tmp.ele[i].isbn.isbn_[j]!='\0'){
                                    the[j]=tmp.ele[i].isbn.isbn_[j];
                                }
                                j=0;
                                while(tmp.ele[i].author.author_[j]!='\0'){
                                    oth[i]=tmp.ele[i].author.author_[j];
                                }
                                tmp.ele[i].author = auth;
                            }
                        }
                        describe+="Author of "+the+" is changed from "+oth+" to "+s+' ';
                    } else if (operat[1] == 'k') {
                        if (operat.size() <= 11 || kflag)error("invalid");
                        kflag = 1;
                        multiset<string> one;
                        set<string> two;
                        string word;
                        for (int i = 10; i < operat.size() - 1; i++) {
                            if (operat[i] == '|' || i == operat.size() - 2) {
                                one.insert(word);
                                word = "";
                            }
                            word += operat[i];
                            s[i - 10] = operat[i];
                        }
                        for (auto iter = one.begin(); iter != one.end(); iter++) {
                            two.insert(*iter);
                        }
                        if (one.size() != two.size())error("Invalid");
                        int j=0;
                        Keyword key(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                while(tmp.ele[i].isbn.isbn_[j]!='\0'){
                                    the[j]=tmp.ele[i].isbn.isbn_[j];
                                }
                                j=0;
                                while(tmp.ele[i].keyword.keyword_[j]!='\0'){
                                    oth[i]=tmp.ele[i].keyword.keyword_[j];
                                }
                                tmp.ele[i].keyword = key;
                            }
                        }
                        describe+="Keyword of "+the+" is changed from "+oth+" to "+s+' ';
                    } else {
                        if (operat.size() <= 7 || pflag)error("invalid");
                        pflag = 1;
                        for (int i = 7; i < operat.size(); i++) {
                            s[i - 7] = operat[i];
                        }
                        stringstream p(s);
                        double pri;
                        p >> pri;
                        int j=0;
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].isbn == mid.isbn) {
                                while(tmp.ele[i].isbn.isbn_[j]!='\0'){
                                    the[j]=tmp.ele[i].isbn.isbn_[j];
                                }
                                oth=to_string(tmp.ele[i].price);
                                tmp.ele[i].price = pri;
                            }
                        }
                        describe+="Price of "+the+" is changed from "+oth+" to "+s+' ';
                    }
                    oth="";
                    the="";
                    s = "";
                }
                now_user.mywrite(now_user.total, mid);
                allbooks.mywrite(tmp.place, tmp);
            } else if (operat == "import") {
                diary diary_;
                if (now_user.get().privilege < 3)error("Invalid");
                _block tmp = now_user.getblock();
                if (!tmp.selected)error("Invalid");
                int qua = 0;
                //string ss;
                operat = scanner.nextToken();
                if (operat[0] == '-') error("Invalid");
                for (int i = 0; i < operat.size(); i++) {
                    qua = qua * 10 + operat[i] - '0';
                }
                operat = scanner.nextToken();
                if (operat[0] == '-') error("Invalid");
//                for (int i = 0; i < operat.size(); i++) {
//                    cost = cost * 10 + operat[i] - '0';
//                }
                stringstream p(operat);
                double cost;
                p >> cost;
                Block bok;
                int j=0;
                string describe,the;
                bok = allbooks.getblock(tmp.isbn);
                for (int i = 0; i < bok.size; i++) {
                    if (bok.ele[i].isbn == tmp.isbn) {
                        while(bok.ele[i].isbn.isbn_[j]!='\0'){
                            the[j]=bok.ele[i].isbn.isbn_[j];
                        }
                        bok.ele[i].quantity += qua;
                        bok.ele[i].total_cost += cost;
                        bok.ele[i].price = bok.ele[i].quantity / bok.ele[i].total_cost;
                    }
                }
                describe="spend "+operat+" to get "+ to_string(qua)+" book "+the;
                //diary_.quantity = qua;
                diary_.postive = 0;
                //diary_.ID = now_user.get().ID;
                diary_.sum = cost;
                record.add_log(diary_);
                allbooks.mywrite(bok.place, bok);
            } else if (operat == "log") {
                if(now_user.get().privilege<7)error("Invalid");
                detail.show_logs();
            }
        }
        catch (ErrorException &ex) {
            cout << ex.getMessage() << '\n';
        }
    }
    return 0;
}
