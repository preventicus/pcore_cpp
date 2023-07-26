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
#include "AbsoluteBlock.h"
#include "IPCore.h"
#include "protobuf/pcore_raw.pb.h"

using namespace PCore;

/**
 * @typedef HeaderProtobuf
 * @brief Alias for the Protocol Buffer representation of DifferentialBlock.
 */
using DifferentialBlockProtobuf = com::preventicus::pcore::Raw_Sensor_Channel_DifferentialBlock;

/**
 * @typedef DifferentialValue
 * @brief Alias for the data type of a single differential value.
 */
using DifferentialValue = int32_t;

/**
 * @typedef DifferentialValues
 * @brief Alias for a collection of differential values.
 */
using DifferentialValues = std::vector<DifferentialValue>;

/**
 * @typedef DifferentialValuesJson
 * @brief Alias for the JSON representation of differential values.
 */
using DifferentialValuesJson = Json::Value;

/**
 * @typedef DifferentialBlockJson
 * @brief Alias for the JSON representation of a single DifferentialBlock.
 */
using DifferentialBlockJson = Json::Value;

namespace PCore {
/**
 * @class DifferentialBlock
 * @brief Class representing a DifferentialBlock containing a collection of differential values.
 */
class DifferentialBlock final : public IPCore<DifferentialBlockProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a DifferentialBlock instance with the given differential values.
   * @param differentialValues The collection of differential values to initialize the DifferentialBlock instance.
   */
  explicit DifferentialBlock(DifferentialValues differentialValues) noexcept;

  /**
   * @brief Constructor to initialize a DifferentialBlock instance from the given DifferentialBlockProtobuf data.
   * @param differentialBlockProtobuf The DifferentialBlockProtobuf data with which to initialize the DifferentialBlock instance.
   */
  explicit DifferentialBlock(const DifferentialBlockProtobuf& differentialBlockProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a DifferentialBlock instance from the given JSON data.
   * @param dataJson The JSON data with which to initialize the DifferentialBlock instance.
   *
   * The `DifferentialBlock` instance is constructed using the provided JSON data, extracting the differentialValues
   * content from the appropriate keys in the JSON object.
   *
   * @note The provided JSON data should contain the required key for the differentialValues data.
   * Otherwise, the behavior is undefined.
   */
  explicit DifferentialBlock(const DifferentialBlockJson& differentialBlockJson) noexcept;

  /**
   * @brief Default constructor to create an empty DifferentialBlock instance.
   */
  explicit DifferentialBlock() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the collection of differential values stored in the DifferentialBlock.
   * @return The collection of differential values.
   */
  [[nodiscard]] DifferentialValues getDifferentialValues() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the DifferentialBlock instance is set (contains valid data).
   * @return True if the DifferentialBlock is set, false otherwise.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the DifferentialBlock instance to a JSON data structure.
   * @return The JSON data structure representing the DifferentialBlock instance.
   *
   * The `toJson` method converts the DifferentialBlock instance into a JSON data structure (DifferentialBlockJson).
   * If the DifferentialBlock instance is not set, an empty JSON object will be returned.
   *
   */
  [[nodiscard]] DifferentialBlockJson toJson() const noexcept final;

  /**
   * @brief Serialize the DifferentialBlock instance into a DifferentialBlockProtobuf object.
   * @param differentialBlockProtobuf The pointer to the DifferentialBlockProtobuf object where the data will be serialized.
   *
   * The `serialize` method serializes the DifferentialBlock instance into an existing DifferentialBlockProtobuf object.
   * The data from the DifferentialBlock instance will be stored in the provided `differentialBlockProtobuf` object.
   *
   * @note The `differentialBlockProtobuf` parameter must not be a null pointer. Providing a null pointer
   * will result in a `NullPointerException` being thrown.
   *
   * @param differentialBlockProtobuf The pointer to the DifferentialBlockProtobuf object where the data will be serialized.
   * @throws NullPointerException if the provided `differentialBlockProtobuf` parameter is a null pointer.
   */
  void serialize(DifferentialBlockProtobuf* differentialBlockProtobuf) const final;

  /**
   * @brief [INTERFACE IMPLEMENTATION - DO NOT CALL]
   *
   * This method is part of an interface implementation and should not be called directly on the DifferentialBlock class.
   * Its purpose is to fulfill the requirements of the interface, and calling it may lead to unintended behavior.
   *
   * @throws ShouldNotBeCalledException if called directly on the DifferentialBlock class.
   */
  void switchDataForm() final;

  /**
   * @brief  Check if this DifferentialBlock instance is equal to another DifferentialBlock instance.
   * @param differentialBlock The DifferentialBlock instance to compare with.
   * @return True if the two instances are equal, false otherwise.
   */
  bool operator==(const IPCore<DifferentialBlockProtobuf>& differentialBlock) const noexcept final;

  /**
   * @brief Check if this DifferentialBlock instance is not equal to another DifferentialBlock instance.
   * @param differentialBlock The DifferentialBlock instance to compare with.
   * @return True if the two instances are not equal, false otherwise.
   */
  bool operator!=(const IPCore<DifferentialBlockProtobuf>& differentialBlock) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief The collection of differential values stored in the DifferentialBlock.
   */
  DifferentialValues differentialValues;
};
}  // namespace PCore