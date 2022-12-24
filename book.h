#ifndef CODE_BOOK_HPP
#define CODE_BOOK_HPP
#include <iostream>
#include <fstream>
#include"error.h"
#include <cstring>
//#include "token_scanner.h"
//#include"diary.h"
//#include"condition.h"
using namespace std;
struct ISBN {
    char isbn_[22];

    ISBN(std::string &in) {
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

    friend ostream &operator<<(ostream &out, ISBN &the) {
        out << the.isbn_;
        return out;
    }
};

struct Name {
    char name_[62];

    Name(std::string &in) {
        for (int i = 0; i < in.size(); i++) {
            name_[i] = in[i];
        }
        name_[in.size()] = '\0';
    }

    Name() {};

    bool operator==(Name &other) {
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
        for (int i = 0; i < in.size(); i++) {
            author_[i] = in[i];
        }
        author_[in.size()] = '\0';
    }

    Author() {};

    bool operator==(Author &other) {
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
        for (int i = 0; i < in.size(); i++) {
            keyword_[i] = in[i];
        }
        keyword_[in.size()] = '\0';
    }

    Keyword() {};

    bool operator==(Keyword &other) {
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
    int quantity = 0;
    double price = 0;
    int total_cost = 0;

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
        out << the.isbn << '\t' << the.name << '\t' << the.author << '\t' << the.keyword << '\t' << the.price << '\t'
            << the.quantity << '\t';
        return out;
    }
};

struct Block {
    int next = -1;
    Book mini, maxi;
    int size = 0;
    Book ele[2001];
    int place;
};

class All_Books {

public:
    const int maxsize = 2000, minsize = 1000;
    int total = -1;
    fstream inout;
    string filename = "All_books";

    All_Books() {
//        filename=file;
        inout.open(filename);
        if (!inout) {
            Block tmp;
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


    ~All_Books() {
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.close();
    }

    void getin(int coord, Block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(Block) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&(node.next)), sizeof(node.next));
        inout.read(reinterpret_cast<char *>(&(node.mini)), sizeof(node.mini));
        inout.read(reinterpret_cast<char *>(&(node.maxi)), sizeof(node.maxi));
        inout.read(reinterpret_cast<char *>(&(node.size)), sizeof(node.size));
    }

    void myread(int coord, Block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(Block) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }

    void mywrite(int coord, Block &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekp(coord * sizeof(Block) + sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));
    }

    void split(int coord, Block &node) {
        total++;
        Block new_;
        for (int i = minsize; i < node.size; ++i) {
            new_.ele[i - minsize] = node.ele[i];
        }
        new_.size = minsize + 1;
        new_.next = node.next;
        new_.place=total;
        node.next = total;
        node.size = minsize;
        node.maxi = node.ele[node.size - 1];
        node.mini = node.ele[0];
        new_.maxi = new_.ele[node.size];
        new_.mini = new_.ele[0];
        mywrite(coord, node);
        mywrite(total, new_);
    }

    void insert_sort(int coord, const Book &ele) {
        Block new_;
        if (total == -1) {
            ++total;
            new_.place=0;
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

    void insert(const Book &ele) {
        Block new_;
        getin(0, new_);
        if (new_.size == 0 || ele < new_.mini) {
            insert_sort(0, ele);
            return;
        }
        Block nx;
        int i = 0;
        while (true) {
            if (new_.next == -1) {
                break;
            }
            getin(new_.next, nx);
            if (new_.mini <= ele && ele < nx.mini) {
                // 插入这里
                insert_sort(i, ele);
                return;
            }
            i = new_.next;
            new_ = nx;
        }
        insert_sort(i, ele);
    }

    void find(const ISBN &inde) {
        Block new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.isbn <= inde) && (inde <= new_.maxi.isbn)) {

                myread(i, new_);
                for (int k = 0; k < new_.size; ++k) {
                    if (new_.ele[k].isbn == inde) {
                        //fin = true;
                        std::cout << new_.ele[k];
                        cout << "\n";
                        return;
                    }
                }
            } else if (inde < new_.mini.isbn) {
                break;
            }
            i = new_.next;
        }

        cout << '\n';
        //return;

    }

    void merge(int coord, Block &node) {
        int nx1 = node.next;
        if (nx1 == -1) {
            mywrite(coord, node);
            return;
        }
        Block nx;
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

    void delete_sort(int coord, const Book &ele) {
        Block new_;
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

    void del(const Book &ele) {
        Block new_;
        int i = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if (new_.mini <= ele && ele <=new_.maxi ) {
                delete_sort(i, ele);
                break;
            }
            if (ele < new_.mini) {
                break;
            }
            i = new_.next;
        }
    }

    void showall() {
        Block new_;
        int i = 0;
        while (i != -1) {
            getin(i, new_);
            if(i==0&&new_.size==0){
                cout<<'\n';
                return;
            }
            for(int k=0;k<new_.size;k++){
                cout<<new_.ele[k]<<'\n';
            }
            i=new_.next;
        }
    };
    Block getblock(const ISBN inde) {
        Block new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.isbn <= inde) && (inde <= new_.maxi.isbn)) {
                myread(i, new_);
                return new_;
            } else if (inde < new_.mini.isbn) {
                break;
            }
            i = new_.next;
        }
        error("Invalid");
    }
    bool exist(ISBN &inde){
        Block new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            getin(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.isbn <= inde) && (inde <= new_.maxi.isbn)) {
                myread(i, new_);
                for (int k = 0; k < new_.size; ++k) {
                    if (new_.ele[k].isbn == inde) {
                        return true;
                    }
                }
            } else if (inde < new_.mini.isbn) {
                break;
            }
            i = new_.next;
        }
        return false;
    }

    void show_name(const Name& name_){

    };
    void show_author(Author& author_){

    };
    void show_keyword(Keyword & keyword_){

    }
//    void buy(TokenScanner &line, condition &status,
//             diaryGroup &Group);
//
//    void modify(TokenScanner &line, condition &status,
//                diaryGroup &Group);
//
//    void select(TokenScanner &line, condition &status,
//                diaryGroup &Group);
//
//    void import(TokenScanner &line, condition &status,
//                diaryGroup &Group);

};
#endif //CODE_BOOK_HPP
