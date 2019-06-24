#pragma once

#include <iostream>
#include <string>
#include <ctype.h>
#include <regex>

#define MUST_LEN 8
#define ALLOWED_SIGN_AMOUNT 11

class Validator
{
public:
	//Password must have: a letter, a number and a sign ($!*?+_=.\/-) Length: >=8 
	static bool isPasswordValid(const std::string& pass);
	static bool isNumeric(const std::string& pass);
	static bool isEmailValid(const std::string& email);

};