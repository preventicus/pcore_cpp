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
#include "IPCore.h"
#include "PcoreProtobuf.h"
#include "json/json.h"

/**
 * @typedef AccMetaDataProtobuf
 * @brief Type alias for the Protobuf representation of Accelerometer Metadata.
 *
 * The AccMetaDataProtobuf type is an alias for the specific Protobuf data structure (com::preventicus::pcore::Raw_Sensor_Channel_AccMetadata).
 * It represents Accelerometer Metadata in the application using Protobuf format.
 */
using AccMetaDataProtobuf = com::preventicus::pcore::Raw_Sensor_Channel_AccMetadata;

/**
 * @typedef AccMetaDataJson
 * @brief Type alias for JSON representation of Accelerometer Metadata.
 *
 * The AccMetaDataJson type is an alias for the JSON value representation (Json::Value).
 * It is used to store and handle Accelerometer Metadata in JSON format.
 */
using AccMetaDataJson = Json::Value;

/**
 * @typedef Type
 * @brief Type alias for an optional variant of Accelerometer Metadata types.
 *
 * The Type type is an alias for the std::optional containing a std::variant of CoordinateProtobuf and NormProtobuf.
 * It represents the optional data type for Accelerometer Metadata in the application, allowing flexibility in data handling.
 */
using Type = std::optional<std::variant<CoordinateProtobuf, NormProtobuf>>;

namespace PCore {
/**
 * @class AccMetaData
 * @brief Class representing Accelerometer Metadata.
 *
 * This class manages Accelerometer Metadata, which can have either NormProtobuf or CoordinateProtobuf data types.
 */
class AccMetaData final : public IPCore<AccMetaDataProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize an AccMetaData instance with NormProtobuf data.
   * @param norm The NormProtobuf data with which to initialize the AccMetaData instance.
   */
  explicit AccMetaData(NormProtobuf norm) noexcept;

  /**
   * @brief Constructor to initialize an AccMetaData instance with CoordinateProtobuf data.
   * @param coordinate The CoordinateProtobuf data with which to initialize the AccMetaData instance.
   */
  explicit AccMetaData(CoordinateProtobuf coordinate) noexcept;

  /**
   * @brief Constructor to initialize an AccMetaData instance from the given AccMetaDataProtobuf data.
   * @param accMetaDataProtobuf The AccMetaDataProtobuf data with which to initialize the AccMetaData instance.
   *
   * This constructor takes a Protobuf object (AccMetaDataProtobuf) as input and initializes the
   * AccMetaData instance with the values extracted from the Protobuf data. It allows creating
   * an AccMetaData object from a Protobuf representation.
   *
   * @note The AccMetaDataProtobuf data must be in the expected format for AccMetaData objects,
   * otherwise the behavior is undefined.
   */
  explicit AccMetaData(const AccMetaDataProtobuf& accMetaDataProtobuf) noexcept;

  /**
   * @brief Constructor to initialize an AccMetaData instance from the given JSON data.
   * @param accMetaDataJson The JSON data with which to initialize the AccMetaData instance.
   *
   * This constructor takes a JSON object (AccMetaDataJson) as input and initializes the
   * AccMetaData instance with the values extracted from the JSON data. It allows creating
   * an AccMetaData object from a JSON representation.
   *
   * @note The JSON data must conform to the expected format for AccMetaData objects,
   * otherwise the behavior is undefined.
   */
  explicit AccMetaData(const AccMetaDataJson& accMetaDataJson);

  /**
   * @brief Default constructor to create an empty AccMetaData instance.
   */
  explicit AccMetaData() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the optional type of AccMetaData.
   * @tparam T The specific data type to retrieve (NormProtobuf or CoordinateProtobuf).
   * @return An optional containing the type if available, or empty if the type is not present.
   */
  template <typename T>
  [[nodiscard]] std::optional<T> getType() const noexcept;

  /**
   * @brief Check if the AccMetaData instance has a specific data type.
   * @tparam T The specific data type to check (NormProtobuf or CoordinateProtobuf).
   * @return true if the AccMetaData instance has the specified data type, otherwise false.
   */
  template <typename T>
  [[nodiscard]] bool hasType() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the AccMetaData instance is set.
   * @return true if the AccMetaData instance is set, otherwise false.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the AccMetaData instance to a JSON data structure.
   * @return The JSON data structure representing the AccMetaData instance.
   *
   * The `toJson` method serializes the AccMetaData instance into a JSON object (AccMetaDataJson).
   * The data from the AccMetaData instance will be stored in the returned JSON object, following the
   * specified JSON format for AccMetaData.
   *
   * If the AccMetaData instance is not set (contains neither CoordinateProtobuf nor NormProtobuf data),
   * the method will return an empty JSON object.
   */
  [[nodiscard]] AccMetaDataJson toJson() const noexcept final;

  /**
   * @brief Serialize the AccMetaData instance into an AccMetaDataProtobuf object.
   * @param accMetaDataProtobuf The pointer to the AccMetaDataProtobuf object where the data will be serialized.
   *
   * The `serialize` method serializes the AccMetaData instance into an existing AccMetaDataProtobuf object.
   * The data from the AccMetaData instance will be stored in the provided `accMetaDataProtobuf` object.
   *
   * @note The `accMetaDataProtobuf` parameter must not be a null pointer. Providing a null pointer
   * will result in a `NullPointerException` being thrown.
   *
   * @note If the AccMetaData instance is not set (contains neither CoordinateProtobuf nor NormProtobuf data),
   * this method will return without modifying the `accMetaDataProtobuf`.
   *
   * @param accMetaDataProtobuf The pointer to the AccMetaDataProtobuf object where the data will be serialized.
   * @throws NullPointerException if the provided `accMetaDataProtobuf` parameter is a null pointer.
   */
  void serialize(AccMetaDataProtobuf* accMetaDataProtobuf) const final;

  /**
   * @brief [INTERFACE IMPLEMENTATION - DO NOT CALL]
   *
   * This method is part of an interface implementation and should not be called directly on the AccMetaData class.
   * Its purpose is to fulfill the requirements of the interface, and calling it may lead to unintended behavior.
   *
   * @throws ShouldNotBeCalledException if called directly on the AccMetaData class.
   */
  void switchDataForm() final;

  /**
   * @brief Check if this AccMetaData instance is equal to another AccMetaData instance.
   * @param accMetaData The other AccMetaData instance for comparison.
   * @return true if the AccMetaData instances are equal, otherwise false.
   */
  bool operator==(const IPCore<AccMetaDataProtobuf>& accMetaData) const noexcept final;

  /**
   * @brief Check if this AccMetaData instance is not equal to another AccMetaData instance.
   * @param accMetaData The other AccMetaData instance for comparison.
   * @return true if the AccMetaData instances are not equal, otherwise false.
   */
  bool operator!=(const IPCore<AccMetaDataProtobuf>& accMetaData) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief The optional type of AccMetaData (NormProtobuf or CoordinateProtobuf).
   */
  Type type;
};
}  // namespace PCore