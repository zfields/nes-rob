#ifndef HAL_CLOCK_HPP
#define HAL_CLOCK_HPP

class HalClock {
  public:
    virtual ~HalClock (void) { }
    virtual int delayMicroseconds (unsigned int pin) const = 0;
};

#endif // HAL_CLOCK_HPP
