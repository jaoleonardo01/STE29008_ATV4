#ifndef __BUFFER_H__
#define __BUFFER_H__

class BUFFER
{
public:
    BUFFER(const char *b, int CMAX2);
    ~BUFFER();

    int fir(int xnew);
    void circ_update(int xnew);
    int get(int i);

private:
    int pos;
    int circ[], coef[];
    int CMAX;
    //int circ[5];
};

#endif // __BUFFER_H__