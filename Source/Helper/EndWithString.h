#pragma once

#include <vector>

using namespace std;

int EndWithString(vector<string>& srcs, string patterns, vector<string>& result);
inline bool EndWithString(string src, string pattern);