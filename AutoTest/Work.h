#pragma once

#include <Windows.h>

class CWork
{
public:
	CWork() {};
	virtual ~CWork() {};
public:
	int Execute(int command) {

		switch (command) {
		case 1: {
			ExitProcess(1);
			break;
		}
		case 2: {
			throw ("input2");
			break;
		}
		case 3: {
			return 3;
			break;
		}
		default: {
			;
		}
		}

		return  command;


	}
protected:
	virtual void ExitProcess(DWORD dw) {
		::ExitProcess(dw);
	}
	
};

