#pragma once
#include <string>
#include <stack>
#include "NFANodes.h"

class NFAProcess {  //NFA Main Module
  public :
    //Constructor
    NFAProcess();
  
  private :
    std::string RegExp;
    std::stack<char> operatorStack;
    std::stack<NFA> NFANodesStack;

  public :
    void init();
    
};