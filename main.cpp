#include "thompson.h"

int main() {
  std::string regexp = "aa|(b|c)";
  NFAProcess* test = new NFAProcess();
  test -> init(regexp);
  std::vector<char> path;
  test -> NFAMap ->debugOutput(test -> NFAMap -> getStartNode(), path);
  system("pause");
}