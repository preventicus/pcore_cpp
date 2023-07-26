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
#include <json/json.h>
#include <vector>
#include "UnixTimestamp.h"

/**
 * @typedef UnixTimestamps
 * @brief Type alias for a collection of Unix timestamps.
 *
 * The UnixTimestamps type is an alias for the standard vector of UnixTimestamp.
 * It represents a collection of Unix timestamps used in the application.
 */
using UnixTimestamps = std::vector<UnixTimestamp>;

/**
 * @typedef AbsoluteTimestampsContainerJson
 * @brief Type alias for JSON representation of an AbsoluteTimestampsContainer.
 *
 * The AbsoluteTimestampsContainerJson type is an alias for the JSON value representation.
 * It is used to store and handle AbsoluteTimestampsContainer in JSON format.
 */
using AbsoluteTimestampsContainerJson = Json::Value;

/**
 * @typedef UnixTimestampsJson
 * @brief Type alias for JSON representation of Unix timestamps.
 *
 * The UnixTimestampsJson type is an alias for the JSON value representation.
 * It is used to store and handle Unix timestamps in JSON format.
 */
using UnixTimestampsJson = Json::Value;

namespace PCore {
/**
 * @class AbsoluteTimestampsContainer
 * @brief The AbsoluteTimestampsContainer class represents a container for absolute timestamps.
 *
 * This class manages UnixTimestamps in milliseconds.
 */
class AbsoluteTimestampsContainer final {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize an AbsoluteTimestampsContainer instance with the given UnixTimestamps in milliseconds.
   * @param unixTimestampsInMs The UnixTimestamps in milliseconds with which to initialize the AbsoluteTimestampsContainer instance.
   */
  explicit AbsoluteTimestampsContainer(UnixTimestamps unixTimestampsInMs) noexcept;

  /**
   * @brief Constructor to initialize an AbsoluteTimestampsContainer instance from the given JSON data.
   * @param absoluteTimestampContainerJson The JSON data with which to initialize the AbsoluteTimestampsContainer instance.
   *
   * This constructor takes a JSON object (AbsoluteTimestampsContainerJson) as input and initializes the
   * AbsoluteTimestampsContainer instance with the values extracted from the JSON data. It allows creating
   * an AbsoluteTimestampsContainer object from a JSON representation.
   *
   * @note The JSON data must conform to the expected format for AbsoluteTimestampsContainer objects,
   * otherwise the behavior is undefined.
   */
  explicit AbsoluteTimestampsContainer(const AbsoluteTimestampsContainerJson& absoluteTimestampContainerJson) noexcept;

  /**
   * @brief Default constructor to create an empty AbsoluteTimestampsContainer instance.
   */
  explicit AbsoluteTimestampsContainer() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the contained UnixTimestamps in milliseconds.
   * @return The contained UnixTimestamps in milliseconds.
   */
  [[nodiscard]] UnixTimestamps getUnixTimestampsInMs() const noexcept;

  /**
   * @brief Get the first UnixTimestamp in milliseconds from the container.
   * @return The first UnixTimestamp in milliseconds from the container.
   */
  [[nodiscard]] UnixTimestamp getFirstUnixTimestampInMs() const noexcept;

  /**
   * @brief Get the last UnixTimestamp in milliseconds from the container.
   * @return The last UnixTimestamp in milliseconds from the container.
   */
  [[nodiscard]] UnixTimestamp getLastUnixTimestampInMs() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                       Public Methods                       //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the AbsoluteTimestampsContainer instance is set.
   * @return true if the AbsoluteTimestampsContainer instance is set, otherwise false.
   */
  [[nodiscard]] bool isSet() const noexcept;

  /**
   * @brief Convert the AbsoluteTimestampsContainer instance to a JSON data structure.
   * @return The JSON data structure representing the AbsoluteTimestampsContainer instance.
   *
   * The `toJson` method serializes the AbsoluteTimestampsContainer instance into a JSON object (AbsoluteTimestampsContainerJson).
   * It captures the relevant data from the AbsoluteTimestampsContainer and returns it as a JSON representation.
   */
  [[nodiscard]] AbsoluteTimestampsContainerJson toJson() const noexcept;

  /**
   * @brief Check if this AbsoluteTimestampsContainer instance is equal to another AbsoluteTimestampsContainer instance.
   * @param absoluteTimestampsContainer The other AbsoluteTimestampsContainer instance for comparison.
   * @return true if the AbsoluteTimestampsContainer instances are equal, otherwise false.
   */
  bool operator==(const AbsoluteTimestampsContainer& absoluteTimestampsContainer) const noexcept;

  /**
   * @brief Check if this AbsoluteTimestampsContainer instance is not equal to another AbsoluteTimestampsContainer instance.
   * @param absoluteTimestampsContainer The other AbsoluteTimestampsContainer instance for comparison.
   * @return true if the AbsoluteTimestampsContainer instances are not equal, otherwise false.
   */
  bool operator!=(const AbsoluteTimestampsContainer& absoluteTimestampsContainer) const noexcept;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief The contained UnixTimestamps in milliseconds.
   */
  UnixTimestamps unixTimestampsInMs;
};
}  // namespace PCore