#pragma once
#include "logic.h"

class SR_LATCH
{
private:
	OUT m = 0;
public:
	OUT q = 0;

	void run(IN s, IN r);
};

class D_LATCH
{
private:
	NAND n0, n1, n2, n3, n4;
public:
	OUT q = 0;

	void run(IN data, IN store);
};

class D_FF
{
private:
	NOT n0;
	D_LATCH dl0, dl1;
public:
	OUT q = 0;

	void run(IN data, IN clock);
};

class REGISTER
{
private:
	NOT n0;
	AND a0, a1;
	OR o0;
	D_FF df0;
public:
	OUT q = 0;

	void run(IN data, IN store, IN clock);
};

class REGISTER_4
{
private:
	REGISTER r0, r1, r2, r3;
public:
	OUT q[4] = { 0, 0, 0, 0 };

	void run(INx data, IN store, IN clock);
};