#ifndef CODE_BOOK_HPP
#define CODE_BOOK_HPP
#include <iostream>
//#include <fstream>
#include"error.h"
//#include <cstring>
#include<vector>
#include"linklist.h"

using namespace std;
struct ISBN {
    char isbn_[22];

    ISBN(std::string &in) {
        if(in.size()>20)error("Invalid");
        for (int i = 0; i < in.size(); i++) {
            isbn_[i] = in[i];
        }
        isbn_[in.size()] = '\0';
    }

    ISBN() {};

    bool operator==(const ISBN &other) const {
        return (!strcmp(isbn_, other.isbn_));
    }

    bool operator<(const ISBN &other) const {
        return (strcmp(isbn_, other.isbn_) < 0);
    }

    bool operator<=(const ISBN &other) const {
        return ((strcmp(isbn_, other.isbn_) < 0) || (!strcmp(isbn_, other.isbn_)));
    }

    friend ostream &operator<<(ostream &out,const ISBN &the) {
        out << the.isbn_;
        return out;
    }
};

struct Name {
    char name_[62];

    Name(std::string &in) {
        if(in.size()>60)error("Invalid");
        for (int i = 0; i < in.size(); i++) {
            name_[i] = in[i];
        }
        name_[in.size()] = '\0';
    }

    Name() {name_[0]='\0';};

    bool operator==(const Name &other) const{
        return (!strcmp(name_, other.name_));
    }

    bool operator<(Name &other) {
        return (strcmp(name_, other.name_) < 0);
    }

    friend ostream &operator<<(ostream &out, Name &the) {
        out << the.name_;
        return out;
    }
};

struct Author {
    char author_[62];

    Author(std::string &in) {
        if(in.size()>60)error("Invalid");

        for (int i = 0; i < in.size(); i++) {
            author_[i] = in[i];
        }
        author_[in.size()] = '\0';
    }

    Author() {author_[0]='\0';};

    bool operator==(Author &other) const{
        return (!strcmp(author_, other.author_));
    }

    bool operator<(Author &other) {
        return (strcmp(author_, other.author_) < 0);
    }

    friend ostream &operator<<(ostream &out, Author &the) {
        out << the.author_;
        return out;
    }
};

struct Keyword {
    char keyword_[62];

    Keyword(std::string &in) {
        if(in.size()>60)error("Invalid");

        for (int i = 0; i < in.size(); i++) {
            keyword_[i] = in[i];
        }
        keyword_[in.size()] = '\0';
    }

    Keyword() {keyword_[0]='\0';};

    bool operator==(Keyword &other) const{
        return (!strcmp(keyword_, other.keyword_));
    }

    bool operator<(Keyword &other) {
        return (strcmp(keyword_, other.keyword_) < 0);
    }

    friend ostream &operator<<(ostream &out, Keyword &the) {
        out << the.keyword_;
        return out;
    }
};

class Book {
public:
    ISBN isbn;
    Name name;
    Author author;
    Keyword keyword;
    long long quantity = 0;
    double price = 0;
    double total_cost = 0;

    bool operator<(const Book &other) const {
        return isbn < other.isbn;
    }

    bool operator==(const Book &other) const {
        return isbn == other.isbn;
    }

    bool operator<=(const Book &other) const {
        return (isbn < other.isbn) || (isbn == other.isbn);
    }

    Book(std::string isbn__, std::string name__, std::string author__, std::string keyword__, int quan,
         double pri, double cost) : isbn(isbn__), name(name__), author(author__), keyword(keyword__) {
        quantity = quan;
        price = pri;
        total_cost = cost;
    };

    Book() {};

    ~Book() {};

