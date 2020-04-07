#include "thompson.h"

NFAProcess::NFAProcess() {};

/*
 * ( ) * Top level
 * '\0' Connect Op ---- level 2
 * | Or Op ------ level 1
 */
int NFAProcess::getOpPriority(char op) {
  switch(op) {
    case '(' :
      return 0;
    case ')':
      return 0;
    case '*':
      return 0;
    case '\0':
      return 2;
    case '|':
      return 1;
    default:
      return -1;
  }
}

void NFAProcess::throwError() {
  std::cerr << "Illegal Expression\n";
  system("pause");
  exit(0);
}

void NFAProcess::init(std::string regexp) {

  RegExp = regexp;
  std::stack<char> operatorStack;
  std::stack<NFA*> NFANodesStack;
  bool isPreAlpha = false;

  for(auto item : RegExp) {

    if(getOpPriority(item) == -1) {

      NFANodesStack.push(new NFA(item));

      if(isPreAlpha) {

        operatorStack.push('\0');

      }

      isPreAlpha = true;

    } else if(item == '(') {

      operatorStack.push(item);
      isPreAlpha = false;

    } else if(item == '*') {

      if(NFANodesStack.size() < 1) throwError();

      isPreAlpha = false;
      NFA* nxt = NFA::useKleeneClosure(NFANodesStack.top());
      NFANodesStack.pop();
      NFANodesStack.push(nxt);

    } else if(item == ')') {

      isPreAlpha = false;
      while(operatorStack.top() != '(') {

        char op = operatorStack.top();
        operatorStack.pop();

        if(operatorStack.size() < 1) throwError();
        if(op == '\0') {

          if(NFANodesStack.size() < 2) throwError();

          NFA* e1 = NFANodesStack.top(); NFANodesStack.pop();
          NFA* e2 = NFANodesStack.top(); NFANodesStack.pop();
          NFANodesStack.push(NFA::useConcat(e1, e2));

        } else if(op == '|') {

          if(NFANodesStack.size() < 2) throwError();

          NFA* e1 = NFANodesStack.top(); NFANodesStack.pop();
          NFA* e2 = NFANodesStack.top(); NFANodesStack.pop();
          NFANodesStack.push(NFA::useOr(e1, e2));

        } else {

          throwError();

        }
      }

      operatorStack.pop();

    } else {

      isPreAlpha = false;

      if(operatorStack.size() < 1) operatorStack.push(item);
      else {

        while(!operatorStack.empty() && getOpPriority(item) <= getOpPriority(operatorStack.top())) {

          char op = operatorStack.top();
          operatorStack.pop();

          if(op == '\0') {

            if(NFANodesStack.size() < 2) 
              throwError();

            NFA* e1 = NFANodesStack.top(); NFANodesStack.pop();
            NFA* e2 = NFANodesStack.top(); NFANodesStack.pop();
            NFANodesStack.push(NFA::useConcat(e1, e2));

          } else if(op == '|') {

            if(NFANodesStack.size() < 2) throwError();

            NFA* e1 = NFANodesStack.top(); NFANodesStack.pop();
            NFA* e2 = NFANodesStack.top(); NFANodesStack.pop();
            NFANodesStack.push(NFA::useOr(e1, e2));

          } else {

            throwError();

          }
        }

        operatorStack.push(item);

      }
    }
  }
  while(!operatorStack.empty()) {

    char op = operatorStack.top();
    operatorStack.pop();

    if(op == '\0') {

      if(NFANodesStack.size() < 2) throwError();

      NFA* e1 = NFANodesStack.top(); NFANodesStack.pop();
      NFA* e2 = NFANodesStack.top(); NFANodesStack.pop();
      NFANodesStack.push(NFA::useConcat(e1, e2));

    } else if(op == '|') {

      if(NFANodesStack.size() < 2) throwError();

      NFA* e1 = NFANodesStack.top(); NFANodesStack.pop();
      NFA* e2 = NFANodesStack.top(); NFANodesStack.pop();
      NFANodesStack.push(NFA::useOr(e1, e2));

    } else {

      throwError();

    }
  }
  if(NFANodesStack.size() != 1) throwError();
  NFAMap = NFANodesStack.top();
}

bool NFAProcess::runTest(std::string match) {

}