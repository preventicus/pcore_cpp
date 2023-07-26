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
 * @typedef PpgMetaDataProtobuf
 * @brief Definition for the protobuf message type corresponding to PPG metadata.
 */
using PpgMetaDataProtobuf = com::preventicus::pcore::Raw_Sensor_Channel_PpgMetadata;

/**
 * @typedef Wavelength
 * @brief Alias for the wavelength data type used in PPG metadata.
 */
using Wavelength = uint32_t;

/**
 * @typedef PpgMetaDataJson
 * @brief Alias for the JSON data type used to represent PPG metadata.
 */
using PpgMetaDataJson = Json::Value;

/**
 * @brief Alias for an optional variant type that represents the light data in PPG metadata.
 *
 * The `Light` type is an optional variant type that can hold either a `Wavelength` value or
 * a `ColorProtobuf` value. It is used to represent the different types of light data that can be
 * present in PPG metadata.
 */
using Light = std::optional<std::variant<Wavelength, ColorProtobuf>>;

namespace PCore {
/**
 * @class PpgMetaData
 * @brief Represents metadata for a PPG (Photoplethysmography) sensor channel.
 *
 * The PpgMetaData class encapsulates metadata information for a PPG sensor channel. It contains optional light
 * information, which can be either a wavelength in nanometers (nm) or a ColorProtobuf enum representing the color.
 */
class PpgMetaData final : public IPCore<PpgMetaDataProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a PpgMetaData instance with the given color.
   * @param colorProtobuf The ColorProtobuf enum representing the color information.
   *
   * The PpgMetaData instance is constructed using the provided color information, encapsulated in the
   * ColorProtobuf enum. The light member is set to the provided color value.
   *
   * @note The colorProtobuf parameter should be a valid color value. Otherwise, the behavior is undefined.
   */
  explicit PpgMetaData(ColorProtobuf colorProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a PpgMetaData instance with the given wavelength.
   * @param wavelengthInNm The wavelength value in nanometers (nm).
   *
   * The PpgMetaData instance is constructed using the provided wavelength information. The light member is set to the
   * provided wavelength value in nanometers.
   *
   * @note The wavelengthInNm parameter should be a valid wavelength value. Otherwise, the behavior is undefined.
   */
  explicit PpgMetaData(Wavelength wavelengthInNm) noexcept;

  /**
   * @brief Constructor to initialize a PpgMetaData instance from the given protobuf data.
   * @param ppgMetaDataProtobuf The protobuf data with which to initialize the PpgMetaData instance.
   *
   * The PpgMetaData instance is constructed using the provided protobuf data, extracting the light information
   * from the appropriate field in the protobuf object. The light information can be either a wavelength in
   * nanometers (nm) or a ColorProtobuf enum representing the color.
   */
  explicit PpgMetaData(const PpgMetaDataProtobuf& ppgMetaDataProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a PpgMetaData instance from the given JSON data.
   * @param ppgMetaDataJson The JSON data with which to initialize the PpgMetaData instance.
   *
   * The PpgMetaData instance is constructed using the provided JSON data, extracting the light information from
   * the appropriate key in the JSON object. The light information can be either a wavelength in nanometers (nm) or a
   * ColorProtobuf enum representing the color.
   *
   * @note The provided JSON data should contain the required key for the light information.
   * Otherwise, the behavior is undefined.
   */
  explicit PpgMetaData(const PpgMetaDataJson& ppgMetaDataJson);

  /**
   * @brief Constructor to initialize an empty PpgMetaData instance.
   *
   * The PpgMetaData instance is constructed as an empty instance without any light information.
   */
  explicit PpgMetaData() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the light information of the PpgMetaData instance.
   * @tparam L The type of light information to retrieve (Wavelength or ColorProtobuf).
   * @return An optional containing the light information, if present. Otherwise, an empty optional is returned.
   */
  template <typename L>
  [[nodiscard]] std::optional<L> getLight() const noexcept;

  /**
   * @brief Check if the PpgMetaData instance has light information of a specific type.
   * @tparam L The type of light information to check for (Wavelength or ColorProtobuf).
   * @return true if the PpgMetaData instance contains light information of the specified type, false otherwise.
   */
  template <typename L>
  [[nodiscard]] bool hasLight() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the PpgMetaData instance is set with valid data.
   * @return true if the PpgMetaData instance is set with valid data, false otherwise.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the PpgMetaData instance to JSON format.
   *
   * The `toJson` method converts the PpgMetaData instance to a JSON object. The resulting JSON data
   * represents the PpgMetaData instance and includes the relevant information about the PPG metadata.
   *
   * If the PpgMetaData instance is not set, the method will return an empty JSON object.
   *
   * @return The JSON data representing the PpgMetaData instance.
   */
  [[nodiscard]] PpgMetaDataJson toJson() const noexcept final;

  /**
   * @brief Serialize the PpgMetaData instance to protobuf format.
   *
   * The `serialize` method serializes the PpgMetaData instance into a protobuf data structure.
   * It populates the provided `ppgMetaDataProtobuf` pointer with the relevant data from the PpgMetaData instance.
   *
   * @param ppgMetaDataProtobuf The pointer to the protobuf data to serialize into.
   * @throw NullPointerException is ppgMetaDataProtobuf is null
   */
  void serialize(PpgMetaDataProtobuf* ppgMetaDataProtobuf) const final;

  /**
   * @brief [INTERFACE IMPLEMENTATION - DO NOT CALL]
   *
   * This method is part of an interface implementation and should not be called directly on the PpgMetaData class.
   * Its purpose is to fulfill the requirements of the interface, and calling it may lead to unintended behavior.
   *
   * @throws ShouldNotBeCalledException if called directly on the PpgMetaData class.
   */
  void switchDataForm() final;

  /**
   * @brief Check if two PpgMetaData instances are equal.
   * @param ppgMetaData The other PpgMetaData instance to compare with.
   * @return true if the two PpgMetaData instances are equal, false otherwise.
   */
  bool operator==(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const noexcept final;

  /**
   * @brief Check if two PpgMetaData instances are not equal.
   * @param ppgMetaData The other PpgMetaData instance to compare with.
   * @return true if the two PpgMetaData instances are not equal, false otherwise.
   */
  bool operator!=(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Member representing the light data in PPG metadata.
   *
   * The `light` member is an optional variant type that can hold either a `Wavelength` value or
   * a `ColorProtobuf` value. It represents the light data present in PPG metadata. If the PPG metadata
   * contains wavelength information, it will be stored in this member as a `Wavelength`. If it contains
   * color information, it will be stored as a `ColorProtobuf`.
   *
   * @note The `light` member may be unset (empty) if no light data is present in the PPG metadata.
   */
  Light light;
};
}  // namespace PCore