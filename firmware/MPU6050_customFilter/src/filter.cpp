#include "filter.h"

expFilter::expFilter (Fix16 smooth) {
  smoothFactor = smooth;
  smoothFactorComp = Fix16(1)-smooth;
  average = 0;
}

expFilter::expFilter (Fix16 smooth, Fix16 initialAverage) {
  smoothFactor = smooth;
  smoothFactorComp = Fix16(1)-smooth;
  average = initialAverage;
}

highPass::highPass (Fix16 _smooth, int16_t _threshold) : expFilter(_smooth) {
  threshold = _threshold;
}

int16_t highPass::filterData (Fix16 inData) {
  Fix16 returnValue = inData - average;
  if ( abs(int16_t(returnValue)) < threshold ) {
    average = smoothFactor*inData + smoothFactorComp*average;
  }
  return returnValue;
}

lowPass::lowPass (Fix16 _smooth) : expFilter(_smooth) {}

Fix16 lowPass::filterData (Fix16 inData) {
  average = smoothFactor*inData + smoothFactorComp*average;
  return average;
}

Integrator::Integrator (Fix16 initialValue) {
  timeInterval = 0;
  integral = initialValue;
}

Fix16 Integrator::integrate(Fix16 inData) {
  Fix16 dt = Fix16( int16_t(millis()-timeInterval) ) / 1000;
  integral += inData * dt;
  timeInterval = millis();
  return integral;
}

complementaryFilter::complementaryFilter (Fix16 _smooth) : expFilter(_smooth) {}

Fix16 complementaryFilter::filterData (Fix16 inDataA, Fix16 inDataB) {
  average = smoothFactor*(average + Fix16(inDataA)) + smoothFactorComp*Fix16(inDataB);
  return average;
}
