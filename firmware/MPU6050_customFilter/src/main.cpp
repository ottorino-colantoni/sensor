// Copyright (c) 2017 Luca Anastasio
//
// GNU GENERAL PUBLIC LICENSE
//    Version 3, 29 June 2007
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <I2Cdev.h>
#include <MPU6050.h>
#include "filter2.h"

MPU6050 *sensor = new MPU6050();



ImuFilter filter(sensor);

void setup(/* arguments */) {
  Fastwire::setup(400, false);
  sensor->initialize();
  sensor->setFullScaleAccelRange(1);
  sensor->setFullScaleGyroRange(1);
  Serial.begin(115200);

  filter.setSmoothFactor(0.98, 0.999, 0.01);
  filter.setGyroOffset(200, 200, 300);
}

void loop(/* arguments */) {

  filter.run();

  Serial.flush();
  Serial.print(int16_t(filter.getPitch()));
  Serial.print(" ");
  Serial.print(int16_t(filter.getRoll()));
  Serial.print(" ");
  Serial.print(int16_t(filter.getYaw()));
  Serial.println(" ");

  delay(10);

}
