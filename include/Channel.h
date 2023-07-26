/*

Created by Jakob Glueck, Steve Merschel 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#pragma once

#include "AbsoluteBlock.h"
#include "AccMetaData.h"
#include "BlockIdx.h"
#include "DataForm.h"
#include "DifferentialBlock.h"
#include "IPCore.h"
#include "PpgMetaData.h"
#include "protobuf/pcore_raw.pb.h"

using namespace PCore;

/**
 * @typedef ChannelProtobuf
 * @brief Type alias for the protocol buffer representation of a sensor channel.
 */
using ChannelProtobuf = com::preventicus::pcore::Raw_Sensor_Channel;

/**
 * @typedef BlockIdxs
 * @brief Type alias for a collection of BlockIdx.
 */
using BlockIdxs = std::vector<BlockIdx>;

/**
 * @typedef DifferentialBlocks
 * @brief Type alias for a collection of DifferentialBlock objects.
 */
using DifferentialBlocks = std::vector<DifferentialBlock>;

/**
 * @typedef ChannelJson
 * @brief Type alias for the JSON representation of a sensor channel.
 */
using ChannelJson = Json::Value;

/**
 * @typedef DifferentialBlocksJson
 * @brief Type alias for the JSON representation of a collection of DifferentialBlock objects.
 */
using DifferentialBlocksJson = Json::Value;

/**
 * @typedef MetaData
 * @brief Type alias for the optional metadata associated with a sensor channel (AccMetaData or PpgMetaData).
 */
using MetaData = std::optional<std::variant<AccMetaData, PpgMetaData>>;

/**
 * @typedef Values
 * @brief Type alias for the optional values of a sensor channel (AbsoluteBlock or DifferentialBlocks).
 */
using Values = std::optional<std::variant<AbsoluteBlock, DifferentialBlocks>>;

namespace PCore {
/**
 * @class Channel
 * @brief Class representing a sensor channel data stream.
 *
 * The `Channel` class manages data streams from sensor channels and their associated metadata.
 * It can store data in either AbsoluteBlock or DifferentialBlocks format, depending on the data form.
 */
class Channel final : public IPCore<ChannelProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Constructor to initialize a Channel instance with AccMetaData and AbsoluteBlock data.
   * @param accMetaData The AccMetaData associated with the channel.
   * @param absoluteBlock The AbsoluteBlock data stream for the channel.
   */
  explicit Channel(AccMetaData accMetaData, AbsoluteBlock absoluteBlock) noexcept;

  /**
   * @brief Constructor to initialize a Channel instance with PpgMetaData and AbsoluteBlock data.
   * @param ppgMetaData The PpgMetaData associated with the channel.
   * @param absoluteBlock The AbsoluteBlock data stream for the channel.
   */
  explicit Channel(PpgMetaData ppgMetaData, AbsoluteBlock absoluteBlock) noexcept;

  /**
   * @brief Constructor to initialize a Channel instance with PpgMetaData and DifferentialBlocks data.
   * @param ppgMetaData The PpgMetaData associated with the channel.
   * @param differentialBlocks The DifferentialBlocks data stream for the channel.
   */
  explicit Channel(PpgMetaData ppgMetaData, DifferentialBlocks differentialBlocks) noexcept;

  /**
   * @brief Constructor to initialize a Channel instance with AccMetaData and DifferentialBlocks data.
   * @param accMetaData The AccMetaData associated with the channel.
   * @param differentialBlocks The DifferentialBlocks data stream for the channel.
   */
  explicit Channel(AccMetaData accMetaData, DifferentialBlocks differentialBlocks) noexcept;

  /**
   * @brief Constructor to initialize a Channel instance from the given JSON data.
   * @param channelJson The JSON data with which to initialize the Channel instance.
   *
   * The constructor takes a JSON representation of a sensor channel (`channelJson`) and initializes a `Channel` instance.
   * It determines the appropriate metadata and data values to be associated with the channel based on the JSON data.
   *
   * If the JSON data contains PpgMetaData, a `PpgMetaData` object will be created and associated with the `Channel`.
   * In this case the SensorType is SENSOR_TYPE_PPG.
   *
   * If the JSON data contains AccMetaData, an `AccMetaData` object will be created and associated with the `Channel`.
   * In this case the SensorType is SENSOR_TYPE_ACC.
   *
   * If neither PpgMetaData nor AccMetaData is present in the JSON data, the `metaData` will be set to `std::nullopt`.
   * In this case the SensorType is SENSOR_TYPE_NONE.
   *
   * If the JSON data contains DifferentialBlocks, a vector of `DifferentialBlock` objects will be created and associated
   * with the `Channel` as the data values.
   * In this case the DataForm is DATA_FORM_DIFFERENTIAL.
   *
   * If the JSON data contains an AbsoluteBlock, an `AbsoluteBlock` object will be created and associated with the `Channel`
   * as the data values.
   * In this case the DataForm is DATA_FORM_ABSOLUTE.
   *
   * If neither DifferentialBlocks nor AbsoluteBlock is present in the JSON data, the `values` will be set to `std::nullopt`.
   * In this case the DataForm is DATA_FORM_NONE.
   *
   * @note The `channelJson` should contain all the required information for the `Channel` instance to be properly initialized.
   * If any required data is missing or the format is invalid, unexpected behavior may occur.
   */
  explicit Channel(const ChannelJson& channelJson) noexcept;

