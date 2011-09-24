#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "util.h"
#include "handler.h"

typedef void (*FunctionHandler)(void);

typedef struct _FunctionEntry
{
	char * declaration;
	FunctionHandler handler;
} FunctionEntry;

FunctionEntry * pEntrys = NULL;
const int count = 1;

// �ڴ���亯��
// ��ʵ�Ƕ� calloc �ķ�װ
// ֮����Ҫ�ٷ�װ������ calloc �Ļ����϶������ڴ����ʧ��ʱ�Ĵ������
// ����ڴ治�㣬���̽������򣬲��ټ���ִ��
// ���ǱȽϴֲڵĴ����ַ������ǿ��Ա�֤�����ٷ���������������
// �ڱ���Ŀ�в��漰�û����ݵı��棬��˴ֱ��Ľ�������
// ������������ݶ�ʧ������
void * memoryAllocate(size_t size)
{
	void * p = calloc(1, size);
	if (p == NULL)
	{
		puts("allocate memory failed!\n");
		exit(0);
	}
	else
	{
		return p;
	}
}


void setEntry(FunctionEntry * pEntry, char * declaration, FunctionHandler handler)
{
	// �����������������������Ϊ��
	assert(pEntry);
	assert(declaration);
	assert(handler);

	// ��� pEntry �� declaration Ŀǰ�������ݵģ��Ƚ�������ɾ��
	// Ȼ�����滻Ϊ������ ���漰�ڴ���ͷ����ٷ��䣩
	if (pEntry->declaration != NULL)
	{
		free(pEntry->declaration);
		pEntry->declaration = NULL;
	}

	pEntry->declaration = (char *)memoryAllocate(strlen(declaration) + 1);
	strcpy(pEntry->declaration, declaration);

	// ����ָ�������ͷţ����������������ֵ������ֵ
	// ֱ������Ϊ�µ�ֵ����
	pEntry->handler = handler;
}

void createEntry(int index, char * declaration, FunctionHandler handler)
{
	assert(index < count);
	assert(declaration);
	assert(handler);
	setEntry(&pEntrys[index], declaration, handler);
}

void initEntrys()
{
	pEntrys = (FunctionEntry *)memoryAllocate(sizeof(FunctionEntry) * count);
	createEntry(0, "double acos(double x)", acos_handler);
}

void showEntrys()
{
	assert(pEntrys);
	for (int i = 0; i < count; i++)
	{
		printf("%d %s\n", i, pEntrys[i].declaration);
	}
}

void begin()
{
	do 
	{
		puts("function list:");
		showEntrys();
		int i = getInt("select (-1 for quit): ");
		if (i == -1)
		{
			break;
		}
		else if (i > -1 && i < count)
		{
			pEntrys[i].handler();
		}
		else
		{
			printf("index out of range [%d, %d]\n", 0, count - 1);
		}
	} while (true);
}

int main()
{
	initEntrys();
	begin();
	return 0;
}