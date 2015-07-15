#pragma once

#include "types.h"

struct running
{
	running(fake * fk) : m_fk(fk), rundeps(0), curroutine(0)
	{
	}
	~running()
	{
		clear();
	}
	void clear()
	{
		rundeps = 0;
		curroutine = 0;
		curcallstack.clear();
	}

	fake * m_fk;
	// ִ�е�������
	int rundeps;
	// ��ǰִ�е�routine
	routine * curroutine;
	// call stack
	String curcallstack;
};

