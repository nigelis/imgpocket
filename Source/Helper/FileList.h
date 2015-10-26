#pragma once

#include <vector>

using namespace std;

int FileListFromFolder(const string& folder, vector<string>& list, const string& patterns = "*.*");
int FileListFromFile(const string& file, vector<string>& list);