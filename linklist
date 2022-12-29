#ifndef CODE_LINKLIST_HPP
#define CODE_LINKLIST_HPP
///////////////////
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

//class myString {
//private:
//    char s[70];
//public:
//    myString() {};
//
//    myString(char *p) {
//        int length = strlen(p);
//        if (length > 64) {
//            exit(1);
//        }
//        for (int i = 0; i < length; ++i) {
//            s[i] = p[i];
//        }
//        s[length] = '\0';
//    }
//
//    ~myString() {};
//    friend bool operator==(const myString &x, const myString &y) {
//        return (!strcmp(x.s, y.s));
//    }
//    friend bool operator<(const myString &x, const myString &y) {
//        return (strcmp(x.s, y.s) < 0);
//    }
//
//    friend bool operator<=(const myString &x, const myString &y) {
//        return (x < y) || (x == y);
//    }
//
//    friend std::ostream &operator<<(std::ostream &x, const myString &y) {
//        x << y.s;
//        return x;
//    };
//};
template <class t,class T>
class point {
public:
    t index;
    T valu;
    point() {};
    point(const t &a, const int &b) {
        index = a;
        valu = b;
    }
    friend bool operator==(const point<t,T> &a, const point<t,T> &b) {
        return (a.index == b.index );
    }

    friend bool operator<(const point<t,T> &a, const point<t,T> &b) {
        return ((a.index<b.index));
    }

    friend bool operator>(const point<t,T> &a, const point<t,T> &b) {
        return (!(a == b) && (!(a < b)));
    }
    friend bool operator>=(const point<t,T> &a, const point<t,T> &b) {
        return !(a < b);
    }
    friend bool operator<=(const point<t,T> &a, const point<t,T> &b) {
        return !(a > b);
    }
};
template<class t,class T>
struct block__{
    int next = -1;
    point<t,T> mini, maxi;
    int size = 0;
    point<t,T> ele[2001];
    int place;
};
template <class t,class T>
class linklist_ {
public:
    
    const int maxsize = 2000, minsize = 1000;
    int total = -1;
    fstream inout;
    string filename;

//    void print(){
//        block__<t,T> tmp;
//        for(int i=0;i<=total;i++){
//            inout.seekg(i*sizeof(block__<t,T>));
//            inout.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
//            cout<<tmp.ele[0].str<<' '<<tmp.ele[0].val<<'s'<<'\n';
//            cout<<tmp.ele[1].str<<' '<<tmp.ele[1].val<<'\n';
//        }
//    }
linklist_(){

}
    linklist_(string name):filename(name) {
        inout.open(filename);
        if (!inout) {
            block__<t,T> tmp;
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

    ~linklist_() {
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.close();
    }
    void myrea(int coord, block__<t,T> &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(block__<t,T>) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&(node.next)), sizeof(node.next));
        inout.read(reinterpret_cast<char *>(&(node.mini)), sizeof(node.mini));
        inout.read(reinterpret_cast<char *>(&(node.maxi)), sizeof(node.maxi));
        inout.read(reinterpret_cast<char *>(&(node.size)), sizeof(node.size));
    }
    void myread(int coord, block__<t,T> &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(block__<t,T>) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }
    void mywrite(int coord, block__<t,T> &node) {
        if (coord < 0) {
            exit(1);
        }
        //cout<<node.size;
        inout.seekp(coord * sizeof(block__<t,T>) + sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));
//        block__<t,T>tp;
//        myread(0,tp);
//        cout<<tp.size;
    }

    void split(int coord, block__<t,T> &node) {
        total++;
        block__<t,T> new_;
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

    void insert_sort(int coord, const point<t,T> &ele) {
        block__<t,T> new_;
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

    void insert(const point<t,T> &ele) {
        block__<t,T> new_;
        myread(0, new_);
        if (new_.size == 0 || ele < new_.mini) {
            insert_sort(0, ele);
            return;
        }
        block__<t,T> nx;
        int i = 0;
        while (true) {
            if (new_.next == -1) {
                break;
            }
            myread(new_.next, nx);
            if (ele >= new_.mini && ele < nx.mini) {
                insert_sort(i, ele);
                return;
            }
            i = new_.next;
            new_ = nx;
        }
        insert_sort(i, ele);
    }
    block__<t,T> getblock(const t &inde){
        block__<t,T> new_;
        int i = 0;
        while (i != -1) {
            myread(i, new_);
//            cout<<new_.ele[0].index<<' ';
//            cout<<inde<<'\n';
            //if(new_.ele[0].index==inde)cout<<"right";
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.index <= inde) && (inde <= new_.maxi.index)) {
                //cout<<"awsl";
                return new_;
            } else if (inde < new_.mini.index) {
                break;
            }
            i = new_.next;
        }

        //cout<<"6666666";
        error("Invalid");

};
    bool exist(const t &inde){
        block__<t,T> new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            myread(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.index <= inde) && (inde <= new_.maxi.index)) {
                myread(i, new_);
                for (int k = 0; k < new_.size; ++k) {
                    if (new_.ele[k].index == inde) {
                        //fin = true;
                        //std::cout << new_.ele[k].valu << " ";
                        return true;
                    }
                }
            } else if (inde < new_.mini.index) {
                break;
            }
            i = new_.next;
        }
        return false;
}
    void find(const t &inde) {
        block__<t,T> new_;
        int i = 0;
        //bool fin = 0;
        while (i != -1) {
            myread(i, new_);
            if (new_.size == 0) {
                i = new_.next;
                continue;
            }
            if ((new_.mini.index <= inde) && (inde <= new_.maxi.index)) {
                myread(i, new_);
                for (int k = 0; k < new_.size; ++k) {
                    if (new_.ele[k].index == inde) {
                        //fin = true;
                        std::cout << new_.ele[k].valu;
                    }
                }
            } else if (inde < new_.mini.index) {
                break;
            }
            i = new_.next;
        }
        
        cout << "\n";

    }
    void merge(int coord, block__<t,T> &node) {
        int nx1 = node.next;
        if (nx1 == -1) {
            mywrite(coord, node);
            return;
        }
        block__<t,T> nx;
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
    void delete_sort(int coord, const point<t,T> &ele) {
        block__<t,T> new_;
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

    void del(const point<t,T> &ele) {
        block__<t,T> new_;
        int i = 0;
        while (i != -1) {
            myread(i, new_);
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

};

#endif //CODE_LINKLIST_HPP
