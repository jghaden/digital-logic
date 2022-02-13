#include "combinational.h"

void NOT::run(IN a)
{
	q = !(a);
}

void AND::run(IN a, IN b)
{
	q = (a && b);
}

void AND::run(INx in)
{
	q = 1;

	for (size_t i = 0; i < in.size(); i++)
	{
		if (!in[i])
		{
			q = 0;
			break;
		}
	}
}

void OR::run(IN a, IN b)
{
	q = (a || b);
}

void OR::run(INx in)
{
	q = 0;

	for (size_t i = 0; i < in.size(); i++)
	{
		if (in[i])
		{
			q = 1;
			break;
		}
	}
}

void XOR::run(IN a, IN b)
{
	q = (a ^ b);
}

void NAND::run(IN a, IN b)
{
	q = !(a && b);
}

void NAND::run(INx in)
{
	q = 0;

	for (size_t i = 0; i < in.size(); i++)
	{
		if (!in[i])
		{
			q = 1;
			break;
		}
	}
}

void NOR::run(IN a, IN b)
{
	q = !(a || b);
}

void NOR::run(INx in)
{
	q = 1;

	for (size_t i = 0; i < in.size(); i++)
	{
		if (in[i])
		{
			q = 0;
			break;
		}
	}
}

void XNOR::run(IN a, IN b)
{
	q = !(a ^ b);
}

void H_ADDER::run(IN a, IN b)
{
	XOR x0;
	AND a0;

	x0.run(a, b);
	a0.run(a, b);

	sum = x0.q;
	carry = a0.q;
}

void F_ADDER::run(IN a, IN b, IN c)
{
	OR o0;
	H_ADDER ad0, ad1;

	ad0.run(a, b);
	ad1.run(ad0.sum, c);

	o0.run(ad0.carry, ad1.carry);

	sum = ad1.sum;
	carry = o0.q;
}

void ADDER_4::run(INx a, INx b, IN c)
{
	F_ADDER ad0, ad1, ad2, ad3;

	ad0.run(a[3], b[3], c);
	ad1.run(a[2], b[2], ad0.carry);
	ad2.run(a[1], b[1], ad1.carry);
	ad3.run(a[0], b[0], ad2.carry);

	sum[0] = ad0.sum;
	sum[1] = ad1.sum;
	sum[2] = ad2.sum;
	sum[3] = ad3.sum;
	carry = ad3.carry;
}

void ADDER_X::run(INx a, INx b, IN c)
{
	carry = c;

	for (size_t i = a.size(); i > 0; i--)
	{
		F_ADDER add;

		add.run(a[i - 1], b[i - 1], carry);

		sum.push_back(add.sum);

		carry = add.carry;
	}
}

void ADDER_X::summary()
{
	std::cout << carry << ':';

	for (size_t i = sum.size(); i > 0; i--)
	{
		std::cout << sum[i - 1];
	}
}

void DEC_4::run(IN a, IN b)
{
	_not[0].run(a);
	_not[1].run(b);

	_and[0].run(_not[0].q, _not[1].q);
	_and[1].run(a, _not[1].q);
	_and[2].run(_not[0].q, b);
	_and[3].run(a, b);

	q[0] = _and[0].q;
	q[1] = _and[1].q;
	q[2] = _and[2].q;
	q[3] = _and[3].q;
}

void ADDSUB_X::run(INx a, INx b, IN subtract)
{
	NOR n0;
	ADDER_X adder;

	if (subtract)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			b[i] = !b[i];
		}
	}

	adder.run(a, b, subtract);
	n0.run(adder.sum);

	sum = adder.sum;
	carry = adder.carry;
	negative = adder.sum[a.size() - 1];
	zero = n0.q;
}

void ADDSUB_X::summary()
{
	std::cout << carry << negative << zero << ':';

	for (size_t i = sum.size(); i > 0; i--)
	{
		std::cout << sum[i - 1];
	}
}

