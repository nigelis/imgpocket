#include "FileList.h"

#include <Windows.h>
#include <fstream>
#include <string>
#include "SplitString.h"


/*!
Get file list in specified folder.
allowing filter for file extension.

@param folder [in] string, specified folder, end with folder name, not including '\', "C:\Windows" for example.
@param list [out] vector<string>, file list to return.
@param patterns [in] filter pattern, like "*.jpg;*.png", all files as default.
@return int 0x0000 = Success.
*/
int FileListFromFolder(const string &folder, vector<string> &list, const string &patterns)
{
	string path;
	path = folder;
	/*! if folder ends with '\', remove the back slash */
	while (path[path.length() - 1] == '\\')
	{
		path = path.substr(0, path.length() - 1);
	}

	/*! get independent search pattern from patterns */
	vector<string> pattern;
	SplitString(patterns, ";", pattern);

	for (int i = 0; i < pattern.size(); i++)
	{
		HANDLE handler;				/*!< 查找文件所用句柄*/
		WIN32_FIND_DATAA find_data;	/*!< 当前文件相关信息*/

		string find_str = path + "\\" + pattern[i];

		handler = FindFirstFileA(find_str.c_str(), &find_data);
		if (handler != INVALID_HANDLE_VALUE)
		{
			do
			{
				list.push_back(find_data.cFileName);
			} while (FindNextFileA(handler, &find_data) != 0);
		}
		FindClose(handler);
	}

	return 0;
}

/*!
获取文件列表.
获取指定文件中所有的文件名(行字符串).

@param file [in] 文件的路径
@param list [out] 返回获取的文件列表
@return int 正常获取,则返回0
*/
int FileListFromFile(const string &file, vector<string> &list)
{
	ifstream infile(file);
	string line;

	while (getline(infile, line))
	{
		list.push_back(line);
	}
	infile.close();

	return 0;
}

