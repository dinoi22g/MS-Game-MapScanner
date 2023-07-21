#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <queue>
#include <vector>
#include "inifiles.hpp"
using namespace std;

typedef struct
{
	long id;
    char st[28];
	char name[32];
} Item;

struct Node
{
	Node* father;
	long val;
};

typedef long (*MLPROC)(char*, long, void*);

Item *Maps = NULL;
long MapCount = 0;
long *MapFlag = NULL;
char inifile[260];

void InitMapList(const char *file, const char *file2)
{
	if(Maps)
		delete Maps;
	FILE* fp = fopen(file, "rb");
	long long p = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long l = ftell(fp);
	fseek(fp, p, SEEK_SET);
	MapCount = l / sizeof(Item);
	char* buffer = (char*)new Item[MapCount];
	fread(buffer, l, 1, fp);
	fclose(fp);
	Maps = (Item*)buffer;
	MapFlag = new long[MapCount];
	strcpy(inifile, file2);
}

void DestoryMapList()
{
	if (Maps)
		delete Maps;
	MapCount = 0;
	if (MapFlag)
    	delete MapFlag;
}

long GetMapIndex(long id)
{
	long low = 0;
	long high = MapCount - 1;
	while (low <= high)
	{
		long mid = (low + high) / 2;
		if (Maps[mid].id == id)
			return mid;
		else if (Maps[mid].id > id)
			high = mid - 1;
		else if (Maps[mid].id < id)
			low = mid + 1;
	}
	return -1;
}

char* GetMapName(long id)
{
	long index = GetMapIndex(id);
	if (index == -1) {
		return NULL;
	} else {
        return Maps[index].name;
    }
}

long GetMapId(char* name)
{
	for (int i = 0; i < MapCount; i++) {
		if (strcmp(name, Maps[i].name) == 0) {
			return Maps[i].id;
		}
	}
	return -1;
}

long _EnumPossibleMap(long id, MLPROC proc, void *param)
{
	TIniFile *item = new TIniFile(inifile);
	int i = 0;
	while (true)
	{
		char Name[6];
		char IdStr[10];
		sprintf(Name, "Link%d", i++);
		sprintf(IdStr, "%d", id);
		TIniFile *item = new TIniFile(inifile);
		long link =item->ReadInteger(IdStr, Name, -1);
		delete item;
		long index = GetMapIndex(link);
		if (link == -1)
			return 1;
		if (MapFlag[index])
			continue;
		MapFlag[index] = 1;
		if (proc(Maps[index].name, link, param) == 0)
			return 0;
		if (_EnumPossibleMap(link, proc, param) == 0)
			return 0;
	}
}

void EnumPossibleMap(long id, MLPROC proc, void *param)
{
	memset(MapFlag, 0, sizeof(long) * MapCount);
	_EnumPossibleMap(id, proc, param);
}

long* SearchPath(long Start, long End)
{
	queue<Node*> unvisited, visited;
	vector<Node*> trash;
	int i;

	Node *n = new Node[1];
	n->father = NULL;
	n->val = Start;
	unvisited.push(n);
	trash.push_back(n);
	memset(MapFlag, 0, sizeof(long) * MapCount);
	while (unvisited.empty() == false)
	{
		Node *current = unvisited.front();
		visited.push(current);
		unvisited.pop();
		if (current->val == End) {
        	n = current;
			break;
		}
		i = 0;
		while (true)
		{
			char Name[6];
			char IdStr[10];
			sprintf(Name, "Link%d", i++);
			sprintf(IdStr, "%d", current->val);
			TIniFile *item = new TIniFile(inifile);
			long link =item->ReadInteger(IdStr, Name, -1);
			delete item;
			if (link == -1)
				break;
			if (MapFlag[GetMapIndex(link)])
				continue;
			MapFlag[GetMapIndex(link)] = 1;
			n = new Node[1];
			n->val = link;
			n->father = current;
			unvisited.push(n);
			trash.push_back(n);
		}
	}

	int c = 0;
	Node *tmp = n;
	while (n->father)
	{
		n = n->father;
		c++;
	}
	long *path = new long[c + 2];
	i = c + 1;
	path[c + 1] = 0;
	while (tmp->father)
	{
		path[--i] = tmp->val;
		tmp = tmp->father;
	}
	path[--i] = Start;

	while (trash.empty() == false)
	{
		delete trash.back();
		trash.pop_back();
	}

	return path;
}

bool GetTeleportPoint(long MapId, long TargetId, POINT *Point)
{
	TIniFile *item = new TIniFile(inifile);
	char IdStr[2][10];
	char Tmp[10];
	sprintf(IdStr[0], "%d", MapId);
	sprintf(IdStr[1], "%d", TargetId);
	long pt;
	//GetPrivateProfileString(IdStr[0], IdStr[1], "", Tmp, 10, inifile);
	pt = item->ReadInteger(IdStr[0], IdStr[1], 10);
	if ( pt != -1) {
		Point->x = *(short*)&pt;
		pt >>= 16;
		Point->y = *(short*)&pt;
		return true;
	} else {
		return false;
    }
	/*if (strlen(Tmp) > 0) {
		long pt;
		sscanf(Tmp, "%d", &pt);
		Point->x = *(short*)&pt;
		pt >>= 16;
		Point->y = *(short*)&pt;
		return true;
	} else {
    	return false;
	} */
}
