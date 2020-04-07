#pragma once
#include <string>
#include <stack>
#include <vector>
#include <iostream>

class PreProcess {
  public :
    //Constructor
    explicit PreProcess();

  private :

    const static char DELIMITER = '&';
    const char OP[4] = {'|', '*', '(', ')'};
    std::string originalExpression; //Original RegExp
    std::vector<char> RPNExpression;  //Processed RegExp

    bool isOp(char item);
    void throwError();

  public :
    /*
     * @func
     * @params {String}
     */
    void getInput(std::string inputRegExp);
    void preProcess();
    std::vector<char> getRPN();
};