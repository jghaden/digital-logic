#include "combinational.h"
#include "sequential.h"

void SR_LATCH::run(IN s, IN r)
{
	if (r)
	{
		m = 0;
		q = 0;
	}
	else
	{
		if (s)
		{
			m = 1;
			q = 1;
		}
	}
}

void D_LATCH::run(IN data, IN store)
{
	n0.run(data, data);

	n1.run(data, store);
	n2.run(store, n0.q);

	n3.run(n1.q, n4.q);
	n4.run(n2.q, n3.q);

	q = n3.q;
}

void D_FF::run(IN data, IN clock)
{
	n0.run(clock);

	dl0.run(data, n0.q);
	dl1.run(dl0.q, clock);

	q = dl1.q;
}

void REGISTER::run(IN data, IN store, IN clock)
{
	n0.run(store);

	a0.run(df0.q, n0.q);
	a1.run(data, store);

	o0.run(a0.q, a1.q);

	df0.run(o0.q, clock);

	q = df0.q;
}

void REGISTER_4::run(INx data, IN store, IN clock)
{
	r0.run(data[0], store, clock);
	r1.run(data[1], store, clock);
	r2.run(data[2], store, clock);
	r3.run(data[3], store, clock);

	q[0] = r0.q;
	q[1] = r1.q;
	q[2] = r2.q;
	q[3] = r3.q;
}