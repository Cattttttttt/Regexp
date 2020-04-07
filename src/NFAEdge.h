#pragma once

class NFANode;
class NFAEdge { //NFA Edges

  public :
    //Constructor
    NFAEdge(char limit, NFANode* towards);

  public :
    NFANode* towards; //Towards NFA Node
    char transfer;  //Transfer condition

  public :
    bool checkTransferCondition(char cur);
    NFANode* getTowardsNode();
};