  /**
   * @brief Constructor to initialize a Channel instance from the given ChannelProtobuf data.
   * @param channelProtobuf The ChannelProtobuf data with which to initialize the Channel instance.
   *
   * The constructor takes a protocol buffer representation of a sensor channel (`channelProtobuf`) and initializes a `Channel` instance.
   * It determines the appropriate metadata and data values to be associated with the channel based on the `channelProtobuf` data.
   *
   * If the `channelProtobuf` contains AccMetaData, an `AccMetaData` object will be created and associated with the `Channel`.
   * In this case the SensorType is SENSOR_TYPE_ACC.
   *
   * If the `channelProtobuf` contains PpgMetaData, a `PpgMetaData` object will be created and associated with the `Channel`.
   * In this case the SensorType is SENSOR_TYPE_PPG.
   *
   * If neither AccMetaData nor PpgMetaData is present in the `channelProtobuf`, the `metaData` will be set to `std::nullopt`.
   * In this case the SensorType is SENSOR_TYPE_NONE.
   *
   * If the `channelProtobuf` contains DifferentialBlocks, a vector of `DifferentialBlock` objects will be created and associated
   * with the `Channel` as the data values. After initialization with channelProtobuf the DataForm is DATA_FORM_DIFFERENTIAL.
   *
   * If no DifferentialBlocks are present in the `channelProtobuf`, the `values` will be set to `std::nullopt`.
   * In this case the DataForm is DATA_FORM_NONE.
   *
   * @note The `channelProtobuf` should contain all the required information for the `Channel` instance to be properly initialized.
   * If any required data is missing or the format is invalid, unexpected behavior may occur.
   */
  explicit Channel(const ChannelProtobuf& channelProtobuf) noexcept;

  /**
   * @brief Default constructor to create an empty Channel instance.
   */
  explicit Channel() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Get the optional values of the channel data.
   * @tparam V The specific data type to retrieve (AbsoluteBlock or DifferentialBlocks).
   * @return An optional containing the values if available, or empty if the values are not present.
   */
  template <typename V>
  [[nodiscard]] std::optional<V> getValues() const noexcept;

  /**
   * @brief Get the optional metadata associated with the channel.
   * @tparam M The specific metadata type to retrieve (AccMetaData or PpgMetaData).
   * @return An optional containing the metadata if available, or empty if the metadata is not present.
   */
  template <typename M>
  [[nodiscard]] std::optional<M> getMetaData() const noexcept;

  /**
   * @brief Check if the channel data has values of a specific data type.
   * @tparam V The specific data type to check (AbsoluteBlock or DifferentialBlocks).
   * @return true if the channel data has the specified values, otherwise false.
   */
  template <typename V>
  [[nodiscard]] bool hasValues() const noexcept;

  /**
   * @brief Check if the channel has associated metadata of a specific type.
   * @tparam M The specific metadata type to check (AccMetaData or PpgMetaData).
   * @return true if the channel has the specified metadata, otherwise false.
   */
  template <typename M>
  [[nodiscard]] bool hasMetaData() const noexcept;


  /**
   * @brief Get the sensor type associated with the channel.
   * @return The SensorTypeProtobuf value representing the sensor type.
   */
  [[nodiscard]] SensorTypeProtobuf getSensorType() const noexcept;

  /**
   * @brief Get the data form of the channel.
   * @return The DataForm value representing the data form.
   */
  [[nodiscard]] DataForm getDataForm() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Check if the Channel instance is set with data.
   * @return true if the Channel instance has data, otherwise false.
   */
  [[nodiscard]] bool isSet() const noexcept final;

