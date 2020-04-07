#pragma once
#include <string>
#include <stack>
#include "NFANodes.h"

class NFAProcess {  //NFA Main Module
  public :
    //Constructor
    explicit NFAProcess();
  
  public :
    std::string RegExp;
    NFA* NFAMap;

    int getOpPriority(char op);
    void throwError();

  public :
    void init(std::string regexp);
    bool runTest(std::string match);
};