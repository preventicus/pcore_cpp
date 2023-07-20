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

#include <exception>
#include <utility>
#include "string"

namespace PCore {

class PcoreException : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept final { return message.c_str(); }

 protected:
  explicit PcoreException(std::string functionName) : functionName(std::move(functionName)), message() {}

  const std::string functionName;
  std::string message;
};

class NullPointerException : public PcoreException {
 public:
  explicit NullPointerException(const std::string& functionName, const std::string& pointerName) noexcept
      : PcoreException(functionName), pointerName(pointerName) {
    message = "NullPointerException: In " + functionName + " pointer " + pointerName + " is null.\n";
  }

 private:
  const std::string pointerName;
};

class DataFormIsNoneException : public PcoreException {
 public:
  explicit DataFormIsNoneException(const std::string& functionName) noexcept : PcoreException(functionName) {
    message = "DataForm is NONE: In " + functionName + "\n";
  }
};

class SensorTypeIsNoneException : public PcoreException {
 public:
  explicit SensorTypeIsNoneException(const std::string& functionName) noexcept : PcoreException(functionName) {
    message = "SensorType is NONE: In " + functionName + "\n";
  }
};

class WrongDataFormException : public PcoreException {
 public:
  explicit WrongDataFormException(const std::string& functionName, const std::string& text) noexcept : PcoreException(functionName), text(text) {
    message = "Wrong DataForm: In " + functionName + ": " + text + "\n";
  }

 private:
  const std::string text;
};

class WrongValueException : public PcoreException {
 public:
  explicit WrongValueException(const std::string& functionName, const std::string& text) noexcept : PcoreException(functionName), text(text) {
    message = "Wrong Value: In " + functionName + ": " + text + "\n";
  }

 private:
  const std::string text;
};

class OnlyOneParameterAllowedException : public PcoreException {
 public:
  explicit OnlyOneParameterAllowedException(const std::string& functionName, const std::string& para1Name, const std::string& para2Name) noexcept
      : PcoreException(functionName), para1Name(para1Name), para2Name(para2Name) {
    message = "In " + functionName + " only " + para1Name + " or " + para2Name + " can be processed\n";
  }

 private:
  const std::string para1Name;
  const std::string para2Name;
};

class ShouldNotBeCalledException : public PcoreException {
 public:
  explicit ShouldNotBeCalledException(const std::string& functionName) noexcept : PcoreException(functionName) {
    message = functionName + " should not be called\n";
  }
};
}  // namespace PCore