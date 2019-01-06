#pragma once

#include <string>
#include <iostream>

#include "Work.h"


class CWork_MOCK:public CWork
{
public:
	CWork_MOCK() {};
	virtual ~CWork_MOCK() {};

public:
	
public:
	//START:A,B,C,;GetInfo:D,E,F,;END:X,Y,Z,;
	std::wstring GetFlowString() {
		return m_flow;
	}
	
protected:
	void ExitProcess(DWORD dw) {
		RECORD_EXECUTE_START(L"ExitProcess");
		RECORD_EXECUTE_PUSH_ARGS(dw);
		RECORD_EXECUTE_END();
		;
	}

	//持有锁
	void RECORD_EXECUTE_START(std::wstring funcName) {
		m_child_flow += funcName;
		m_child_flow += L":";
	}
	//释放锁
	void RECORD_EXECUTE_END() {
		m_child_flow += L";";
		m_flow += m_child_flow;
		m_child_flow.clear();

	}
	// START:A, B, C; GetInfo:D, E, F; END:X, Y, Z; 
	void RECORD_EXECUTE_PUSH_ARGS(char c) {
		RECORD_EXECUTE_ADD_WSTRING(std::to_wstring(c));;
	}
	void RECORD_EXECUTE_PUSH_ARGS(DWORD dw) {
		RECORD_EXECUTE_ADD_WSTRING(std::to_wstring(dw));
	}
	void RECORD_EXECUTE_PUSH_ARGS(std::wstring wstr) {
		RECORD_EXECUTE_ADD_WSTRING(wstr);;
	}
	void RECORD_EXECUTE_PUSH_ARGS(int i) {
		RECORD_EXECUTE_ADD_WSTRING(std::to_wstring(i));

	}
	void RECORD_EXECUTE_PUSH_ARGS_HEX(char* p,unsigned int length) {
		throw(L"未实现");
	}

	void RECORD_EXECUTE_ADD_WSTRING(std::wstring wstr) {
		m_child_flow += wstr;
		m_child_flow += L",";
	}

	//修正 , ;
	bool first_args = true;

	std::wstring m_child_flow;
	std::wstring m_flow;

};

#include <regex>

class CWork_Test {
	
public:
	CWork_Test() {
		Exec();
	}
	void Exec() {
		CWork_MOCK* p = new CWork_MOCK();
		p->Execute(1);
		wprintf(L"%s\r\n",p->GetFlowString().c_str());

		/*
		通过 正则 匹配
		reg_assert
		*/
		std::wstring reg_assert = L"^(ExitProcess):1,;$";
		
		if (std::regex_match(p->GetFlowString(), std::wregex(reg_assert)))
		{
			wprintf(L"ok");
		}
		else {
			wprintf(L"fault");
		}


		delete(p);

	}


 };