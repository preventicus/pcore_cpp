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
#include "Header.h"
#include "IPCore.h"
#include "PcoreJson.h"
#include "Raw.h"
#include "protobuf/pcore.pb.h"

using namespace PCore;

/**
 * @typedef DataProtobuf
 * @brief Alias for the Protocol Buffer representation of Data.
 */
using DataProtobuf = com::preventicus::pcore::Data;

/**
 * @typedef DataJson
 * @brief Alias for the JSON representation of Data.
 */
using DataJson = Json::Value;

namespace PCore {
/**
 * @class Data
 * @brief Class representing data with a header and raw content.
 *
 * The `Data` class represents a data object that consists of a header and raw content.
 */
class Data final : public IPCore<DataProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a Data instance from the given raw and header data.
   * @param raw The raw data to be included in the Data instance.
   * @param header The header data to be included in the Data instance.
   */
  explicit Data(Raw raw, Header header) noexcept;

  /**
   * @brief Constructor to initialize a Data instance from the given DataProtobuf data.
   * @param dataProtobuf The DataProtobuf data with which to initialize the Data instance.
   *
   * The `Data` instance is constructed using the provided `dataProtobuf` data, extracting the header
   * and raw content from it.
   */
  explicit Data(const DataProtobuf& DataProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a Data instance from the given JSON data.
   * @param dataJson The JSON data with which to initialize the Data instance.
   *
   * The `Data` instance is constructed using the provided JSON data, extracting the header and raw
   * content from the appropriate keys in the JSON object. The header data is extracted from the "header" key,
   * and the raw content is extracted from the "raw" key.
   *
   * @note The provided JSON data should contain the required keys for the header and raw data.
   * Otherwise, the behavior is undefined.
   *
   * @throw WrongValueException If the time zone offset is wrong (must be between -720 and 840).
   */
  explicit Data(const DataJson& dataJson);

  /**
   * @brief Default constructor to create an empty Data instance.
   */
  explicit Data() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the raw data stored in the Data instance.
   * @return The raw data of the Data instance.
   */
  [[nodiscard]] Raw getRaw() const noexcept;

  /**
   * @brief Get the header data stored in the Data instance.
   * @return The header data of the Data instance.
   */
  [[nodiscard]] Header getHeader() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the Data instance is set.
   * @return True if the Data instance is set, false otherwise.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the Data instance to a JSON data structure.
   * @return The JSON data structure representing the Data instance.
   *
   * The `toJson()` method converts the `Data` instance to a JSON data structure. If the `Data`
   * instance is not set (contains neither header nor raw data), an empty JSON object is returned.
   */
  [[nodiscard]] DataJson toJson() const noexcept final;

  /**
   * @brief Serialize the Data instance into a DataProtobuf object.
   * @param dataProtobuf The pointer to the DataProtobuf object where the data will be serialized.
   *
   * The `serialize()` method serializes the Data instance into an existing DataProtobuf object.
   * The data from the Data instance will be stored in the provided `dataProtobuf` object.
   *
   * @note The `dataProtobuf` parameter must not be a null pointer. Providing a null pointer
   * will result in a `NullPointerException` being thrown.
   *
   * @note If the Data instance is not set (contains neither header nor raw data),
   * this method will return without modifying the `dataProtobuf`.
   *
   * @param dataProtobuf The pointer to the DataProtobuf object where the data will be serialized.
   * @throws NullPointerException if the provided `dataProtobuf` parameter is a null pointer.
   * @throws WrongDataFormException if the header data form is not set to `DataForm::DATA_FORM_DIFFERENTIAL`.
   */
  void serialize(DataProtobuf* dataProtobuf) const final;

  /**
   * @brief Switch the data form of the Data instance from DataForm DATA_FORM_ABSOLUTE to DATA_FORM_DIFFERENTIAL.
   *
   * The `switchDataForm` method allows changing the data form of the Data instance from AbsoluteBlock
   * to DifferentialBlocks.
   *
   * If the Data instance is not set (contains neither header nor raw data), this method will return without any effect.
   */
  void switchDataForm() noexcept final;

  /**
   * @brief Compare the Data instance with another Data instance for equality.
   * @param data The Data instance to compare with.
   * @return True if the Data instances are equal, false otherwise.
   */
  bool operator==(const IPCore<DataProtobuf>& data) const noexcept final;

  /**
   * @brief Compare the Data instance with another Data instance for inequality.
   * @param data The Data instance to compare with.
   * @return True if the Data instances are not equal, false otherwise.
   */
  bool operator!=(const IPCore<DataProtobuf>& data) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////
  Header header;
  Raw raw;
};
}  // namespace PCore