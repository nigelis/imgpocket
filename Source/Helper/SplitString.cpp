#include "SplitString.h"

/*!
分割字符串.
按照指定字符,分割原字符串

@param str [in] 原始字符串
@param separate [in] 分隔符
@param result [out] 分割结果
*/
int SplitString(string str, string separate, vector<string>& result)
{
	int divide;	/*!< 指定分割字符串的位置*/
	divide = 0;

	str += separate;	/*!< 方便处理不存在分割符的情况*/

	while ((divide = str.find(separate)) != string::npos)
	{
		/*! 若divide为0,则意味着无有效的字符串可以被分割出来 */
		if (divide != 0)
		{
			result.push_back(str.substr(0, divide));
			str = str.substr(divide + 1);
		}
		else
		{
			str = str.substr(1);
		}
	}

	return 0;
}