  /**
   * @brief Convert the Channel instance to a JSON data structure.
   * @return The JSON data structure representing the Channel instance.
   *
   * The method serializes the current state of the `Channel` instance into a JSON data structure (`ChannelJson`).
   * It captures the current metadata and data values associated with the `Channel` object and converts them into their
   * respective JSON representations.
   *
   * If the `Channel` instance is not set, an empty JSON data structure will be returned.
   *
   * If the `Channel` instance is in the `DataForm::DATA_FORM_ABSOLUTE` data form, the method will serialize the `AbsoluteBlock`
   * data into the JSON data structure. It will also include the appropriate metadata (`AccMetaDataJson` or `PpgMetaDataJson`) based
   * on the `SensorType` associated with the channel.
   *
   * If the `Channel` instance is in the `DataForm::DATA_FORM_DIFFERENTIAL` data form, the method will serialize the
   * `DifferentialBlocks` data into the JSON data structure. Similar to the absolute data form, it will also include the
   * appropriate metadata (`AccMetaDataJson` or `PpgMetaDataJson`) based on the `SensorType` associated with the channel.
   *
   * @note The returned JSON data structure may vary depending on the data form and the presence of metadata and data values in the
   * `Channel` object.
   */
  [[nodiscard]] ChannelJson toJson() const noexcept final;

  /**
   * @brief Serialize the Channel instance into a ChannelProtobuf object.
   * @param channelProtobuf The pointer to the ChannelProtobuf object where the data will be serialized.
   *
   * The method serializes the current state of the `Channel` instance into a Protocol Buffer representation (`ChannelProtobuf`).
   * It populates the `channelProtobuf` object with the metadata and data values associated with the `Channel`.
   *
   * @param channelProtobuf A pointer to the `ChannelProtobuf` object where the data will be serialized.
   *
   * @note The `channelProtobuf` should be a valid pointer to a `ChannelProtobuf` object. If `channelProtobuf` is a nullptr, a
   * `NullPointerException` will be thrown.
   *
   * @note If the Channel is not set, the method return an empty `ChannelProtobuf`.
   *
   * @note This method is specifically designed for channels in the `DataForm::DATA_FORM_DIFFERENTIAL` data form. If the `Channel`
   * instance is not in the differential data form, a `WrongDataFormException` will be thrown, indicating that the serialization is
   * only supported for channels in the differential data form.
   *
   * @throws NullPointerException If the provided `channelProtobuf` pointer is a nullptr.
   * @throws WrongDataFormException If the `Channel` instance is not in the differential data form.
   */
  void serialize(ChannelProtobuf* channelProtobuf) const final;

  /**
   * @brief Switch the data form of the Channel instance from DataForm DATA_FORM_ABSOLUTE to DATA_FORM_DIFFERENTIAL.
   * @param blockIdxs The block indices to specify the DifferentialBlocks. The block indices specify the locations
   * where the absolute data is to be split.
   *
   * The `switchDataForm` method allows changing the data form of the Channel instance from AbsoluteBlock
   * to DifferentialBlocks.
   *
   * If `Channel` is not set, the method does not switch the data form.
   */
  void switchDataForm(const BlockIdxs& blockIdxs) noexcept;

  /**
   * @brief Switch the data form of the Channel instance from DataForm DATA_FORM_DIFFERENTIAL to DATA_FORM_ABSOLUTE.
   *
   * The `switchDataForm` method allows changing the data form of the Channel instance from DifferentialBlocks
   * to AbsoluteBlock.
   *
   * If `Channel` is not set, the method does not switch the data form.
   */
  void switchDataForm() noexcept final;

  /**
   * @brief Compare the Channel instance for equality with another IPCore<ChannelProtobuf> object.
   * @param channel The IPCore<ChannelProtobuf> object to compare with.
   * @return true if the Channel instance is equal to the specified object, otherwise false.
   */
  bool operator==(const IPCore<ChannelProtobuf>& channel) const noexcept final;

  /**
   * @brief Compare the Channel instance for inequality with another IPCore<ChannelProtobuf> object.
   * @param channel The IPCore<ChannelProtobuf> object to compare with.
   * @return true if the Channel instance is not equal to the specified object, otherwise false.
   */
  bool operator!=(const IPCore<ChannelProtobuf>& channel) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                     Calculate Methode                      //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Calculate the DifferentialBlocks based on the AbsoluteBlock and given block indices.
   * @param absoluteBlock The AbsoluteBlock to calculate DifferentialBlocks from.
   * @param blockIdxs The block indices to specify where to split the absolute data.
   * @return The calculated DifferentialBlocks.
   */
  [[nodiscard]] DifferentialBlocks calculateDifferentialBlocks(const AbsoluteBlock& absoluteBlock, const BlockIdxs& blockIdxs) const noexcept;

