#pragma once
#include <vector>
#include <iostream>
#include "NFAEdge.h"

class NFANode { //NFA Nodes

  public :
    //Constructor
    explicit NFANode(int status);

  private :
    enum class Status {START, NORMAL, END};
    NFANode::Status curStatus = Status::NORMAL; //Node Status

  public :
    std::vector<NFAEdge*> edgeFromCurNode; //Record edges

    void addTowards(char limit, NFANode* next);
    int getNodeStatus();
    void changeStatus(int status);
};

class NFA { //NFA Set
  public :
    /*Constructors*/
    NFA();
    explicit NFA(char a);
    ~NFA();

  private :
    NFANode* startNFANode;
    NFANode* endNFANode;

  public :
    static NFA* useConcat(NFA* target1, NFA* target2);
    static NFA* useOr(NFA* target1, NFA* target2);
    static NFA* useKleeneClosure(NFA* target);
    NFANode* getStartNode();
    void debugOutput(NFANode* current, std::vector<char> path);
};