#ifndef filter_h
#define filter_h

#include <fixmath.h>
#include "Arduino.h"

/** Base class for exponential filters
*/
class expFilter {
protected:
  Fix16 average, smoothFactor, smoothFactorComp;
public:
  expFilter (Fix16 smooth);
  expFilter (Fix16 smooth, Fix16 initialAverage);
};

/** High Pass filter class, useful for removing drift from gyroscope data
*/
class highPass : expFilter {
private:
  int16_t threshold;
public:
  highPass (Fix16 _smooth, int16_t _threshold);
  int16_t filterData(Fix16 inData);
};

/** Low pass filter class, useful for removing noise from accelerometer data
*/
class lowPass : expFilter {
public:
  lowPass (Fix16 _smooth);
  Fix16 filterData(Fix16 inData);
};

/** Integrator class, useful for determining angular position from angular rate
*/
class Integrator {
private:
  Fix16 integral;
  uint32_t timeInterval;
public:
  Integrator (Fix16 initialValue);
  Fix16 integrate (Fix16 inData);
};

/** Complementary filter class, usefur for putting togheter accelerometer and gyroscope data
*/
class complementaryFilter : expFilter {
public:
  complementaryFilter (Fix16 _smooth);
  Fix16 filterData(Fix16 inDataA, Fix16 inDataB);
};

#endif // filter_h
