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
#include "PcoreJson.h"
#include "Version.h"
#include "protobuf/pcore.pb.h"

using namespace PCore;


using HeaderProtobuf = com::preventicus::pcore::Data_Header;


using TimeZoneOffset = int32_t;
using HeaderJson = Json::Value;
using TimeZoneOffsetJson = Json::Value;

namespace PCore {
/**
 * @class Header
 * @brief The Header class represents the header information of the data.
 *
 * The Header class contains information such as the version, time zone offset, and data form
 * of the data represented by the IPCore HeaderProtobuf message.
 */
class Header final : public IPCore<HeaderProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Construct a new Header object with the given version, time zone offset, and data form.
   *
   * @param version The version of the data.
   * @param timeZoneOffsetInMin The time zone offset in minutes.
   * @param dataForm The data form of the data.
   */
  explicit Header(Version version, TimeZoneOffset timeZoneOffsetInMin, DataForm dataForm);

  /**
   * @brief Construct a new Header object from the provided HeaderProtobuf data.
   *
   * @param headerProtobuf The HeaderProtobuf data to construct the Header object from.
   */
  explicit Header(const HeaderProtobuf& headerProtobuf);

  /**
   * @brief Construct a new Header object from the provided JSON data.
   *
   * @param headerJson The JSON data to construct the Header object from.
   *
   * @note The provided JSON data should contain the required key for the Header.
   * Otherwise, the behavior is undefined.
   *
   * @throw WrongValueException if the time zone offset is not in range.
   */
  explicit Header(const HeaderJson& headerJson);

  /**
   * @brief Default constructor. Constructs an empty Header object.
   */
  explicit Header() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the time zone offset in minutes.
   *
   * @return The time zone offset in minutes.
   */
  [[nodiscard]] TimeZoneOffset getTimeZoneOffsetInMin() const noexcept;

  /**
   * @brief Get the Pcore version of the data.
   *
   * @return The Pcore version of the data.
   */
  [[nodiscard]] Version getPcoreVersion() const noexcept;

  /**
   * @brief Get the data form of the data.
   *
   * @return The data form of the data.
   */
  [[nodiscard]] DataForm getDataForm() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the Header object is set with valid data.
   *
   * @return true if the Header object is set with valid data, false otherwise.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the Header object to JSON format.
   *
   * The method converts the Header object into a JSON data format and returns it.
   * If the Header object is not set, an empty JSON object will be returned.
   *
   * @return The JSON data representing the Header object.
   */
  [[nodiscard]] HeaderJson toJson() const noexcept final;

  /**
   * @brief Serialize the Header object to protobuf format.
   *
   * The method serializes the Header object into the provided `headerProtobuf`,
   * which is a pointer to the protobuf data. If the Header object is not set, no serialization will be performed.
   *
   * @param headerProtobuf The pointer to the protobuf data to serialize into.
   * @throw NullPointerException if pointer is null.
   */
  void serialize(HeaderProtobuf* headerProtobuf) const final;

  /**
   * @brief Switch the data form of the Header object.
   *
   * The `switchDataForm` method allows changing the data form (DataForm::DATA_FORM_DIFFERENTIAL to
   * DataForm::DATA_FORM_ABSOLUTE and vice versa) of the Header object.
   */
  void switchDataForm() noexcept final;

  /**
   * @brief Compare two Header objects for equality.
   *
   * The equality operator compares two Header objects for equality based on their contents.
   * The comparison includes the time zone offset, PCORE version, and data form.
   *
   * @param header The Header object to compare with.
   * @return true if the two Header objects are equal, false otherwise.
   */
  bool operator==(const IPCore<HeaderProtobuf>& header) const noexcept final;

  /**
   * @brief Compare two Header objects for inequality.
   *
   * The inequality operator compares two Header objects for inequality based on their contents.
   * The comparison includes the time zone offset, PCORE version, and data form.
   *
   * @param header The Header object to compare with.
   * @return true if the two Header objects are not equal, false otherwise.
   */
  bool operator!=(const IPCore<HeaderProtobuf>& header) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                       Helper Methods                       //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the time zone offset is valid and within a valid range.
   *
   * The method checks if the time zone offset is within a valid range and throws an exception if it's not valid.
   * The time zone offset is considered valid if it's within the range [-720, 840] minutes, which corresponds to
   * a time zone offset between UTC-12:00 and UTC+14:00.
   */
  void checkTimeZoneOffset() const;

  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief The time zone offset in minutes.
   */
  TimeZoneOffset timeZoneOffsetInMin;

  /**
   * @brief The Pcore version of the data.
   */
  Version pcoreVersion;

  /**
   * @brief The data form of the data.
   */
  DataForm dataForm;
};
}  // namespace PCore