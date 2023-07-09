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

#include <string>
using JsonKey = std::string;

namespace PcoreJsonKey {
static const JsonKey data = "data";
static const JsonKey header = "header";
static const JsonKey time_zone_offset_min = "time_zone_offset_min";
static const JsonKey pcore_version = "pcore_version";
static const JsonKey major = "major";
static const JsonKey minor = "minor";
static const JsonKey patch = "patch";
static const JsonKey data_form = "data_form";
static const JsonKey raw = "raw";
static const JsonKey sensors = "sensors";
static const JsonKey channels = "channels";
static const JsonKey ppg_metadata = "ppg_metadata";
static const JsonKey wavelength_nm = "wavelength_nm";
static const JsonKey color = "color";
static const JsonKey absolute_block = "absolute_block";
static const JsonKey absolute_values = "absolute_values";
static const JsonKey absolute_timestamps_container = "absolute_timestamps_container";
static const JsonKey unix_timestamps_ms = "unix_timestamps_ms";
static const JsonKey sensor_type = "sensor_type";
static const JsonKey differential_blocks = "differential_blocks";
static const JsonKey differential_values = "differential_values";
static const JsonKey differential_timestamps_container = "differential_timestamps_container";
static const JsonKey first_unix_timestamp_ms = "first_unix_timestamp_ms";
static const JsonKey block_differences_ms = "block_differences_ms";
static const JsonKey timestamps_differences_ms = "timestamps_differences_ms";
static const JsonKey acc_metadata = "acc_metadata";
static const JsonKey coordinate = "coordinate";
static const JsonKey norm = "norm";
}  // namespace PcoreJsonKey