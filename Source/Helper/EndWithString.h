#pragma once

#include <vector>

using namespace std;

/*!
Filter string end with specified pattern.

@param srcs [in] vector<string>, source string.
@param patterns [in] string, different pattern can be combined with ';', "jpg;png;" for example.
@param result [out] vector<string>, output results.
*/
int EndWithString(vector<string>& srcs, string patterns, vector<string>& result);

/*!
Decide whether the source string end with specified pattern.

@param src [in] string, source string.
@param pattern [in] string, decide whether the specified string in the end of source string.
@return true = end with specified pattern.
*/
inline bool EndWithString(string src, string pattern);