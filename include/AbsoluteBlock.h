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

/**
 * @typedef AbsoluteValue
 * @brief Type alias for an absolute value.
 *
 * The AbsoluteValue type is an alias for the underlying integer type (int32_t).
 * It represents an absolute value in the context of the application.
 */
using AbsoluteValue = int32_t;

/**
 * @typedef AbsoluteValues
 * @brief Type alias for a collection of absolute values.
 *
 * The AbsoluteValues type is an alias for the standard vector of AbsoluteValue.
 * It represents a collection of absolute values used in the application.
 */
using AbsoluteValues = std::vector<AbsoluteValue>;

/**
 * @typedef AbsoluteValuesJson
 * @brief Type alias for JSON representation of absolute values.
 *
 * The AbsoluteValuesJson type is an alias for the JSON value representation.
 * It is used to store and handle absolute values in JSON format.
 */
using AbsoluteValuesJson = Json::Value;

/**
 * @typedef AbsoluteBlockJson
 * @brief Type alias for JSON representation of an absolute block.
 *
 * The AbsoluteBlockJson type is an alias for the JSON value representation.
 * It is used to store and handle absolute blocks in JSON format.
 */
using AbsoluteBlockJson = Json::Value;

namespace PCore {
/**
 * @class AbsoluteBlock
 * @brief The AbsoluteBlock class represents an absolute block.
 *
 * This class manages AbsoluteValues, which contains the absolute values.
 */
class AbsoluteBlock final {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize an AbsoluteBlock instance with the given absolute values.
   * @param absoluteValues The absolute values with which to initialize the AbsoluteBlock instance.
   */
  explicit AbsoluteBlock(AbsoluteValues absoluteValues) noexcept;

  /**
   * @brief Constructor to initialize an AbsoluteBlock instance from the given JSON data.
   * @param absoluteBlockJson The JSON data with which to initialize the AbsoluteBlock instance.
   *
   * The constructor takes a JSON object (AbsoluteBlockJson) as input and initializes the AbsoluteBlock instance
   * with the values extracted from the JSON data. It allows creating an AbsoluteBlock object from a JSON representation.
   *
   * @note The JSON data must conform to the expected format for AbsoluteBlock objects, otherwise the behavior is undefined.
   */
  explicit AbsoluteBlock(const AbsoluteBlockJson& absoluteBlockJson) noexcept;

  /**
   * @brief Default constructor to create an empty AbsoluteBlock instance.
   */
  explicit AbsoluteBlock() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the contained absolute values.
   * @return The contained absolute values.
   */
  [[nodiscard]] AbsoluteValues getAbsoluteValues() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                       Public Methods                       //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the AbsoluteBlock instance is set.
   * @return true if the AbsoluteBlock instance is set, otherwise false.
   */
  [[nodiscard]] bool isSet() const noexcept;

  /**
   * @brief Convert the AbsoluteBlock instance to a JSON data structure.
   * @return The JSON data structure representing the AbsoluteBlock instance.
   *
   * The `toJson` method serializes the AbsoluteBlock instance into a JSON object (AbsoluteBlockJson).
   * It captures the relevant data from the AbsoluteBlock and returns it as a JSON representation.
   */
  [[nodiscard]] AbsoluteBlockJson toJson() const noexcept;

  /**
   * @brief Check if this AbsoluteBlock instance is equal to another AbsoluteBlock instance.
   * @param absoluteBlock The other AbsoluteBlock instance for comparison.
   * @return true if the AbsoluteBlock instances are equal, otherwise false.
   */
  bool operator==(const AbsoluteBlock& absoluteBlock) const noexcept;

  /**
   * @brief Check if this AbsoluteBlock instance is not equal to another AbsoluteBlock instance.
   * @param absoluteBlock The other AbsoluteBlock instance for comparison.
   * @return true if the AbsoluteBlock instances are not equal, otherwise false.
   */
  bool operator!=(const AbsoluteBlock& absoluteBlock) const noexcept;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief The contained absolute values.
   */
  AbsoluteValues absoluteValues;
};
}  // namespace PCore