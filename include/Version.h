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
#include "IPCore.h"
#include "protobuf/pcore_version.pb.h"

using VersionProtobuf = com::preventicus::pcore::Version;
using Major = uint32_t;
using Minor = uint32_t;
using Patch = uint32_t;
using VersionJson = Json::Value;
using MajorJson = Json::Value;
using MinorJson = Json::Value;
using PatchJson = Json::Value;

namespace PCore {
/**
 * @class Version
 * @brief Represents a version number with major, minor, and patch components.
 *
 * The Version class represents a version number with major, minor, and patch components.
 * The version number follows the semantic versioning format (major.minor.patch).
 */
class Version final : public IPCore<VersionProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a Version instance with the given major, minor, and patch components.
   * @param major The major version component.
   * @param minor The minor version component.
   * @param patch The patch version component.
   */
  explicit Version(Major major, Minor minor, Patch patch) noexcept;

  /**
   * @brief Constructor to initialize a Version instance from the given VersionProtobuf data.
   * @param versionProtobuf The VersionProtobuf data with which to initialize the Version instance.
   *
   * This constructor initializes a Version instance using data from the provided VersionProtobuf object.
   * The major, minor, and patch components will be set based on the values stored in the VersionProtobuf object.
   */
  explicit Version(const VersionProtobuf& versionProtobuf) noexcept;

  /**
   * @brief Constructor to initialize a Version instance from the given JSON data.
   * @param versionJson The JSON data with which to initialize the Version instance.
   *
   * This constructor initializes a Version instance using data from the provided JSON data structure.
   * The major, minor, and patch components will be extracted from the JSON object using specific keys.
   *
   * @throw WrongValueException If major, minor or patch is negative in the JSON object.
   */
  explicit Version(const VersionJson& versionJson);

  /**
   * @brief Default constructor to create an empty Version instance with all components set to zero.
   */
  explicit Version() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the major version component.
   * @return The major version component of the Version.
   */
  [[nodiscard]] Major getMajor() const noexcept;

  /**
   * @brief Get the minor version component.
   * @return The minor version component of the Version.
   */
  [[nodiscard]] Minor getMinor() const noexcept;

  /**
   * @brief Get the patch version component.
   * @return The patch version component of the Version.
   */
  [[nodiscard]] Patch getPatch() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the Version instance is set with valid version information.
   * @return True if the Version instance is set with valid version information, false otherwise.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the Version instance to a JSON data structure.
   *
   * The toJson method converts the Version instance to a JSON data structure. The resulting JSON data structure will represent the
   * Version instance with its major, minor, and patch components. If the Version instance is not set, an empty JSON data structure
   * will be returned.
   *
   * @return The JSON data structure representing the Version instance. If the Version instance is not set, an empty JSON data
   * structure will be returned.
   */
  [[nodiscard]] VersionJson toJson() const noexcept final;

  /**
   * @brief Serialize the Version instance into a VersionProtobuf object.
   * @param versionProtobuf The pointer to the VersionProtobuf object where the data will be serialized.
   *
   * The `serialize` method serializes the Version instance into an existing VersionProtobuf object.
   * The data from the Version instance will be stored in the provided `versionProtobuf` object.
   *
   * @note The `versionProtobuf` parameter must not be a null pointer. Providing a null pointer
   * will result in a `NullPointerException` being thrown.
   *
   * @note If the Version instance is not set (contains invalid major, minor, and patch components),
   * this method will return without modifying the `versionProtobuf`.
   *
   * @param versionProtobuf The pointer to the VersionProtobuf object where the data will be serialized.
   * @throws NullPointerException If the provided `versionProtobuf` parameter is a null pointer.
   */
  void serialize(VersionProtobuf* versionProtobuf) const final;

  /**
   * @brief [INTERFACE IMPLEMENTATION - DO NOT CALL]
   *
   * This method is part of an interface implementation and should not be called directly on the Version class.
   * Its purpose is to fulfill the requirements of the interface, and calling it may lead to unintended behavior.
   *
   * @throws ShouldNotBeCalledException if called directly on the Version class.
   */
  void switchDataForm() final;

  /**
   * @brief Check if the Version instance is equal to another Version instance.
   * @param version The other Version instance to compare with.
   * @return True if the Version instance is equal to the other Version instance, false otherwise.
   */
  bool operator==(const IPCore<VersionProtobuf>& version) const noexcept final;

  /**
   * @brief Check if the Version instance is not equal to another Version instance.
   * @param version The other Version instance to compare with.
   * @return True if the Version instance is not equal to the other Version instance, false otherwise.
   */
  bool operator!=(const IPCore<VersionProtobuf>& version) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////
  Major major;
  Minor minor;
  Patch patch;
};
}  // namespace PCore