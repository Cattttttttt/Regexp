#include "NFANodes.h"
#include "NFAEdge.h"

NFANode::NFANode(int status) {
  switch(status) {
    case 0:
      curStatus = Status::START;
      break;
    case 1:
      curStatus = Status::NORMAL;
      break;
    case 2:
      curStatus = Status::END;
      break;
    default:
      curStatus = Status::NORMAL;
  }
}

void NFANode::changeStatus(int status) {
    switch(status) {
    case 0:
      curStatus = Status::START;
      break;
    case 1:
      curStatus = Status::NORMAL;
      break;
    case 2:
      curStatus = Status::END;
      break;
    default:
      curStatus = Status::NORMAL;
  }
}

void NFANode::addTowards(char limit, NFANode* towards) {
  NFAEdge* tmp = new NFAEdge(limit, towards);
  edgeFromCurNode.push_back(tmp);
}

int NFANode::getNodeStatus() {
  switch(curStatus) {
    case Status::START:
      return 0;
    case Status::NORMAL:
      return 1;
    case Status::END:
      return 2;
    default:
      return 1;
  }
}

NFA::NFA() {}

NFA::NFA(char a) {
  NFANode* start = new NFANode(0);
  NFANode* end = new NFANode(2);
  start -> addTowards(a, end);
  startNFANode = start;
  endNFANode = end;
}

NFA::~NFA() {
  std::clog << "Called Destructor\n";
}

NFANode* NFA::getStartNode() {
  return startNFANode;
}

NFA* NFA::useConcat(NFA* target1, NFA* target2) {
  NFA* res = new NFA(*target1);
  res -> endNFANode -> changeStatus(1);
  target2 -> startNFANode -> changeStatus(1);
  res -> endNFANode -> addTowards('\0', target2 -> startNFANode);
  res -> endNFANode = target2 -> endNFANode;
  delete target2; delete target1;
  return res;
}

NFA* NFA::useOr(NFA* target1, NFA* target2) {
  NFA* res = new NFA();
  res -> startNFANode = new NFANode(0);
  res -> startNFANode -> addTowards('\0', target1 -> startNFANode);
  target1 -> startNFANode -> changeStatus(1);
  res -> startNFANode -> addTowards('\0', target2 -> startNFANode);
  target2 -> startNFANode -> changeStatus(1);
  res -> endNFANode = new NFANode(2);
  target1 -> endNFANode -> addTowards('\0', res -> endNFANode);
  target1 -> endNFANode -> changeStatus(1);
  target2 -> endNFANode -> addTowards('\0', res -> endNFANode);
  target2 -> endNFANode -> changeStatus(1);
  delete target1; delete target2;
  return res;
}

NFA* NFA::useKleeneClosure(NFA* target) {
  NFA* res = new NFA();
  res -> startNFANode = new NFANode(0);
  res -> endNFANode = new NFANode(2);
  target -> startNFANode -> changeStatus(1);
  target -> endNFANode -> changeStatus(1);
  res -> startNFANode -> addTowards('\0', res -> endNFANode);
  res -> startNFANode -> addTowards('\0', target -> startNFANode);
  target -> endNFANode -> addTowards('\0', target -> startNFANode);
  target -> endNFANode -> addTowards('\0', res -> endNFANode);
  delete target;
  return res;
}

void NFA::debugOutput(NFANode* current, std::vector<char> path) {
  if(current -> edgeFromCurNode.size() == 0) {
    std::cout << "From start to end via";
    for(auto item : path) {
      if(item != '\0')
        std::cout << " " << item;
      else std::cout << " epsilon";
    }
    std::cout << std::endl;
    return;
  }
  for(auto nxt : current -> edgeFromCurNode) {
    std::vector<char> next = path;
    next.push_back(nxt -> transfer);
    debugOutput(nxt -> towards, next);
  }
}