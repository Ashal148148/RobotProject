#include "Validator.h"

bool Validator::isPasswordValid(const std::string& pass)
{
	if (pass.length() >= MUST_LEN)
	{
		bool AZFlag = false;
		bool azFlag = false;
		bool numFlag = false;

		for (int i = 0; i < pass.length(); i++)
		{
			if (isupper(pass[i]))
				AZFlag = true;

			if (islower(pass[i]))
				azFlag = true;

			if (isdigit(pass[i]))
				numFlag = true;
		}

		return(AZFlag && azFlag && numFlag);
	}
	else
	{
		return false;
	}
}

bool Validator::isNumeric(const std::string & str)
{
	bool numFlag = false;
	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]))
			numFlag = true;
	}
	return(numFlag);
}

bool Validator::isEmailValid(const std::string & email)
{
	int at = email.find('@');
	if (at == std::string::npos)
	{
		return false;
	}

	int dot = email.find('.', at + 1);
	if (dot == std::string::npos)
	{
		return false;
	}

	std::cout << __FUNCTION__ " returned true" << std::endl;
	return true;
}
