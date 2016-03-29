#include "SplitString.h"

/*!
Split string by specified seperater.

@param str [in] string, original string.
@param separate [in] string, specified separater.
@param result [out] vector<string>, splited result.
*/
int SplitString(string str, string separate, vector<string>& result)
{
	int divide;	/*!< position to split */
	divide = 0;

	str += separate;	/*!< handle for situation separater don't exist in str */

	while ((divide = str.find(separate)) != string::npos)
	{
		if (divide != 0)
		{
			result.push_back(str.substr(0, divide));
			str = str.substr(divide + separate.length());
		}
		else
		{
			/*! divide = 0 means no string before separater */
			str = str.substr(separate.length());
		}
	}

	return 0x0000;
}
