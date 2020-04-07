#include "NFAEdge.h"

NFAEdge::NFAEdge(char limit, NFANode* towards) {
  transfer = limit;
  this -> towards = towards;
}

bool NFAEdge::checkTransferCondition(char cur) {
  return cur == '\0' ? true : transfer == cur;
}

NFANode* NFAEdge::getTowardsNode() {
  return towards;
}