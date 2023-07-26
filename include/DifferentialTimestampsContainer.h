/*

Created by Jakob Glueck, Steve Merschel 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#pragma once
#include <vector>
#include "BlockIdx.h"
#include "DifferentialBlock.h"
#include "IPCore.h"
#include "UnixTimestamp.h"
#include "protobuf/pcore_raw.pb.h"

using namespace PCore;

/**
 * @typedef DifferentialTimestampContainerProtobuf
 * @brief Definition for the protobuf message type corresponding to the container for differential timestamps.
 */
using DifferentialTimestampContainerProtobuf = com::preventicus::pcore::Raw_Sensor_DifferentialTimestampsContainer;

/**
 * @typedef TimeDifference
 * @brief Alias for the data type representing time differences in milliseconds.
 */
using TimeDifference = uint32_t;

/**
 * @typedef BlocksDifferences
 * @brief Alias for a vector of time differences in milliseconds representing the time differences between blocks.
 */
using BlocksDifferences = std::vector<TimeDifference>;

/**
 * @typedef TimestampsDifferences
 * @brief Alias for a vector of time differences in milliseconds representing the time differences between timestamps.
 */
using TimestampsDifferences = std::vector<TimeDifference>;

/**
 * @typedef DifferentialTimestampsContainerJson
 * @brief Alias for the JSON data type used to represent the container for differential timestamps.
 */
using DifferentialTimestampsContainerJson = Json::Value;

/**
 * @typedef UnixTimestampJson
 * @brief Alias for the JSON data type used to represent a Unix timestamp.
 */
using UnixTimestampJson = Json::Value;

/**
 * @typedef BlocksDifferencesJson
 * @brief Alias for the JSON data type used to represent a vector of time differences in milliseconds between blocks.
 */
using BlocksDifferencesJson = Json::Value;

/**
 * @typedef TimestampsDifferencesJson
 * @brief Alias for the JSON data type used to represent a vector of time differences in milliseconds between timestamps.
 */
using TimestampsDifferencesJson = Json::Value;

namespace PCore {
/**
 * @class DifferentialTimestampsContainer
 * @brief Class representing the container for differential timestamps.
 *
 * The `DifferentialTimestampsContainer` class stores information about the differential timestamps for a sensor channel.
 * It contains the first Unix timestamp in milliseconds, time differences between blocks, and time differences between timestamps.
 */
class DifferentialTimestampsContainer final : public IPCore<DifferentialTimestampContainerProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a DifferentialTimestampsContainer instance with the given data.
   * @param firstUnixTimestampInMs The first Unix timestamp in milliseconds.
   * @param blocksDifferencesInMs Time differences in milliseconds between blocks.
   * @param timestampsDifferencesInMs Time differences in milliseconds between timestamps.
   */
  explicit DifferentialTimestampsContainer(UnixTimestamp firstUnixTimestampInMs,
                                           BlocksDifferences blocksDifferencesInMs,
                                           TimestampsDifferences timestampsDifferencesInMs) noexcept;

