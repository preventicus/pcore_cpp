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
#include "Sensor.h"
#include "protobuf/pcore.pb.h"

using namespace PCore;

/**
 * @typedef SensorsJson
 * @brief Alias for the JSON representation of sensor data.
 */
using SensorsJson = Json::Value;

/**
 * @typedef RawProtobuf
 * @brief Alias for the Protobuf representation of raw sensor data.
 */
using RawProtobuf = com::preventicus::pcore::Raw;

/**
 * @typedef Sensors
 * @brief Alias for a vector of sensor data.
 */
using Sensors = std::vector<Sensor>;

/**
 * @typedef RawJson
 * @brief Alias for the JSON representation of raw sensor data.
 */
using RawJson = Json::Value;

namespace PCore {
/**
 * @class Raw
 * @brief The Raw class represents a data structure containing sensor data in its raw form.
 *
 * The `Raw` class represents a data structure that contains sensor data in its raw form. It is used to store raw sensor data
 * from multiple sensors, and the data is organized in a vector of `Sensor` objects. The `Raw` class implements the `IPCore` interface,
 * allowing it to be serialized to Protobuf and JSON formats.
 */
class Raw final : public IPCore<RawProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a Raw instance with the given sensor data and data form.
   * @param sensors The vector of `Sensor` objects containing raw sensor data.
   * @param dataForm The data form of the raw sensor data (e.g., DATA_FORM_ABSOLUTE or DATA_FORM_DIFFERENTIAL).
   *
   * The `Raw` instance is constructed using the provided sensor data and data form. The sensor data is represented by a vector
   * of `Sensor` objects, and the data form specifies the format of the sensor data, such as whether it is in absolute or differential form.
   */
  explicit Raw(Sensors sensors, DataForm dataForm) noexcept;

  /**
   * @brief Constructor to initialize a Raw instance from the given Protobuf data.
   * @param rawProtobuf The Protobuf data with which to initialize the Raw instance.
   *
   * The `Raw` instance is constructed using the provided Protobuf data. The data is extracted from the `RawProtobuf` object,
   * and the sensor data and data form are set accordingly.
   */
  explicit Raw(const RawProtobuf& rawProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a Raw instance from the given JSON data.
   * @param rawJson The JSON data with which to initialize the Raw instance.
   * @param dataForm The data form of the raw sensor data (e.g., DATA_FORM_ABSOLUTE or DATA_FORM_DIFFERENTIAL).
   *
   * The `Raw` instance is constructed using the provided JSON data. The sensor data is extracted from the "sensors" key
   * in the JSON object, and the data form is provided as a separate parameter. The sensor data is organized as a vector
   * of `Sensor` objects.
   *
   * @note The provided JSON data should contain the required keys for the sensor data. Otherwise, the behavior is undefined.
   * @note The data form should be provided as a separate parameter, as it is not be directly available in the JSON data.
   * @param rawJson The JSON data with which to initialize the Raw instance.
   * @param dataForm The data form of the raw sensor data.
   *
   * @throw WrongValueException if dataform is differential and on first unix timestamp is negativ.
   */
  explicit Raw(const RawJson& rawJson, DataForm dataForm);

  /**
   * @brief Default constructor to create an empty Raw instance.
   *
   * The default constructor creates an empty Raw instance without any sensor data. The data form is set to `DATA_FORM_NONE`.
   */
  explicit Raw() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the vector of `Sensor` objects containing raw sensor data.
   * @return The vector of `Sensor` objects containing raw sensor data.
   *
   * The `getSensors` method returns the vector of `Sensor` objects containing raw sensor data.
   */
  [[nodiscard]] Sensors getSensors() const noexcept;

  /**
   * @brief Get the data form of the raw sensor data.
   * @return The data form of the raw sensor data.
   *
   * The `getDataFrom` method returns the data form of the raw sensor data (e.g., DATA_FORM_ABSOLUTE,
   * DATA_FORM_DIFFERENTIAL or DATA_FORM_NONE).
   */
  [[nodiscard]] DataForm getDataFrom() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the Raw instance is set.
   * @return `true` if the Raw instance is set, `false` otherwise.
   *
   * The `isSet` method checks whether the Raw instance is set. If the instance contains valid sensor data,
   * this method will return `true`. Otherwise, it will return `false`.
   *
   * @return `true` if the Raw instance is set or has valid data, `false` otherwise.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the Raw instance to a JSON data structure.
   * @return The JSON data structure representing the Raw instance.
   *
   * The `toJson` method converts the Raw instance to a JSON data structure represented by a `Json::Value` object.
   * The JSON data structure contains the sensor data and the data form of the Raw instance.
   *
   * @return The JSON data structure representing the Raw instance.
   */
  [[nodiscard]] RawJson toJson() const noexcept final;

  /**
   * @brief Serialize the Raw instance into a RawProtobuf object.
   * @param rawProtobuf The pointer to the RawProtobuf object where the data will be serialized.
   *
   * The `serialize` method serializes the Raw instance into an existing RawProtobuf object.
   * The sensor data and data form from the Raw instance will be stored in the provided `rawProtobuf` object.
   *
   * @note The `rawProtobuf` parameter must not be a null pointer. Providing a null pointer
   * will result in a `NullPointerException` being thrown.
   *
   * @param rawProtobuf The pointer to the RawProtobuf object where the data will be serialized.
   * @throws NullPointerException if the provided `rawProtobuf` parameter is a null pointer.
   */
  void serialize(RawProtobuf* rawProtobuf) const final;

  /**
   * @brief Switch the data form of the Raw instance.
   *
   * The `switchDataForm` method allows changing the data form of the Raw instance from `DATA_FORM_DIFFERENTIAL` to `DATA_FORM_ABSOLUTE`
   * or vice versa, depending on the current data form. The method may perform necessary conversions on the sensor data
   * to switch between the data forms.
   */
  void switchDataForm() noexcept final;

  /**
   * @brief Compare if two Raw instances are equal.
   * @param raw The other Raw instance to compare.
   * @return `true` if the two Raw instances are equal, `false` otherwise.
   *
   * The `operator==` method compares the current Raw instance with another Raw instance (`raw`) for equality.
   * The comparison is based on the content and structure of the instances, including the sensor data and data form.
   *
   * @param raw The other Raw instance to compare.
   * @return `true` if the two Raw instances are equal, `false` otherwise.
   */
  bool operator==(const IPCore<RawProtobuf>& raw) const noexcept final;

  /**
   * @brief Compare if two Raw instances are not equal.
   * @param raw The other Raw instance to compare.
   * @return `true` if the two Raw instances are not equal, `false` otherwise.
   *
   * The `operator!=` method compares the current Raw instance with another Raw instance (`raw`) for inequality.
   * The comparison is based on the content and structure of the instances, including the sensor data and data form.
   *
   * @param raw The other Raw instance to compare.
   * @return `true` if the two Raw instances are not equal, `false` otherwise.
   */
  bool operator!=(const IPCore<RawProtobuf>& raw) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief A vector containing the raw sensor data.
   */
  Sensors sensors;

  /**
   * @brief The data form of the raw sensor data, which can be either
   * `DATA_FORM_DIFFERENTIAL`, `DATA_FORM_ABSOLUTE` or `DATA_FORM_NONE`
   */
  DataForm dataForm;
};
}  // namespace PCore