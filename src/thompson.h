#pragma once
#include <string>

class NFA { //NFA Nodes
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

  public :
    void init();
    
};