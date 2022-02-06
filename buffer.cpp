#include "buffer.h"

BUFFER::BUFFER(const char *b, int CMAX2)
{
	int i;
	int i2 = 0;
	CMAX = CMAX2;

    while (b[i2] != '\0')
    {
		coef[i2] = b[i2] - '0';
        //this->put(b[i2]);
        i2++;
    }

	int circ[CMAX];
	for (i=0; i<CMAX; i++) /* set values to 0 */
		circ[i] = 0; pos=CMAX-1; 
}

BUFFER::~BUFFER()
{
}

int BUFFER::get(int i)
{
	int ii;
	ii = (pos - i) % this->CMAX;
	return this->circ[ii];
}

void BUFFER::circ_update(int xnew) {
	pos = ((pos == 0) ? CMAX-1 : (pos-1));
	this->circ[pos] = xnew;
}

int BUFFER::fir(int xnew) {
	int i;
	int result; 
	this->circ_update(xnew); 
	for (i=0, result=0; i<CMAX; i++)
		result += coef[i] * get(i);
	return result;
}