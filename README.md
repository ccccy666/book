# book
# **书店管理系统** 

#### _陈轶凡_

### **程序功能概述**:

完成一个书店管理系统，基于用户名的不同权限等级向店家和顾客提供图书检索与购买服务,
功能包括：

#### _1. 账户_

(1)每个账户应该有用户ID，用户名，密码，权限等级，登录状态；

(2)每个账户应该支持创建账户，注册帐户，注销账户，登录帐户，修改密码，删除账户

(3)支持多个账户嵌套登录，并以最后一个账户权限为准

(4)初始创建超级管理员账户，程序结束时账号退出

#### _2. 图书_

(1)图书信息 : ISBN、图书名、作者名、关键词（可以有多个）、 
购买数量、图书单价、交易总额

(2)基于 ISBN /书名/作者名/关键词检索图书

(3)购买指定图书

(4)修改图书信息

(5)以一定总额购进指定数量的指定图书

#### _3.日志系统_

(1)记录交易笔数

(2)查询财务记录

(3)生成日志

#### 4.交互功能

(1)合法指令为ASCII字符,最长单个指令为1024字节，内部被空格分隔，
以换行区分指令。允许的空白符仅为空格，多个连续空格效果与一个空格等价
，行首行末允许出现多余空格

(2)指令中第一个部分必须为指令关键词，指令中关键词部分必须与指令格式完全匹配


(3) 

[x] 表示一串有特定限制的用户自定义字符串

( x ) ? 表示此处可以出现 0 或 1 次 x

( a | b | c ) 表示此处仅能出现 a, b, c 中其一

quit 和 exit 指令功能为正常退出系统

(4)  

`````
# 基础指令
quit
exit

# 账户系统指令
su [User-ID] ([Password])?
logout
register [User-ID] [Password] [User-Name]
passwd [User-ID] ([Old-Password])? [New-Password]
useradd [User-ID] [Password] [Priority] [User-Name]
delete [User-ID]

# 图书系统指令
show (-ISBN=[ISBN] | -name="[Book-Name]" | -author="[Author]" | -keyword="[Keyword]")?
buy [ISBN] [Quantity]
select [ISBN]
modify (-ISBN=[ISBN] | -name="[Book-Name]" | -author="[Author]" | -keyword="[Keyword]" | -price=[Price])+
import [Quantity] [Total-Cost]

# 日志系统指令
report myself
show finance ([Time])?
report finance
report employee
log
`````

(5)输入一条指令后，
如果合法则执行对应操作，
输出操作结果；
指令非法或操作失败则输出 Invalid\n

仅有空白符的指令合法且无输出内容

(6)
输入指令对应的输出内容非空，则结尾有 \n 字符；

输出内容为空则不输出任何字符



### **主体逻辑说明**：

#### 1.
main函数中通过循环读入控制台的输入并进行处理

#### 2.
main函数中使用try_catch来处理错误信息

#### 3.
通过文件读写读入对应数据，并将修改存储在对应文件中

#### 4.
用不同的类来存储各种信息

### 代码文件结构：

#### 1.
函数包含：main 函数、输入分析函数、普通指令处理函数、账户指令处理函数、
图书指令处理函数、日志处理函数、错误处理函数。

#### 2.
类包含：账户类、图书类、日志类、登陆状态类。

#### 3.
文件主要包含：账户文件、图书文件、日志文件等。


### 各个类的接口及成员说明：

#### 1.token_scanner类
`````
class token_scanner{

public:

std::string part;

token_scanner();

token_scanner(std::string &input);

~token_scanner();

bool has_more_token();

string next_token();

//todo
};
`````

#### 2.account类
````
#include <iostream>

#include <fstream>

#include "linklist_.h"

#include "token_scanner.h"

struct userID{

std::string userid;

}

class account{

public:

int privilege;

string password;

string username;

userID ID;

bool condition;

account();

account(std::string ID_,std::string pass,std::string name,int privi);

~account();

void change_password(std::string new_pass);
};

