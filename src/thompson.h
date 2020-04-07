#pragma once
#include <string>
#include <stack>

class NFA { //NFA Nodes
  public :
    //Constructors
    explicit NFA(char a);
    explicit NFA(const NFA& a);

  private :

  public :
    static NFA combine();
};

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