#include "NFANodes.h"

int main() {
  NFA *e1 = new NFA('a');
  NFA *e2 = new NFA('b');
  NFA *e3 = NFA::useConcat(e1, e2);
  e1 = new NFA('c');
  e3 = NFA::useOr(e1, e3);
  std::vector<char> path;
  e3 -> debugOutput(e3 -> getStartNode(), path);
  system("pause");
}