class all_account{

public:

linklist_<userID,int> id_index=linklist_<UserID,int>("account_index")

std::ifstream in_account;

std::ofstream out_account;

in_account.open("account"),out_account.open("account")

void add_user(account &a_account){

all_account();

~all_account();

void registerUser(TokenScanner& line);

Account find(std::string& userID);

bool exist(std::string& userID);
};
````

#### 3.图书类
`````
#include <iostream>
#include <fstream>
#include <vector>

#include "linklist_.h"
#include "token_scanner.h"
#include "diary.h"
class book{

public:

string ISBN;

string name;

string author;

string keyword;

int quantity=0;

double price=0;

double total_cost=0;

book(std::string isbn,std::string name__,std::string author__,
std::string keyword,int quant,double pri,double cost);

~book();
};

class all_books{

public:

LinkList_<ISBN, int> _isbn_book_map = linklist_<ISBN, int>("book_index_ISBN");

DoubleLinkList_<name, ISBN, int> _name_book_map = DoubleLinkList_<name, ISBN, int>("book_index_name");

DoubleLinkList_<author, ISBN, int> _author_book_map = DoubleLinkList_<author, ISBN, int>("book_index_name");

DoubleLinkList_<keyword, ISBN, int> _keywords_book_map = DoubleLinkList_<keyword, ISBN, int>("book_index_name");

std::fstream _books;

int num=0;

all_books();

~all_books();

void show(TokenScanner& line, condition& status, 
diaryGroup& Group);

void buy(TokenScanner& line, condition& status, 
diaryGroup& Group);

void modify(TokenScanner& line, condition& status, 
diaryGroup& Group);

void select(TokenScanner& line, condition& status, 
diaryGroup& Group);

void import(TokenScanner& line, condition& status, 
diaryGroup& Group)
};
`````

#### 4.日志类
``````
struct finacediary{

double sum;

bool postive;

}
class diary{

public:

int quantity;

double sum;

bool postive;

userID ID;

diary();

~diary();

};
class diaryGroup{

public:

std::fstream log;

std::fstream fiannce_log;

diaryGroup();

~diaryGroup();

void show(TokenScanner& line, condition& loggingStatus)

void finance_report(all_books books);

void report(TokenScanner& line, condition& loggingStatus,
all_books& bookGroup, all_account& accounts);

void add_log(diary new_);

void add_f_log(financediary new_);

};
``````

#### 5.登陆状态类
````
class condition{

public:

std::vector<string> account;

int num=0;

condition();

~condition();

void login(account a_account);

void logout(account a_account);

void select (int book_);
}
````

#### 6.块状链表
````
template <class keytype,class valuetype>
class linklist_{

public:

std::fstream list_;

int length=0;

linklist_(std::string fileName,int size=300);

~linklist_();

void insert(keytype key,valuetype vlue);

void erase(keytype key);

void modify(keytype key,valuetype vlue);

void clear();

valuetype* get(keytype key);
};

template <class keytype1,class keytype2,class valuetype>
class DoubleLinkList_{

public:

std::fstream list_;

int length=0;

DoubleLinkList_(std::string fileName,int size=300);

~DoubleLinkList_();

void insert(keytype1 key1,keytype2 key2,valuetype vlue);

void erase(keytype1 key1,keytype2 key2);

void modify(keytype1 key1,keytype2 key2,valuetype vlue);

void clear();

valuetype* get(keytype1 key1,keytype2 key2);


};
````
### 文件存储说明：

#### 1.账户相关文件

account_index : 存储某一账户在 account 中的位置

account : 存储所有已经注册的账户的相关信息且顺序存储

#### 2.图书相关文件

book_index_ISBN : 以 ISBN 为关键字存储某一图书在 book 中的位置

book_index_author : 以作者名为关键字存储某一图书在 book 中的位置

book_index_name : 以图书名为关键字存储某一图书在 book 中的位置

book_index_keyword : 以关键词为关键字存储某一图书在 book 中的位置

book : 顺序存储所有图书的相关信息，并在上面几个文件里面以块状链表存储对应
book的位置


#### 3.日志相关文件

log : 顺序存储所有操作日志

finance_log : 仅储存财务记录

#### 4.登陆状态存储

顺序存储并且每次在最后做修改
