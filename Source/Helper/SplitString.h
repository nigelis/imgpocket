#pragma once

#include <vector>

using namespace std;

/*!
Split string by specified seperater.

@param str [in] string, original string.
@param separate [in] string, specified separater.
@param result [out] vector<string>, splited result.
*/
int SplitString(string str, string separate, vector<string>& result);