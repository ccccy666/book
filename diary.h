#ifndef CODE_DIARY_HPP
#define CODE_DIARY_HPP
#include"Account.h"
#include "Book.h"
#include"condition.h"

struct financediary{

    double sum;

    bool postive;

};
class diary{

public:

    int quantity;

    double sum;

    bool postive;

    userID ID;

    diary();

    ~diary();

};
class diaryGroup {
public:

    std::fstream log;

    std::fstream fiannce_log;

    diaryGroup();

    ~diaryGroup();

//    void show(TokenScanner &line, condition &loggingStatus);
//
//    void finance_report(all_books books);
//
//    void report(TokenScanner &line, condition &loggingStatus,
//                all_books &bookGroup, All_Account &accounts);

    void add_log(diary new_);

    void add_f_log(financediary new_);

};
#endif //CODE_DIARY_HPP
