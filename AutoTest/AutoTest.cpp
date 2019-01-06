// AutoTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Work_MOCK.h"


int main()
{
	CWork_Test* p = new CWork_Test();
	p->Exec();
	delete(p);


    return 0;
}

