/*

Created by Steve Merschel 2023

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
#include "json/json.h"
namespace PCore {

/**
 * @brief The IPCore class is an abstract base class for representing data structures that can be serialized to Protobuf and JSON formats.
 * @tparam T The Protobuf message type that the class can be serialized to.
 *
 * The `IPCore` class is a templated abstract base class that defines the interface for data structures that can be serialized to Protobuf
 * and JSON formats. Classes inheriting from `IPCore` are expected to implement the serialization methods and other required functionalities.
 * The `IPCore` class provides pure virtual methods that need to be overridden by derived classes.
 *
 * @tparam T The Protobuf message type that the class can be serialized to.
 */
template <typename T>
class IPCore {
 public:
  /**
   * @brief Serialize the data into a Protobuf object.
   * @param protobuf A pointer to the Protobuf object where the data will be serialized.
   *
   * The `serialize` method takes a pointer to a Protobuf object and serializes the data into it.
   * The data from the class instance will be stored in the provided `protobuf` object.
   *
   * @note The `protobuf` parameter must not be a null pointer. If provided a null pointer a
   * NullPointerException should be thrown.
   *
   * @param protobuf A pointer to the Protobuf object where the data will be serialized.
   */
  virtual void serialize(T* protobuf) const = 0;

  /**
   * @brief Convert the data instance to a JSON data structure.
   * @return The JSON data structure representing the data instance.
   *
   * The `toJson` method converts the data instance to a JSON data structure represented by a `Json::Value` object.
   * The JSON data structure can be used to easily inspect and work with the data in JSON format.
   *
   * @return The JSON data structure representing the data instance.
   */
  [[nodiscard]] virtual Json::Value toJson() const = 0;

  /**
   * @brief Switch the data form of the instance.
   *
   * The `switchDataForm` method allows changing the data form of the instance, depending on the specific implementation.
   * The behavior of this method is implementation-specific and should be defined by the derived classes.
   *
   * @note If the instance is not set or if there is no specific behavior to switch data form, this method may be a no-op.
   */
  virtual void switchDataForm() = 0;

  /**
   * @brief Check if the instance is set or has valid data.
   * @return `true` if the instance is set or has valid data, `false` otherwise.
   *
   * The `isSet` method checks whether the instance is set with valid data. The exact criteria for an instance to be considered "set"
   * depend on the specific implementation and should be defined by the derived classes.
   *
   * @return `true` if the instance is set or has valid data, `false` otherwise.
   */
  [[nodiscard]] virtual bool isSet() const = 0;

  /**
   * @brief Compare if two IPCore instances are equal.
   * @param pcore The other IPCore instance to compare.
   * @return `true` if the two IPCore instances are equal, `false` otherwise.
   *
   * The `operator==` method compares the current IPCore instance with another IPCore instance (`pcore`) for equality.
   * The comparison should be based on the content and structure of the instances, and the exact comparison criteria
   * depend on the specific implementation of the derived classes.
   *
   * @param pcore The other IPCore instance to compare.
   * @return `true` if the two IPCore instances are equal, `false` otherwise.
   */
  virtual bool operator==(const IPCore& pcore) const = 0;

  /**
   * @brief Compare if two IPCore instances are not equal.
   * @param pcore The other IPCore instance to compare.
   * @return `true` if the two IPCore instances are not equal, `false` otherwise.
   *
   * The `operator!=` method compares the current IPCore instance with another IPCore instance (`pcore`) for inequality.
   * The comparison should be based on the content and structure of the instances, and the exact comparison criteria
   * depend on the specific implementation of the derived classes.
   *
   * @param pcore The other IPCore instance to compare.
   * @return `true` if the two IPCore instances are not equal, `false` otherwise.
   */
  virtual bool operator!=(const IPCore& pcore) const = 0;
};
}  // namespace PCore