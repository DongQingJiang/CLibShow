#include <stdio.h>
#include <stdlib.h>

static const int bufferSize = 256;
static char inputBuffer[bufferSize];

static char * readLine()
{
	memset(inputBuffer, 0, bufferSize);
	char * p = gets(inputBuffer);
	return p;
}

// ���û�����һ�� int �͵�����
int getInt(const char * message)
{
	while (true)
	{
		if (message != NULL)
		{
			printf(message);
		}
		int v = 0;
		char * line = readLine();

		int success = scanf("%d\n", &v);
		if (success != 0)
		{
			return v;
		}
		else
		{
			// ����û��������������ݣ���Ҫ���û���������
			// �ڴ�֮ǰ���������ǰ���뻺���е��ַ�����������
			// �´� scanf() Ҳ��ʧ�ܣ���������ѭ��
			while (getchar() != '\n'){}
		}
	}
}

// ���û�����һ�� double �͵�����
double getDouble(const char * message)
{
	while (true)
	{
		if (message != NULL)
		{
			printf(message);
		}
		double v = 0.0;
		int success = scanf("%lf", &v);
		if (success != 0)
		{
			return v;
		}
		else
		{
			// ����û��������������ݣ���Ҫ���û���������
			// �ڴ�֮ǰ���������ǰ���뻺���е��ַ�����������
			// �´� scanf() Ҳ��ʧ�ܣ���������ѭ��
			while (getchar() != '\n'){}
		}
	}
}