    friend ostream &operator<<(ostream &out, Book &the) {
        int m=int(the.price);//n=int(the.total_cost);
        string ss1= to_string(the.price);//ss2= to_string(the.quantity);
        string s1=to_string(m);//s2= to_string(n);
        //cout<<the.price<<' ';
        //cout<<ss1<<' '<<s1<<' ';
        out << the.isbn << '\t' << the.name << '\t' << the.author << '\t' << the.keyword << '\t';
        if(ss1.size()>=s1.size()+3){
            //out.p(s1.size()+2)
            for(int i=0;i<s1.size()+3;i++){
                out<<ss1[i];
            }
            out << '\t';
        }else if(ss1.size()==s1.size()+2){
            out<<ss1 <<'0'<< '\t';
        }else if(ss1.size()==s1.size()){
            out<<ss1 <<".00"<< '\t';
        }
        out<<the.quantity;
//        if(ss2.size()>=s2.size()+3){
//            out.precision(s2.size()+2);
//            out<<the.total_cost << '\t';
//        }else if(ss2.size()==s2.size()+2){
//            out<<the.total_cost <<'0'<< '\t';
//        }else{
//            out<<the.total_cost <<".00"<< '\t';
//        }
        return out;
    }
};


class Bookstore{
public:
    linklist_<ISBN,Book>list;
    Bookstore():list(" Books"){

    }
    ~Bookstore(){}
    void insert (const point<ISBN,Book> &inde){
        list.insert(inde);
    }
    block__<ISBN,Book> getblock(const ISBN &inde){
        //cout<<inde;
        return list.getblock(inde);
    }
    bool exist(const ISBN& inde){
        return list.exist(inde);
    }
    void find(const ISBN &inde){
        list.find(inde);
    }
    void showall(){
        block__<ISBN,Book>tmp;
        int i=0;
        while(i!=-1){
            list.myread(i,tmp);
            if(i==0&&tmp.size==0){
                cout<<'\n';
                return;
            }
            for(int k=0;k<tmp.size;k++){
                cout<<tmp.ele[k].valu<<'\n';
            }
            i=tmp.next;
        }
    }
    void show_name(const Name& name_){
        block__<ISBN,Book> new_;
        bool get=0;
        int i=0;
        while(i!=-1){
            list.myread(i,new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            //list.myread(i, new_);
            for (int k = 0; k < new_.size; ++k) {
                if(new_.ele[k].valu.name==name_){
                    get=1;
                    cout<<new_.ele[k].valu<<'\n';
                }
            }
            i=new_.next;
        }
        if(!get)cout<<'\n';
    };
    void show_author(Author& author_){
        block__<ISBN,Book> new_;
        bool get=0;
        int i=0;
        while(i!=-1){
            list.myread(i,new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            //list.myread(i, new_);
            for (int k = 0; k < new_.size; ++k) {
                if(new_.ele[k].valu.author==author_){
                    get=1;
                    cout<<new_.ele[k].valu<<'\n';
                }
            }
            i=new_.next;
        }
        if(!get)cout<<'\n';
    };
    void show_keyword(Keyword & keyword_){
        block__<ISBN,Book> new_;
        bool get=0;
        int i=0,j=0;
        vector<string> words;
        string word;
        while(i!=-1){
            list.myread(i,new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            //myread(i, new_);
            for (int k = 0; k < new_.size; ++k) {
                //cout<<new_.ele[k].valu.keyword<<' ';
                while(new_.ele[k].valu.keyword.keyword_[j]!='\0'){
                    if(new_.ele[k].valu.keyword.keyword_[j]=='|'||new_.ele[k].valu.keyword.keyword_[j+1]=='\0'){
                        if(new_.ele[k].valu.keyword.keyword_[j+1]=='\0'){
                            word+=new_.ele[k].valu.keyword.keyword_[j];
                        }
                        words.push_back(word);
                        word="";
                        j++;
                        continue;
                    }
                    word+=new_.ele[k].valu.keyword.keyword_[j];
                    j++;
                }
                //cout<<words[0]<<' '<<word[1];
                for(auto iter=words.begin();iter!=words.end();iter++){
                    //cout<<*iter<<' ';

                    Keyword kk(*iter);
                    if(keyword_==kk){
                        //cout<<111;
                        get=1;
                        cout<<new_.ele[k].valu<<'\n';
                    }
                }
                words.clear();
                j=0;
            }
            i=new_.next;
        }
        if(!get)cout<<'\n';
    }
};

#endif //CODE_BOOK_HPP
