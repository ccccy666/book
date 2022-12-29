
#include <set>
//#include"Book.h"
//#include"linklist_.h"
//#include"condition.h"
//#include"Account.h"
#include"diary-condition.h"
#include "token_scanner.h"
//#include"condition.h"
//#include<sstream>

using namespace std;

int main() {
    string line, operat;
    Bookstore Allbooks_;
    all_Log detail;
    //All_Books allbooks;
    All_Account allaccount;
    condition now_user;
    Token_scanner scanner;
    diaryGroup record;
//    scanner.ignoreWhitespace();
//    scanner.scanNumbers();
    while (getline(cin, line)) {
        operat = "";
        try {
            scanner.setInput(line);
            //cout<<scanner.nextToken();
            operat = scanner.nextToken();
            //cout<<scanner.line;
            //if(operat=="modify")cout<<operat;
            if (operat == "quit") {
                exit(0);
            } else if (operat == "exit") {
                exit(0);
            } else if (operat == "su") {
                string id, word, describe;
                Account account_;
                operat = scanner.nextToken();
                id = operat;
                userID _id(id);
                if (!allaccount.exist(_id)) {
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
                operat = scanner.nextToken();
                if(operat.size()>30)error("Invalid");
                word = operat;
                if (account_.password != word) {
                    error("Invalid");
                }
                describe = id + " su";
                log alog(describe);
                detail.add_logs(alog);
                now_user.login(account_);
            } else if (operat == "logout") {
                if (now_user.total == -1) {
                    error("Invalid");
                }
                string describe;
                int i = 0;
                Account ac = now_user.get();
                while (ac.ID.userid[i] != '\0') {
                    describe += ac.ID.userid[i];
                    i++;
                }
                describe += " logout";
                log alog(describe);
                detail.add_logs(alog);
                now_user.logout();
            } else if (operat == "register") {
                string id, pasword, nam;
                operat = scanner.nextToken();
                id = operat;

                userID _id(id);
                if (allaccount.exist(_id)) {
                    error("Invalid");
                }
                operat = scanner.nextToken();
                if(operat.size()>30)error("Invalid");
                pasword = operat;
                if(!scanner.hasMoreTokens())error("Invalid");
                operat = scanner.nextToken();
                if(operat.size()>30)error("Invalid");
                nam = operat;
                if(scanner.hasMoreTokens())error("Invalid");
                string describe;
                describe = id + " register";
                log alog(describe);
                detail.add_logs(alog);
                Account new_(id, pasword, nam, 1);
                allaccount.insert(new_);
            } else if (operat == "passwd") {
                //todo
                string id, oldpass, newpass;
                operat=scanner.nextToken();
                id = operat;
                userID _id(id);
                if (allaccount.exist(_id) == 0 || now_user.total == -1)error("Invalid");
                operat = scanner.nextToken();
                if(operat.size()>30)error("Invalid");
                Account tmp;
                block blk;
                if (!scanner.hasMoreTokens()) {
                    //if(now_user.total==-1)error("Invalid");
                    tmp = now_user.get();
                    if (tmp.privilege < 7)error("Invalid");
                    tmp = allaccount.find(_id);
                    //int j=0;
                    oldpass = tmp.password;
//                    while(tmp.password[j]!='\0'){
//                        oldpass+=tmp.password[j];
//                        j++;
//                    }
                    for (int i = 0; i < operat.size(); i++) {
                        tmp.password[i] = operat[i];
                        newpass += operat[i];
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
                    describe = id + " change password from " + oldpass + " to " + newpass;
                    log alog(describe);
                    detail.add_logs(alog);
                    allaccount.mywrite(blk.place, blk);
                    continue;
                }
                tmp = allaccount.find(_id);
                oldpass = operat;
                if (tmp.password != oldpass)error("Invalid");
                operat = scanner.nextToken();
                if(operat.size()>30)error("Invalid");
                newpass = operat;
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
                describe = id + " change password from " + oldpass + " to " + newpass;
                log alog(describe);
                detail.add_logs(alog);
                allaccount.mywrite(blk.place, blk);
            } else if (operat == "useradd") {
                Account tmp = now_user.get();
                if (tmp.privilege < 3) {
                    error("Invalid");
                }
                string id, pasword, nam;
                int priv = 0;
                operat = scanner.nextToken();
                id = operat;
                userID _id(id);
                if (allaccount.exist(_id)) {
                    error("Invalid");
                }
                operat = scanner.nextToken();
                if(operat.size()>30)error("Invalid");
                pasword = operat;
                if(!scanner.hasMoreTokens())error("Invalid");
                operat = scanner.nextToken();
                priv = operat[0] - '0';
                //cout << priv << ' ';
                //有错
                if(operat.size()>1||(priv!=1&&priv!=3&&priv!=7)||priv >= tmp.privilege)error("Invalid");
                if(!scanner.hasMoreTokens())error("Invalid");
                operat = scanner.nextToken();
                if(operat.size()>30)error("Invalid");
                //cout << operat << ' ';
                nam = operat;
                string the;
                int j = 0;
                while (tmp.ID.userid[j] != '\0') {
                    the += tmp.ID.userid[j];
                    j++;
                }
                string describe;
                describe = the + " create " + id;
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
                id = operat;
                userID _id(id);
                if (allaccount.exist(_id) == 0 || now_user.exist(_id)) {
                    error("Invalid");
                }
                string describe, the;
                //int j=0;
                the = tmp.ID.userid;
//                while(tmp.ID.userid[j]!='\0'){
//                    the[j]=tmp.ID.userid[j];
//                    j++;
//                }
                describe = the + " delete " + id;
                log alog(describe);
                detail.add_logs(alog);
                allaccount.del(allaccount.find(_id));
            } else if (operat == "show") {
                if(now_user.total<0)error("Invalid");
                if (!(scanner.hasMoreTokens())) {
                    Allbooks_.showall();
                    //allbooks.showall();
                } else {
                    operat = scanner.nextToken();
                    if (operat == "finance") {
                        if(now_user.get().privilege<7)error("Invalid");
                        if (!scanner.hasMoreTokens()) {
                            record.show(record.total + 1);
                        } else {
                            long long count = 0;
                            operat = scanner.nextToken();
                            for (int i = 0; i < operat.size(); i++) {
                                count = count * 10 + operat[i] - '0';
                            }
                            if (count > record.total + 1) error("Invalid");
                            record.show(count);
                        }
                    } else {
                        string s;
                        //operat = scanner.nextToken();
                        if (operat[1] == 'I') {
                            //int qua = 0;
                            if (operat.size() <= 6) {
                                error("Invalid");
                            }
                            for (int i = 6; i < operat.size(); i++) {
                                s += operat[i];
                            }
                            if(s.size()>20)error("Invalid");
                            ISBN isb(s);
                            Allbooks_.find(isb);
                            //allbooks.find(isb);
                        } else if (operat[1] == 'n') {
                            if (operat.size() <= 8)error("invalid");
                            for (int i = 7; i < operat.size() - 1; i++) {
                                s += operat[i];
                            }
                            if(s.size()>60)error("Invalid");
                            Name nam(s);
                            Allbooks_.show_name(nam);
                            //allbooks.show_name(nam);
                        } else if (operat[1] == 'a') {
                            if (operat.size() <= 10)error("invalid");
                            for (int i = 9; i < operat.size() - 1; i++) {
                                s += operat[i];
                            }
                            if(s.size()>60)error("Invalid");
                            Author auth(s);
                            Allbooks_.show_author(auth);
                            //allbooks.show_author(auth);
                        } else if (operat[1] == 'k') {
                            if (operat.size() <= 11)error("invalid");
                            for (int i = 10; i < operat.size() - 1; i++) {
                                if (operat[i] == '|')error("invalid");
                                s += operat[i];
                            }
                            //cout<<s;
                            if(s.size()>60)error("Invalid");
                            Keyword key(s);
                            Allbooks_.show_keyword(key);
                            //allbooks.show_keyword(key);
                        }
                    }
                }
            } else if (operat == "buy") {
                if(now_user.total<0)error("Invalid");
                diary diary_;
                string is;
                long long qua = 0;
                operat = scanner.nextToken();
                is = operat;
                ISBN isb(is);
                if(!Allbooks_.exist(isb))error("Invalid");
                block__<ISBN,Book>tmp=Allbooks_.getblock(isb);
                //Block tmp = allbooks.getblock(isb);
                operat = scanner.nextToken();
                if (operat[0] == '-'||operat=="0") error("Invalid");
                double spend;
                if(operat.size()>10)error("Invalid");
                for (int i = 0; i < operat.size(); i++) {
                    qua = qua * 10 + operat[i] - '0';
                }
                for (int k = 0; k < tmp.size; k++) {
                    if (tmp.ele[k].index == isb) {
                        tmp.ele[k].valu.quantity -= qua;
                        if (tmp.ele[k].valu.quantity < 0)error("Invalid");
                        spend = qua * tmp.ele[k].valu.price;
                        string ss1= to_string(spend),s1= to_string(int(spend));
                        for(int g=0;g<s1.size()+3;g++){
                            cout<<ss1[g];
                        }
                        cout<<'\n';
                        diary_.sum = spend;
                        //cout << spend << '\n';
                    }
                }
                //diary_.ID = now_user.get().ID;
                diary_.postive = 1;
                //diary_.quantity = qua;
                record.add_log(diary_);
                string describe;
                describe = "sell " + operat + " book " + is + " get " + to_string(spend);
                log alog(describe);
                detail.add_logs(alog);
                Allbooks_.list.mywrite(tmp.place,tmp);
                //allbooks.mywrite(tmp.place, tmp);

            } else if (operat == "select") {
                Account present = now_user.get();
                if (present.privilege < 3)error("Invalid");
                string is;
                operat = scanner.nextToken();
                is = operat;
                ISBN isb(is);
                if (!Allbooks_.exist(isb)) {
                    Book book_;
                    //book_.isbn = isb;
                    point<ISBN,Book>tm;
                    tm.index=isb;
                    tm.valu.isbn=isb;
                    Allbooks_.insert(tm);
                    //allbooks.insert(book_);
                }
                string describe, the = present.ID.userid;
//                int j=0;
//                while(present.ID.userid[j]!='\0'){
//                    the[j]=present.ID.userid[j];
//                    j++;
//                }
                describe = the + " select book " + is;
                log alog(describe);
                now_user.select(isb);
            } else if (operat == "modify") {
                //cout<<operat;
                bool iflag = 0, nflag = 0, aflag = 0, kflag = 0, pflag = 0;
                _block mid = now_user.getblock();
                if(mid.account.privilege<3)error("Invalid");
                if (!mid.selected || !scanner.hasMoreTokens())error("Invalid");
                //cout<<mid.isbn<<' ';
                block__<ISBN,Book>tmp=Allbooks_.getblock(mid.isbn);
                //cout<<1;
                //Block tmp = allbooks.getblock(mid.isbn);
                //cout<<1;
                string s, describe, the, oth;
                Account now = now_user.get();
                //if(now.privilege<3)error("Invalid");
                //int pri=0;
                while (scanner.hasMoreTokens()) {
                    operat = scanner.nextToken();
                    //cout<<operat;
                    if (operat[1] == 'I') {
                        if (operat.size() <= 6 || iflag)error("invalid");
                        iflag = 1;
                        for (int i = 6; i < operat.size(); i++) {
                            s += operat[i];
                        }
                        ISBN isb(s);
                        if(Allbooks_.exist(isb))error("Invalid");
                        if (isb == mid.isbn||s.size()>20)error("invalid");
                        //int j = 0;
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].index == mid.isbn) {
                                the=tmp.ele[i].valu.isbn.isbn_;
                                for(int p=0;p<now_user.total;p++){
                                    _block un;
                                    now_user.myread(p,un);
                                    if(un.isbn==mid.isbn){
                                        un.isbn=isb;
                                        now_user.mywrite(p,un);
                                    }
                                }
//                                while (tmp.ele[i].valu.isbn.isbn_[j] != '\0') {
//                                    the[j] = tmp.ele[i].isbn.isbn_[j];
//                                }
                                tmp.ele[i].index=tmp.ele[i].valu.isbn = mid.isbn = isb;
                            }
                        }

                        tmp.mini=tmp.ele[0];
                        tmp.maxi=tmp.ele[tmp.size-1];
                        describe += the + " is modified to " + s + ' ';
                    } else if (operat[1] == 'n') {
                        if (operat.size() <= 8 || nflag)error("invalid");
                        nflag = 1;
                        for (int i = 7; i < operat.size() - 1; i++) {
                            s += operat[i];
                        }
                        //int j=0;
                        //cout<<s;
                        //if(s=="aPerez")cout<<"!!!!!!!!!!!!";
                        Name nam(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].index == mid.isbn) {
                                the = tmp.ele[i].valu.isbn.isbn_;
//                                while(tmp.ele[i].isbn.isbn_[j]!='\0'){
//                                    the[j]=tmp.ele[i].isbn.isbn_[j];
//                                }
                                //j=0;
                                //string oth;
                                oth = tmp.ele[i].valu.name.name_;
//                                while(tmp.ele[i].name.name_[j]!='\0'){
//                                    oth[i]=tmp.ele[i].name.name_[j];
//                                }
                                tmp.ele[i].valu.name = nam;
                            }
                        }
                        describe += "Name of " + the + " is changed from " + oth + " to " + s + ' ';
                    } else if (operat[1] == 'a') {
                        if (operat.size() <= 10 || aflag)error("invalid");
                        aflag = 1;
                        for (int i = 9; i < operat.size() - 1; i++) {
                            s += operat[i];
                        }
                        //int j=0;
                        Author auth(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].index == mid.isbn) {
                                the = tmp.ele[i].valu.isbn.isbn_;
//                                while(tmp.ele[i].is.bn.isbn_[j]!='\0'){
//                                    the[j]=tmp.ele[i].isbn.isbn_[j];
//                                }
//                                j=0;
                                oth = tmp.ele[i].valu.author.author_;
//                                while (tmp.ele[i].author.author_[j] != '\0') {
//                                    oth[i] = tmp.ele[i].author.author_[j];
//                                }
                                tmp.ele[i].valu.author = auth;
                            }
                        }
                        describe += "Author of " + the + " is changed from " + oth + " to " + s + ' ';
                    } else if (operat[1] == 'k') {
                        if (operat.size() <= 11 || kflag)error("invalid");
                        kflag = 1;
                        multiset<string> one;
                        set<string> two;
                        string word;
                        for (int i = 10; i < operat.size() - 1; i++) {
                            if (operat[i] == '|' || i == operat.size() - 2) {
                                if(operat[i+1]=='|'||operat[operat.size() - 2]=='|')error("Invalid");
                                if(i==operat.size()-2){
                                    word += operat[i];
                                }
                                one.insert(word);
                                word = "";
                            }
                            word += operat[i];
                            s+= operat[i];
                        }
                        for (auto iter = one.begin(); iter != one.end(); iter++) {
                            two.insert(*iter);
                        }
                        if (one.size() != two.size())error("Invalid");
                        //int j = 0;
                        Keyword key(s);
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].index == mid.isbn) {
                                the=tmp.ele[i].valu.isbn.isbn_;
//                                while (tmp.ele[i].isbn.isbn_[j] != '\0') {
//                                    the[j] = tmp.ele[i].isbn.isbn_[j];
//                                }
                                //j = 0;
                                oth=tmp.ele[i].valu.keyword.keyword_;
//                                while (tmp.ele[i].keyword.keyword_[j] != '\0') {
//                                    oth[i] = tmp.ele[i].keyword.keyword_[j];
//                                }
                                tmp.ele[i].valu.keyword = key;
                            }
                        }
                        describe += "Keyword of " + the + " is changed from " + oth + " to " + s + ' ';
                    } else {
                        if (operat.size() <= 7 || pflag)error("invalid");
                        //cout<<operat;
                        pflag = 1;
                        for (int i = 7; i < operat.size(); i++) {
                            s += operat[i];
                        }
                        if(s.size()>13)error("Invalid");
                        //cout<<s<<' ';
                        stringstream p(s);
                        double pri;
                        p >> pri;

                        int j = 0;
                        for (int i = 0; i < tmp.size; i++) {
                            if (tmp.ele[i].index == mid.isbn) {
                                the=tmp.ele[i].valu.isbn.isbn_;
//                                while (tmp.ele[i].isbn.isbn_[j] != '\0') {
//                                    the[j] = tmp.ele[i].isbn.isbn_[j];
//                                }
                                oth = to_string(tmp.ele[i].valu.price);
                                tmp.ele[i].valu.price = pri;
                            }
                        }
                        describe += "Price of " + the + " is changed from " + oth + " to " + s + ' ';
                    }
                    oth = "";
                    the = "";
                    s = "";
                }
                now_user.mywrite(now_user.total, mid);
                Allbooks_.list.mywrite(tmp.place,tmp);
                //allbooks.mywrite(tmp.place, tmp);
            } else if (operat == "import") {
                diary diary_;
                if (now_user.get().privilege < 3)error("Invalid");
                _block tmp = now_user.getblock();
                if (!tmp.selected)error("Invalid");
                long long qua = 0;
                operat = scanner.nextToken();
                if (operat[0] == '-'||operat.size()>10) error("Invalid");
                for (int i = 0; i < operat.size(); i++) {
                    if(operat[i]>'9'||operat[i]<'0')error("Invalid");
                    qua = qua * 10 + operat[i] - '0';
                }
                operat = scanner.nextToken();
                if (operat[0] == '-'||operat.size()>13) error("Invalid");
//                for (int i = 0; i < operat.size(); i++) {
//                    if(operat[i]>'9'||operat[i]<'0'||operat[i]!='.')error("Invalid");
//                }
                stringstream p(operat);
                double cost;
                p >> cost;
                block__<ISBN,Book> bok=Allbooks_.getblock(tmp.isbn);
                //int j = 0;
                string describe, the;

                //bok = allbooks.getblock(tmp.isbn);
                for (int i = 0; i < bok.size; i++) {
                    if (bok.ele[i].index == tmp.isbn) {
                        the=bok.ele[i].valu.isbn.isbn_;
//                        while (bok.ele[i].isbn.isbn_[j] != '\0') {
//                            the[j] = bok.ele[i].isbn.isbn_[j];
//                        }
                        bok.ele[i].valu.quantity += qua;
                        bok.ele[i].valu.total_cost += cost;
                        //bok.ele[i].valu.price = bok.ele[i].valu.quantity / bok.ele[i].valu.total_cost;
                    }
                }
                describe = "spend " + operat + " to get " + to_string(qua) + " book " + the;
                //diary_.quantity = qua;
                diary_.postive = 0;
                //diary_.ID = now_user.get().ID;
                diary_.sum = cost;
                record.add_log(diary_);
                Allbooks_.list.mywrite(bok.place,bok);
                //allbooks.mywrite(bok.place, bok);
            } else if (operat == "log") {
                if (now_user.get().privilege < 7)error("Invalid");
                detail.show_logs();
            } else if (operat != " ")error("Invalid");
        }
        catch (ErrorException &ex) {
            cout << ex.getMessage() << '\n';
        }
    }
    return 0;
}
