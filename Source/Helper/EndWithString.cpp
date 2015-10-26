#include "EndWithString.h"
#include "SplitString.h"


/*!
筛选字符串数组中以特定字符串结尾的字符串.

@param srcs [in] 源字符串数组
@param patterns [in] 特定模式,彼此间以";"分割
@param result [out] 筛选后的字符串数组
*/
int EndWithString(vector<string>& srcs, string patterns, vector<string>& result)
{
	/*! 从patterns中用";"分解得到独立的搜索条件 */
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
	return 0;
}

/*!
判断字符串是否以特定字符串结尾.

@param src [in] 源字符串
@param pattern [in] 特定字符串,判断源字符串的尾部是否为它
@return true=以特定字符串结尾,false=并不以特定字符串结尾
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
