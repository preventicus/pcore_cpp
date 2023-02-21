/*

Created by Jakob Glück 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <gtest/gtest.h>

#include "SensorExampleFactory.h"

class SensorTest : public ::testing::Test {
 protected:
  Sensor normalSensorWithAccMetaData1 = SensorExampleFactory::normalSensor();
  Sensor normalSensorWithAccMetaData2 = SensorExampleFactory::normalSensor();
  Sensor comparableSensorWithPpgMetaData1 = SensorExampleFactory::comparableSensor();
  Sensor comparableSensorWithPpgMetaData2 = SensorExampleFactory::comparableSensor();
  Sensor normalSensorWithOneUnix = SensorExampleFactory::sensorWithOneUnixAndOneValue();
  Sensor normalSensorWithNUllUnix = SensorExampleFactory::sensorWithNUllUnixAndNUllValue();
  Sensor normalSensorWithOneUnixAndOneValueInLastBlock = SensorExampleFactory::sensorWithOneUnixAndOneValueInLastBlock();
  Sensor normalSensorWithEqualTimestampsInterval = SensorExampleFactory::sensorWithEqualTimestampsInterval();
};
TEST_F(SensorTest, TestGetMethodStandardSensor) {
  std::vector<Channel> channels = this->normalSensorWithAccMetaData1.getChannels();
  std::vector<Channel> comparableChannels = ChannelExampleFactory::normalVectorWithChannel();
  for (size_t i = 0; i < channels.size(); i++) {
    EXPECT_TRUE(channels[i].isEqual(comparableChannels[i]));
  }
  DifferentialTimestampsContainer differentialTimestampsContainer = this->normalSensorWithAccMetaData1.getDifferentialTimestamps();
  DifferentialTimestampsContainer comparableDifferentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::normalDifferentialTimestamps();
  EXPECT_TRUE(differentialTimestampsContainer.isEqual(comparableDifferentialTimestampsContainer));
  AbsoluteTimestampsContainer absoluteTimestampsContainer = this->normalSensorWithAccMetaData1.getAbsoluteTimestamps();
  AbsoluteTimestampsContainer comparableAbsoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::normalAbsoluteTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer.isEqual(comparableAbsoluteTimestampsContainer));
  EXPECT_EQ(this->normalSensorWithAccMetaData1.getSensorType(), ProtobufSensorType::SENSOR_TYPE_ACC);
}

TEST_F(SensorTest, TestGetMethodComparableSensor) {
  std::vector<Channel> channels = this->comparableSensorWithPpgMetaData1.getChannels();
  std::vector<Channel> comparableChannels = ChannelExampleFactory::normalVectorWithChannel();
  for (size_t i = 0; i < channels.size(); i++) {
    EXPECT_TRUE(channels[i].isEqual(comparableChannels[i]));
  }
  DifferentialTimestampsContainer differentialTimestampsContainer = this->comparableSensorWithPpgMetaData1.getDifferentialTimestamps();
  DifferentialTimestampsContainer comparableDifferentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::normalDifferentialTimestamps();
  EXPECT_TRUE(differentialTimestampsContainer.isEqual(comparableDifferentialTimestampsContainer));
  AbsoluteTimestampsContainer absoluteTimestampsContainer = this->comparableSensorWithPpgMetaData1.getAbsoluteTimestamps();
  AbsoluteTimestampsContainer comparableAbsoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::normalAbsoluteTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer.isEqual(comparableAbsoluteTimestampsContainer));
  EXPECT_EQ(this->comparableSensorWithPpgMetaData1.getSensorType(), ProtobufSensorType::SENSOR_TYPE_PPG);
}

TEST_F(SensorTest, TestSensorWithOneUnix) {
  for (auto& unix : AbsoluteTimestampsContainerExampleFactory::unixTimestampsOneElement_ms()) {
    EXPECT_EQ(this->normalSensorWithOneUnix.getDifferentialTimestamps().getFirstTimestamp(), unix);
  }
  for (size_t i = 0; i < DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms().size(); i++) {
    EXPECT_EQ(this->normalSensorWithOneUnix.getDifferentialTimestamps().getBlockIntervals()[i],
              DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms()[i]);
  }
  for (size_t i = 0; i < DifferentialTimestampsContainerExampleFactory::zeroTimestampsIntervals_ms().size(); i++) {
    EXPECT_EQ(this->normalSensorWithOneUnix.getDifferentialTimestamps().getTimestampsIntervals()[i],
              DifferentialTimestampsContainerExampleFactory::zeroTimestampsIntervals_ms()[i]);
  }
}

TEST_F(SensorTest, normalSensorWithNUllUnix) {
  EXPECT_EQ(this->normalSensorWithNUllUnix.getDifferentialTimestamps().getFirstTimestamp(),
            DifferentialTimestampsContainerExampleFactory::zeroFirstTimestamp_ms());
  EXPECT_EQ(this->normalSensorWithNUllUnix.getDifferentialTimestamps().getBlockIntervals(),
            DifferentialTimestampsContainerExampleFactory::emptyBlockIntervals_ms());
  EXPECT_EQ(this->normalSensorWithNUllUnix.getDifferentialTimestamps().getTimestampsIntervals(),
            DifferentialTimestampsContainerExampleFactory::emptyTimestampsIntervals_ms());
}

TEST_F(SensorTest, TestSensorWithOneUnixAndOneValueInLastBlock) {
  EXPECT_EQ(this->normalSensorWithOneUnixAndOneValueInLastBlock.getDifferentialTimestamps().getFirstTimestamp(),
            AbsoluteTimestampsContainerExampleFactory::absoluteTimestampWithOneUnixInLastBlock()[0]);
  for (size_t i = 0; i < DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_msWithOneUnixInLastBlock().size(); i++) {
    EXPECT_EQ(this->normalSensorWithOneUnixAndOneValueInLastBlock.getDifferentialTimestamps().getBlockIntervals()[i],
              DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_msWithOneUnixInLastBlock()[i]);
  }
  for (size_t i = 0; i < DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_msWithOneUnixInLastBlock().size(); i++) {
    EXPECT_EQ(this->normalSensorWithOneUnixAndOneValueInLastBlock.getDifferentialTimestamps().getTimestampsIntervals()[i],
              DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_msWithOneUnixInLastBlock()[i]);
  }
}

TEST_F(SensorTest, TestSensorWithEqualTimestampsInterval) {
  EXPECT_EQ(this->normalSensorWithEqualTimestampsInterval.getDifferentialTimestamps().getFirstTimestamp(),
            AbsoluteTimestampsContainerExampleFactory::absoluteTimestampWithEqualTimestampIntervals()[0]);
  for (size_t i = 0; i < DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms().size(); i++) {
    EXPECT_EQ(this->normalSensorWithEqualTimestampsInterval.getDifferentialTimestamps().getBlockIntervals()[i],
              DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms()[i]);
  }
  for (size_t i = 0; i < DifferentialTimestampsContainerExampleFactory::zeroTimestampsIntervals_ms().size(); i++) {
    EXPECT_EQ(this->normalSensorWithEqualTimestampsInterval.getDifferentialTimestamps().getTimestampsIntervals()[i],
              DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_msWithEqualDifferences()[i]);
  }
}

TEST_F(SensorTest, ComparableEqualNormalSensor) {
  EXPECT_TRUE(this->normalSensorWithAccMetaData1.isEqual(this->normalSensorWithAccMetaData2));
}

TEST_F(SensorTest, ComparableEqualComparableSensor) {
  EXPECT_TRUE(this->comparableSensorWithPpgMetaData1.isEqual(this->comparableSensorWithPpgMetaData2));
}

TEST_F(SensorTest, ComparableDifferentSensor) {
  EXPECT_FALSE(this->comparableSensorWithPpgMetaData1.isEqual(this->normalSensorWithAccMetaData1));
}

TEST_F(SensorTest, ComparableDifferentComparableSensor) {
  EXPECT_FALSE(this->comparableSensorWithPpgMetaData2.isEqual(this->normalSensorWithAccMetaData1));
}

TEST_F(SensorTest, TestSerializeAndDeserializeMethodStandardSensor) {
  ProtobufSensor protobufSensor;
  this->normalSensorWithAccMetaData1.serialize(&protobufSensor);
  Sensor sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(this->normalSensorWithAccMetaData1.isEqual(sensor2));
}

TEST_F(SensorTest, TestSerializeAndDeserializeMethodComparableSensor) {
  ProtobufSensor protobufSensor;
  this->comparableSensorWithPpgMetaData1.serialize(&protobufSensor);
  Sensor sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(this->comparableSensorWithPpgMetaData1.isEqual(sensor2));
}

TEST_F(SensorTest, TestMethodFirstTimestamp) {
  EXPECT_EQ(this->normalSensorWithAccMetaData1.getFirstTimestamp(), DifferentialTimestampsContainerExampleFactory::expectedFirstTimestamps());
}

TEST_F(SensorTest, TestMethodLastTimestamp) {
  EXPECT_EQ(this->normalSensorWithAccMetaData1.getLastTimestamp(), DifferentialTimestampsContainerExampleFactory::lastTimestamp());
}

TEST_F(SensorTest, TestMethodDuration) {
  EXPECT_EQ(this->normalSensorWithAccMetaData1.getDuration(), DifferentialTimestampsContainerExampleFactory::duration());
}

TEST_F(SensorTest, CheckSensorPtr) {
  ProtobufSensor protobufSensor;
  EXPECT_NO_THROW(this->comparableSensorWithPpgMetaData1.serialize(&protobufSensor));
}

TEST_F(SensorTest, CheckSensorNullPtr) {
  ProtobufSensor* protobufSensor = nullptr;
  EXPECT_THROW(this->comparableSensorWithPpgMetaData1.serialize(protobufSensor), std::invalid_argument);
}
