#ifndef __ADC_H__
#define __ADC_H__

class ADC_Channel
{
public:
    ADC_Channel(unsigned char channel = 0);
    ~ADC_Channel();

    unsigned int sample();
};

#endif // __ADC_H__