void ALU_74181::run(INx a, INx b, INx s, IN m, IN cn)
{
	_not[0].run(m);

	_not[1].run(b[0]);
	_not[2].run(b[1]);
	_not[3].run(b[2]);
	_not[4].run(b[3]);

	_and[0].run({ a[0] });
	_and[1].run(s[0], b[0]);
	_and[2].run(s[1], _not[1].q);
	_and[3].run({ _not[1].q, s[2], a[0] });
	_and[4].run({ a[0], b[0], s[3] });

	_and[5].run({ a[1] });
	_and[6].run(s[0], b[1]);
	_and[7].run(s[1], _not[2].q);
	_and[8].run({ _not[2].q, s[2], a[1] });
	_and[9].run({ a[1], b[1], s[3] });

	_and[10].run({ a[2] });
	_and[11].run(s[0], b[2]);
	_and[12].run(s[1], _not[3].q);
	_and[13].run({ _not[3].q, s[2], a[2] });
	_and[14].run({ a[2], b[2], s[3] });

	_and[15].run({ a[3] });
	_and[16].run(s[0], b[3]);
	_and[17].run(s[1], _not[4].q);
	_and[18].run({ _not[4].q, s[2], a[3] });
	_and[19].run({ a[3], b[3], s[3] });

	_nor[0].run({ _and[0].q, _and[1].q, _and[2].q });
	_nor[1].run({ _and[3].q, _and[4].q });
	_nor[2].run({ _and[5].q, _and[6].q, _and[7].q });
	_nor[3].run({ _and[8].q, _and[9].q });
	_nor[4].run({ _and[10].q, _and[11].q, _and[12].q });
	_nor[5].run({ _and[13].q, _and[14].q });
	_nor[6].run({ _and[15].q, _and[16].q, _and[17].q });
	_nor[7].run({ _and[18].q, _and[19].q });

	_nand[0].run(cn, _not[0].q);

	_not[5].run(_nor[0].q);
	_and[20].run(_not[0].q, _nor[0].q);
	_and[21].run({ _not[0].q, _nor[0].q, cn });

	_not[6].run(_nor[2].q);
	_and[22].run(_not[0].q, _nor[2].q);
	_and[23].run({ _not[0].q, _nor[0].q, _nor[3].q });
	_and[24].run({ _not[0].q, cn, _nor[1].q, _nor[3].q });
	_not[7].run(_nor[4].q);

	_and[25].run(_not[0].q, _nor[4].q);
	_and[26].run({ _not[0].q, _nor[2].q, _nor[5].q });
	_and[27].run({ _not[0].q, _nor[0].q, _nor[3].q, _nor[5].q });
	_and[28].run({ _not[0].q, cn, _nor[1].q, _nor[3].q, _nor[5].q });
	_not[8].run(_nor[6].q);

	_nand[1].run({ _nor[1].q, _nor[3].q, _nor[5].q, _nor[7].q });
	_nand[2].run({ cn, _nor[1].q, _nor[1].q, _nor[3].q, _nor[5].q, _nor[7].q });

	_and[29].run({ _nor[0].q, _nor[3].q, _nor[5].q, _nor[7].q });
	_and[30].run({ _nor[2].q, _nor[5].q, _nor[7].q });
	_and[31].run(_nor[4].q, _nor[7].q);
	_and[32].run({ _nor[6].q });

	_and[33].run(_not[5].q, _nor[1].q);
	_and[34].run(_not[6].q, _nor[3].q);
	_and[35].run(_not[7].q, _nor[5].q);
	_and[36].run(_not[8].q, _nor[7].q);

	_nor[8].run(_and[20].q, _and[21].q);
	_nor[9].run({ _and[22].q, _and[23].q, _and[24].q });
	_nor[10].run({ _and[25].q, _and[26].q, _and[27].q, _and[28].q });
	_nor[11].run({ _and[29].q, _and[30].q, _and[31].q, _and[32].q });

	_xor[0].run(_nand[0].q, _and[33].q);
	_xor[1].run(_nor[8].q, _and[34].q);
	_xor[2].run(_nor[9].q, _and[35].q);
	_xor[3].run(_nor[10].q, _and[36].q);

	_and[37].run({ _xor[0].q, _xor[1].q, _xor[2].q, _xor[3].q });
	_nand[3].run(_nand[4].q, _nor[11].q);

	// Outputs
	f[0] = _xor[0].q;
	f[1] = _xor[1].q;
	f[2] = _xor[2].q;
	f[3] = _xor[3].q;

	ab = _and[37].q;
	p = _nand[1].q;
	cn4 = _nand[3].q;
	g = _nor[11].q;
}

void ALU_74181::summary()
{
	std::cout << ab << p << cn4 << g << ':';
	std::cout << f[3] << f[2] << f[1] << f[0];
}