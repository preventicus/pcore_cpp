/*

Created by Jakob Glueck, Steve Merschel 2023

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

#pragma once

#include "AbsoluteTimestampsContainer.h"
#include "Channel.h"
#include "DifferentialTimestampsContainer.h"
#include "IPCore.h"
#include "protobuf/pcore_raw.pb.h"

using namespace PCore;

/**
 * @typedef Channels
 * @brief Alias for a channels vector.
 */
using Channels = std::vector<Channel>;

/**
 * @typedef SensorJson
 * @brief Alias for a JSON value representing a sensor.
 */
using SensorJson = Json::Value;

/**
 * @typedef Duration
 * @brief Alias for a duration value in milliseconds.
 */
using Duration = uint64_t;

/**
 * @typedef ChannelsJson
 * @brief Alias for a JSON value representing a list of channels.
 */
using ChannelsJson = Json::Value;

/**
 * @typedef Timestamps
 * @brief Alias for an optional variant of AbsoluteTimestampsContainer or DifferentialTimestampsContainer.
 */
using Timestamps = std::optional<std::variant<AbsoluteTimestampsContainer, DifferentialTimestampsContainer>>;

namespace PCore {
/**
 * @class Sensor
 * @brief Class representing a sensor with associated channels and timestamps.
 *
 * The `Sensor` class represents a sensor in the PCore data format, which can contain multiple channels
 * and timestamps. The `Sensor` instance can be constructed using the provided channels, timestamps, and
 * sensor type. The channels and timestamps are stored in the appropriate member variables, and the data
 * form is determined based on the provided timestamps during construction.
 */
class Sensor final : public IPCore<SensorProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a Sensor instance with differential timestamps.
   * @param channels The list of channels associated with the sensor.
   * @param differentialTimestampsContainer The differential timestamps for the sensor.
   * @param sensorTypeProtobuf The protobuf representation of the sensor type.
   */
  explicit Sensor(Channels channels, DifferentialTimestampsContainer differentialTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a Sensor instance with absolute timestamps.
   * @param channels The list of channels associated with the sensor.
   * @param absoluteTimestampsContainer The absolute timestamps for the sensor.
   * @param sensorTypeProtobuf The protobuf representation of the sensor type.
   */
  explicit Sensor(Channels channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a Sensor instance from the given JSON data.
   * @param sensorJson The JSON data with which to initialize the Sensor instance.
   * @param dataForm The data form (absolute or differential) used for the sensor timestamps.
   *
   * The `Sensor` instance is constructed using the provided JSON data, extracting the channels,
   * timestamps, and sensor type from the appropriate keys in the JSON object. The data form is
   * specified during initialization and is used to determine how timestamps are represented.
   *
   * @note The provided JSON data should contain the required keys for channels, timestamps, and
   * sensor type. Otherwise, the behavior is undefined.
   *
   * @param sensorJson The JSON data with which to initialize the Sensor instance.
   * @param dataForm The data form (absolute or differential) used for the sensor timestamps.
   *
   * @throw WrongValueException if the fist unix timestamp in the DifferentialTimestampsContainer is negativ
   */
  explicit Sensor(const SensorJson& sensorJson, DataForm dataForm);

  /**
   * @brief Constructor to initialize a Sensor instance from the given protobuf data.
   * @param sensorProtobuf The protobuf data with which to initialize the Sensor instance.
   */
  explicit Sensor(const SensorProtobuf& sensorProtobuf) noexcept;

  /**
   * @brief Default constructor to create an empty Sensor instance.
   */
  explicit Sensor() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the sensor type of the Sensor instance.
   * @return The protobuf representation of the sensor type.
   */
  [[nodiscard]] SensorTypeProtobuf getSensorType() const noexcept;

  /**
   * @brief Get the list of channels associated with the Sensor instance.
   * @return The list of channels.
   */
  [[nodiscard]] Channels getChannels() const noexcept;

  /**
   * @brief Get the timestamps associated with the Sensor instance.
   * @tparam T The type of timestamps (AbsoluteTimestampsContainer or DifferentialTimestampsContainer).
   * @return The optional variant containing the timestamps, or an empty optional if no timestamps are set.
   */
  template <typename T>
  [[nodiscard]] std::optional<T> getTimestamps() const noexcept;

  /**
   * @brief Check if the Sensor instance has timestamps of the specified type.
   * @tparam T The type of timestamps (AbsoluteTimestampsContainer or DifferentialTimestampsContainer).
   * @return True if the timestamps of the specified type are set, false otherwise.
   */
  template <typename T>
  [[nodiscard]] bool hasTimestamps() const noexcept;

  /**
   * @brief Get the data form used for the timestamps of the Sensor instance.
   * @return The data form (absolute or differential) used for the timestamps.
   */
  [[nodiscard]] DataForm getDataFrom() const noexcept;

  /**
   * @brief Get the first Unix timestamp in milliseconds for the Sensor instance.
   * @return The first Unix timestamp in milliseconds.
   */
  [[nodiscard]] UnixTimestamp getFirstUnixTimestampInMs() const noexcept;

  /**
   * @brief Get the last Unix timestamp in milliseconds for the Sensor instance.
   * @return The last Unix timestamp in milliseconds.
   */
  [[nodiscard]] UnixTimestamp getLastUnixTimestampInMs() const noexcept;

  /**
   * @brief Get the duration of the data in milliseconds for the Sensor instance.
   * @return The duration of the data in milliseconds.
   */
  [[nodiscard]] Duration getDurationInMs() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                     Interface Methode                      //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the Sensor instance is set with valid data.
   * @return True if the Sensor instance is set, false otherwise.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the Sensor instance to JSON format.
   *
   * This function converts the Sensor instance to a JSON data representation. It constructs a JSON object
   * containing the sensor's channels and associated timestamps. The data form of the timestamps (either absolute
   * or differential) is determined, and the corresponding timestamps are included in the JSON object. The sensor
   * type is also included in the JSON object.
   *
   * @return The JSON data representing the Sensor instance.
   *
   * @note If the Sensor instance is not set, an empty JSON object is returned.
   */
  [[nodiscard]] SensorJson toJson() const noexcept final;

  /**
   * @brief Serialize the Sensor instance to protobuf format.
   *
   * This function serializes the Sensor instance to the protobuf format. It populates the given SensorProtobuf
   * pointer with the sensor's channels and associated timestamps. The data form of the timestamps (either absolute
   * or differential) is checked, and only the differential timestamps are serialized. If the data form is not
   * differential, a WrongDataFormException is thrown, as differential timestamps are expected in this method.
   *
   * If the Sensor not set the method returns an empty sensorProtobuf.
   *
   * @param sensorProtobuf The pointer to the protobuf data to serialize into.
   *
   * @throws NullPointerException If the sensorProtobuf pointer is null.
   * @throws WrongDataFormException If the data form is not differential.
   */
  void serialize(SensorProtobuf* sensorProtobuf) const final;

  /**
   * @brief Switch the data form of the Sensor instance from AbsoluteTimestampsContainer to DifferentialTimestampsContainer.
   *
   * This method switches the data form of the Sensor instance from absolute timestamps to differential timestamps.
   *
   * @note The function modifies the Sensor instance by updating the data form and timestamps, as well as calling
   *       switchDataForm() on each channel.
   */
  void switchDataForm() noexcept final;

  /**
   * @brief Check if two Sensor instances are equal.
   * @param sensor The Sensor instance to compare with.
   * @return True if the Sensor instances are equal, false otherwise.
   */
  bool operator==(const IPCore<SensorProtobuf>& sensor) const noexcept final;

  /**
   * @brief Check if two Sensor instances are not equal.
   * @param sensor The Sensor instance to compare with.
   * @return True if the Sensor instances are not equal, false otherwise.
   */
  bool operator!=(const IPCore<SensorProtobuf>& sensor) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Calculate absolute timestamps from differential timestamps.
   * @param differentialTimestampsContainer The differential timestamps to convert.
   * @return The absolute timestamps converted from the differential timestamps.
   */
  [[nodiscard]] AbsoluteTimestampsContainer calculateAbsoluteTimestamps(
      const DifferentialTimestampsContainer& differentialTimestampsContainer) const noexcept;

  /**
   * @brief Calculate differential timestamps from absolute timestamps and block indices.
   * @param absoluteTimestampsContainer The absolute timestamps to convert.
   * @param blockIdxs The block indices to specify the DifferentialBlocks.
   * @return The differential timestamps converted from the absolute timestamps and block indices.
   */
  [[nodiscard]] DifferentialTimestampsContainer calculateDifferentialTimestamps(const AbsoluteTimestampsContainer& absoluteTimestampsContainer,
                                                                                const BlockIdxs& blockIdxs) const noexcept;

  /**
   * @brief Find the block indices for the Sensor instance.
   * @return The block indices specifying the locations where the absolute data is to be split.
   */
  [[nodiscard]] BlockIdxs findBlockIdxs() const noexcept;

  /**
   * @brief Calculate the first Unix timestamp in milliseconds for the last block of the Sensor instance.
   * @return The first Unix timestamp in milliseconds for the last block.
   */
  [[nodiscard]] UnixTimestamp calculateFirstUnixTimestampInLastBlock() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief The sensor type of the Sensor instance.
   */
  SensorTypeProtobuf sensorType;

  /**
   * @brief The list of channels associated with the Sensor instance.
   */
  Channels channels;

  /**
   * @brief The timestamps associated with the Sensor instance.
   */
  Timestamps timestamps;
};
}  // namespace PCore