  /**
   * @brief Constructor to initialize a DifferentialTimestampsContainer instance from the given protobuf data.
   * @param differentialTimestampsContainerProtobuf The protobuf data with which to initialize the DifferentialTimestampsContainer instance.
   */
  explicit DifferentialTimestampsContainer(const DifferentialTimestampContainerProtobuf& differentialTimestampsContainerProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a DifferentialTimestampsContainer instance from the given JSON data.
   * @param differentialTimestampsContainerJson The JSON data with which to initialize the DifferentialTimestampsContainer instance.
   *
   * @note The provided JSON data should contain the required key for the DifferentialTimestampsContainer.
   * Otherwise, the behavior is undefined.
   *
   * @throw WrongValueException is the first unix timestamps is negativ.
   */
  explicit DifferentialTimestampsContainer(const DifferentialTimestampsContainerJson& differentialTimestampsContainerJson);

  /**
   * @brief Default constructor to create an empty DifferentialTimestampsContainer instance.
   */
  explicit DifferentialTimestampsContainer() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the first Unix timestamp in milliseconds.
   * @return The first Unix timestamp in milliseconds.
   */
  [[nodiscard]] UnixTimestamp getFirstUnixTimestampInMs() const noexcept;

  /**
   * @brief Get the last Unix timestamp in milliseconds for the DifferentialTimestampsContainer instance.
   *
   * The method calculates and returns the last Unix timestamp in milliseconds based on the provided `firstUnixTimestampInLastBlock`
   * and the number of elements in the last block (`numberOfElementsInLastBlock`). The method considers the time differences between
   * blocks and elements to compute the last Unix timestamp accurately.
   *
   * @param firstUnixTimestampInLastBlock The first Unix timestamp in milliseconds of the last block.
   * @param numberOfElementsInLastBlock The number of elements in the last block.
   * @return The last Unix timestamp in milliseconds.
   */
  [[nodiscard]] UnixTimestamp getLastUnixTimestampInMs(UnixTimestamp firstUnixTimestampInLastBlock,
                                                       size_t numberOfElementsInLastBlock) const noexcept;

  /**
   * @brief Get the time differences in milliseconds between blocks.
   * @return A vector of time differences in milliseconds between blocks.
   */
  [[nodiscard]] BlocksDifferences getBlocksDifferencesInMs() const noexcept;

  /**
   * @brief Get the time differences in milliseconds between timestamps.
   * @return A vector of time differences in milliseconds between timestamps.
   */
  [[nodiscard]] TimestampsDifferences getTimestampsDifferencesInMs() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the DifferentialTimestampsContainer instance is set.
   * @return True if the instance is set; otherwise, false.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the DifferentialTimestampsContainer instance to JSON format.
   *
   * The method converts the DifferentialTimestampsContainer instance into a JSON data format and returns it.
   * If the DifferentialTimestampsContainer instance is not set, an empty JSON object will be returned.
   *
   * @return The JSON data representing the DifferentialTimestampsContainer instance.
   */
  [[nodiscard]] DifferentialTimestampsContainerJson toJson() const noexcept final;

  /**
   * @brief Serialize the DifferentialTimestampsContainer instance to protobuf format.
   *
   * The method serializes the DifferentialTimestampsContainer instance into the provided `differentialTimestampsContainerProtobuf`,
   * which is a pointer to the protobuf data. If the DifferentialTimestampsContainer instance is not set, no serialization will be performed.
   *
   * @param differentialTimestampsContainerProtobuf The pointer to the protobuf data to serialize into.
   */
  void serialize(DifferentialTimestampContainerProtobuf* differentialTimestampsContainerProtobuf) const final;

  /**
   * @brief [INTERFACE IMPLEMENTATION - DO NOT CALL]
   *
   * This method is part of an interface implementation and should not be called directly on the DifferentialTimestampsContainer class.
   * Its purpose is to fulfill the requirements of the interface, and calling it may lead to unintended behavior.
   *
   * @throws ShouldNotBeCalledException if called directly on the DifferentialTimestampsContainer class.
   */
  void switchDataForm() final;

  /**
   * @brief Equality comparison operator.
   *
   * The equality comparison operator (`operator==`) checks if the current DifferentialTimestampsContainer instance is equal
   * to the given `differentialTimestampsContainer` instance.
   *
   * @param differentialTimestampsContainer The IPCore instance of the DifferentialTimestampContainerProtobuf class to compare.
   * @return True if the instances are equal; otherwise, false.
   */
  bool operator==(const IPCore<DifferentialTimestampContainerProtobuf>& differentialTimestampsContainer) const noexcept final;

  /**
   * @brief Inequality comparison operator.
   *
   * The inequality comparison operator (`operator!=`) checks if the current DifferentialTimestampsContainer instance is not equal
   * to the given `differentialTimestampsContainer` instance.
   *
   * @param differentialTimestampsContainer The IPCore instance of the DifferentialTimestampContainerProtobuf class to compare.
   * @return True if the instances are not equal; otherwise, false.
   */
  bool operator!=(const IPCore<DifferentialTimestampContainerProtobuf>& differentialTimestampsContainer) const noexcept final;

  ////////////////////////////////////////////////////////////////
  //                     Calculate Methode                      //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Calculate the first Unix timestamp in milliseconds for a specific block.
   * @param blockIdx The index of the block.
   * @return The first Unix timestamp in milliseconds for the given block.
   */
  [[nodiscard]] UnixTimestamp calculateFirstUnixTimestampInBlock(const BlockIdx& blockIdx) const;

  /**
   * @brief Get the last Unix timestamp in milliseconds for a specific block.
   * @param blockIdx The index of the block.
   * @param firstUnixTimestampInBlockInMs The first Unix timestamp in milliseconds of the block.
   * @param lastDifferentialBlock The last differential block in the container.
   * @return The last Unix timestamp in milliseconds for the given block.
   */
  [[nodiscard]] UnixTimestamp calculateLastUnixTimestampInBlock(const BlockIdx& blockIdx,
                                                                UnixTimestamp firstUnixTimestampInBlockInMs,
                                                                const DifferentialBlock& lastDifferentialBlock) const;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Member representing the first Unix timestamp in milliseconds.
   *
   * The `firstUnixTimestampInMs` member stores the first Unix timestamp in milliseconds
   * for the DifferentialTimestampsContainer instance.
   */
  UnixTimestamp firstUnixTimestampInMs;

  /**
   * @brief Member representing the time differences in milliseconds between blocks.
   *
   * The `blocksDifferencesInMs` member is a vector that stores the time differences in milliseconds
   * between consecutive blocks in the DifferentialTimestampsContainer instance.
   */
  BlocksDifferences blocksDifferencesInMs;

  /**
   * @brief Member representing the time differences in milliseconds between timestamps.
   *
   * The `timestampsDifferencesInMs` member is a vector that stores the time differences in milliseconds
   * between consecutive timestamps in the DifferentialTimestampsContainer instance.
   */
  TimestampsDifferences timestampsDifferencesInMs;
};
}  // namespace PCore