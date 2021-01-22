#ifndef HAL_GPIO_HPP
#define HAL_GPIO_HPP

class HalGpio {
  public:
    static const int PIN_STATE_HIGH;
    static const int PIN_MODE_INPUT;
    static const int PIN_MODE_INPUT_PULLUP;
    static const int PIN_STATE_LOW;
    static const int PIN_MODE_OUTPUT;

    virtual ~HalGpio (void) { }
    virtual int digitalWrite (unsigned int pin, int state) const = 0;
    virtual int pinMode (unsigned int pin, int mode) const = 0;
};

#endif // HAL_GPIO_HPP
