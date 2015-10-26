#include "EndWithString.h"
#include "SplitString.h"

/*!
Filter string end with specified pattern.

@param srcs [in] vector<string>, source string.
@param patterns [in] string, different pattern can be combined with ';', "jpg;png;" for example.
@param result [out] vector<string>, output results.
*/
int EndWithString(vector<string>& srcs, string patterns, vector<string>& result)
{
	/*! get independent search pattern by dividing patterns with ';' */
	vector<string> pattern;
	SplitString(patterns, ";", pattern);

	for (int i = 0; i < srcs.size(); i++)
	{
		for (int j = 0; j < pattern.size(); j++)
		{
			if (EndWithString(srcs[i], pattern[j]))
			{
				result.push_back(srcs[i]);
				break;
			}
		}
	}
	return 0x0000;
}

/*!
Decide whether the source string end with specified pattern.

@param src [in] string, source string.
@param pattern [in] string, decide whether the specified string in the end of source string.
@return true = end with specified pattern.
*/
bool EndWithString(string src, string pattern)
{
	int len_src, len_pattern;
	len_src = src.length();
	len_pattern = pattern.length();

	if (len_src < len_pattern)
		return false;

	return (src.substr(len_src - len_pattern) == pattern);
}