  /**
   * @brief Create a DifferentialBlock instance from the given AbsoluteValues data.
   * @param fromBlockIdx The starting block index for the differential calculation. It should be a valid index within the `absoluteValues`
   * vector. If `fromBlockIdx` is out of range, the behavior is undefined.
   * @param toBlockIdx The ending block index (inclusive) for the differential calculation. It should be a valid index within the
   * `absoluteValues` vector and should be greater than or equal to `fromBlockIdx`. If `toBlockIdx` is out of range or less than
   * `fromBlockIdx`, the behavior is undefined.
   * @param absoluteValues The AbsoluteValues data from which to create the DifferentialBlock. The vector should contain valid data and
   * should not be empty. If the `absoluteValues` vector is empty or not properly initialized, the behavior is undefined.
   * @return The created DifferentialBlock instance.
   *
   * The method calculates the differential values based on the given `fromBlockIdx` and `toBlockIdx` within the `absoluteValues` vector.
   * The `fromBlockIdx` specifies the starting block index, and the `toBlockIdx` specifies the ending block index (inclusive) for the
   * differential calculation. The differential values are computed as the differences between consecutive elements of `absoluteValues`.
   * The method then constructs a DifferentialBlock instance using the computed differential values and returns the created instance.
   */
  [[nodiscard]] DifferentialBlock createDifferentialBlock(BlockIdx fromBlockIdx,
                                                          BlockIdx toBlockIdx,
                                                          const AbsoluteValues& absoluteValues) const noexcept;

  /**
   * @brief Calculate the AbsoluteBlock based on the given DifferentialBlocks.
   * @param differentialBlocks The DifferentialBlocks to calculate the AbsoluteBlock from.
   * @return The calculated AbsoluteBlock.
   */
  [[nodiscard]] AbsoluteBlock calculateAbsoluteBlock(const DifferentialBlocks& differentialBlocks) noexcept;

  /**
   * @brief Serialize the DifferentialBlocks data into the ChannelProtobuf object.
   * @param channelProtobuf The pointer to the ChannelProtobuf object where the DifferentialBlocks data will be serialized. The caller is
   * responsible for nullptr check.
   *
   * @note The method assumes that the `Channel` instance is in the differential data form (`DataForm::DATA_FORM_DIFFERENTIAL`). If the `Channel`
   * instance is not in the differential data form or does not have any DifferentialBlocks data, the method will return without making
   * any changes to the `channelProtobuf` object.
   */
  void serializeValues(ChannelProtobuf* channelProtobuf) const noexcept;

  /**
   * @brief Serialize the Metadata into the ChannelProtobuf object based on the SensorType.
   * @param channelProtobuf The pointer to the ChannelProtobuf object where the DifferentialBlocks data will be serialized. The caller is
   * responsible for nullptr check.
   *
   * @notw If the `Channel` instance is not associated with SensorTypeProtobuf::SENSOR_TYPE_PPG or SensorTypeProtobuf::SENSOR_TYPE_ACC,
   * the method will return without making any changes to the `channelProtobuf` object.
   */
  void serializeMetaData(ChannelProtobuf* channelProtobuf) const noexcept;

  /**
   * @brief Compare the optional Values in the Channel instance for equality with another Values object.
   * @param values The Values object to compare with.
   * @return true if the optional Values are equal, otherwise false.
   */
  bool operator==(const Values& values) const noexcept;

  /**
   * @brief Compare the optional MetaData in the Channel instance for equality with another MetaData object.
   * @param metaData The MetaData object to compare with.
   * @return true if the optional MetaData is equal, otherwise false.
   */
  bool operator==(const MetaData& metaData) const noexcept;
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////

  /**
   * @brief Optional metadata associated with the Channel instance.
   *
   * This member variable represents the optional metadata associated with the Channel instance. The metadata can be either an instance
   * of AccMetaData or PpgMetaData, or it can be empty (std::nullopt) if no metadata is present.
   */
  MetaData metaData;

  /**
   * @brief Optional data values associated with the Channel instance.
   *
   * This member variable represents the optional data values associated with the Channel instance. The data values can be either an
   * AbsoluteBlock or a vector of DifferentialBlocks, or it can be empty (std::nullopt) if no data values are present. The data values
   * store the actual sensor measurements.
   */
  Values values;
};
}  // namespace PCore