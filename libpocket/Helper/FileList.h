#pragma once

#include <vector>

using namespace std;

/*!
Get file list in specified folder.
allowing filter for file extension.

@param folder [in] string, specified folder, end with folder name, not including '\', "C:\Windows" for example.
@param list [out] vector<string>, file list to return.
@param patterns [in] filter pattern, like "*.jpg;*.png", all files as default.
@return int 0x0000 = Success.
*/
int FileListFromFolder(const string& folder, vector<string>& list, const string& patterns = "*.*");

/*!
Get file list from specified document content.
one file path per line.

@param file [in] string, file path.
@param list [out] vector<string>, file list to return.
@return int 0x0000 = Success.
*/
int FileListFromFile(const string& file, vector<string>& list);