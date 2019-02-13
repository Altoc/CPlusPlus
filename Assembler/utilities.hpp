/*
*	Ian Whitesel
*	Assembler pt. 3
*	Summer 2018
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include<iostream>
#include"stack.hpp"

///////////////////////////////////////////////////////////////FREE FUNCTION DECLARATIONS
//Convert infix expr to POSTfix expr
String convertExprPost(const String& infix);

//Convert infix expr to PREfix expr
String convertExprPre(const String& infix);

//Evaluates prefix/postfix expr into assembly
String evaluate(const String& lOperand, const String& op, const String& rOperand, int N, const int& args, std::ostream& file);

//Convert postfix expr to assembly
String convertPostToAssembly(const String& postfix, const int& args, std::ostream& file);

//Convert prefix expr to assembly
String convertPreToAssembly(const String& prefix, const int& args, std::ostream& file);

#endif //UTILITIES_H