#include <iostream>
#include <vector>

#include "logic.h"
#include "combinational.h"
#include "sequential.h"

using namespace std;

int main()
{
	SR_LATCH sr;			// Stores 1-bit of memory using an SR NOR latch

	IN s = HIGH;			// Set bit   - HIGH (1)
	IN r = LOW;				// Reset bit - LOW  (0)

	sr.run(s, r);			// Set HIGH and Reset LOW
	cout << sr.q << endl;	// Ouput: 1

	sr.run(LOW, LOW);		// Set LOW and Reset LOW
	cout << sr.q << endl;	// Ouput: 1

	sr.run(LOW, HIGH);		// Set LOW and Reset HIGH
	cout << sr.q << endl;	// Ouput: 0

	return 0;
}


