#ifndef filter2_h
#define filter2_h

#include <fixmath.h>
#include <Arduino.h>
#include <MPU6050.h>

class lowPass {
private:
  Fix16 average, smoothFactor, smoothFactorComp;
public:
  lowPass ();
  void setSmoothFactor(Fix16 smooth);
  Fix16 filterData2(Fix16 inData);
};

class complementaryFilter {
private:
  Fix16 smoothFactor, smoothFactorComp, smoothFactorGyro, smoothFactorCompGyro, gyroCalcOffset, averageValue;
  uint32_t timeInterval;
  int16_t gyroOffset;
public:
  complementaryFilter();
  void setSmoothFactor(Fix16 complementary, Fix16 gyroscope);
  Fix16 filterData(Fix16 & Gyro, Fix16 & AccA, Fix16 & AccB, Fix16 & AccC);
  void setGyroOffset(int16_t offset);
};

class ImuFilter {
private:
  Fix16 AccX, AccY, AccZ,
        GyroX, GyroY, GyroZ,
        Pitch, Roll, Yaw;
  int16_t *ax, *ay, *az, *gx, *gy, *gz;
  MPU6050* imu;
  complementaryFilter PitchFilter, RollFilter, YawFilter;
  lowPass lowPassX, lowPassY, lowPassZ;
public:
  ImuFilter(MPU6050* _imu);
  Fix16 getPitch();
  Fix16 getRoll();
  Fix16 getYaw();
  void setGyroOffset(int16_t x, int16_t y, int16_t z);
  void setSmoothFactor(Fix16 complementary, Fix16 gyroscope, Fix16 accelerometer);
  void run();
};

inline Fix16 Abs(Fix16 X) {
  return (X>0) ? X : (Fix16(0)-X);
}

#endif // filter2_h
