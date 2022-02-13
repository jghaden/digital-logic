#pragma once
#include <iostream>
#include "logic.h"

struct NOT
{
	OUT q = false;

	void run(IN a);
};

struct AND
{
	OUT q = 0;

	void run(IN a, IN b);
	void run(INx in);
};

struct OR
{
	OUT q = 0;

	void run(IN a, IN b);
	void run(INx in);
};

struct XOR
{
	OUT q = 0;

	void run(IN a, IN b);
};

struct NAND
{
	OUT q = 1;

	void run(IN a, IN b);
	void run(INx in);
};

struct NOR
{
	OUT q = 1;

	void run(IN a, IN b);
	void run(INx in);
};

struct XNOR
{
	OUT q = 1;

	void run(IN a, IN b);
};

struct H_ADDER
{
	OUT sum = 0;
	OUT carry = 0;

	void run(IN a, IN b);
};

struct F_ADDER
{
	OUT sum = 0;
	OUT carry = 0;

	void run(IN a, IN b, IN c);
};

struct ADDER_4
{
	OUT sum[4] = { 0, 0, 0, 0 };
	OUT carry = 0;

	void run(INx a, INx b, IN c);
};

struct ADDER_X
{
	OUTx sum;
	OUT carry = 0;

	void run(INx a, INx b, IN c);
	void summary();
};

class DEC_4
{
private:
	NOT _not[2];
	AND _and[4];
public:
	OUTx q = { 0,0,0,0 };

	void run(IN a, IN b);
};

struct ADDSUB_X
{
	OUT carry = 0;
	OUT negative = 0;
	OUT zero = 1;
	OUTx sum;

	void run(INx a, INx b, IN subtract);
	void summary();
};

class ALU_74181
{
private:
	NOT _not[9];
	AND _and[38];
	NOR _nor[12];
	NAND _nand[4];
	XOR _xor[4];
public:
	OUTx f = { 0,0,0,0 };
	OUT ab = 0;
	OUT p = 0;
	OUT cn4 = 0;
	OUT g = 0;

	void run(INx a, INx b, INx s, IN m, IN cn);
	void summary();
};