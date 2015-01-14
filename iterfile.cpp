#include <stdio.h>
#include <string>
DWORD IterFiles(string srcPath, string destPath)
{
	int iRet = 0;
	DIR *pDir;
	string destNewPath;
	struct dirent *pDirent;
	pDir = opendir(srcPath.c_str());
	if (pDir == NULL)
	{
		return -1;
	}
	while ((pDirent = readdir(pDir)) != NULL)
	{
		// if ((pDirent->d_name == '.') || pDirent->d_name[0] == '..')
		if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
		{
			continue;
		}
		char szTmpPath[1024] = {0};
		sprintf(szTmpPath, "%s/%s", srcPath.c_str(), pDirent->d_name);
		destNewPath = destPath + "/" + pDirent->d_name;

		if (IsDirectory(szTmpPath))
		{
			//如果是文件夹则进行递归
			iRet = IterFiles(szTmpPath, destNewPath);
			if (iRet < 0)
			{
				break;
			}
		}
		else
		{/* do something */
		}
	}

	closedir(pDir);

	return iRet;
}

int main()
{
	char	file[256] = {0};
	string  src = "getdir.c";
	string	dst;
	IterFiles(src, dst);
	printf();
}
