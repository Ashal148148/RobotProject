#include "Validator.h"

bool Validator::isPasswordValid(const std::string& pass)
{
	char allowedSigns[] = { '$', '!', '*', '?', '+', '_', '=', '.', '\\', '/', '-' };
	if (pass.length() >= MUST_LEN)
	{
		bool signFlag = false;
		bool azFlag = false;
		bool numFlag = false;

		for (int i = 0; i < pass.length(); i++)
		{
			for (int j = 0; j < ALLOWED_SIGN_AMOUNT; j++)
			{
				if (pass[i] == allowedSigns[j])
				{
					signFlag = true;
					break;
				}
			}		

			if (islower(pass[i]))
				azFlag = true;

			if (isdigit(pass[i]))
				numFlag = true;
		}

		return(signFlag && azFlag && numFlag);
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
