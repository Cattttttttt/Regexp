#include "preprocess.h"

PreProcess::PreProcess() {};

void PreProcess::getInput(std::string inputRegExp) {
  originalExpression = inputRegExp;
}

bool PreProcess::isOp(char item) {
  for(auto tmp : OP) {
    if(item == tmp) return true;
  }
  return false;
}

void PreProcess::throwError() {
  std::cerr << "Illegal Expression";
  exit(0);
}

void PreProcess::preProcess() {
  int numOfLeftBracket = 0;
  std::stack<char> opStack;
  std::stack<char> nodeStack;
  for(auto item : originalExpression) {
    if(isOp(item)) {
      if(item == ')' && !numOfLeftBracket) throwError();
      else if(item == ')' && numOfLeftBracket) {

      } else if(item == '(') {
        opStack.push(item);
        numOfLeftBracket++;
      } else {

      }
    } else {

    }
  }
}

std::vector<char> PreProcess::getRPN() {
  return RPNExpression;
}