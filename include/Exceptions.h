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
/**
 * @class PcoreException
 * @brief Base class for custom exceptions in the PCore namespace.
 */
class PcoreException : public std::exception {
 public:
  /**
   * @brief Get the error message associated with the exception.
   * @return The error message as a null-terminated character array.
   */
  [[nodiscard]] const char* what() const noexcept final { return message.c_str(); }

 protected:
  /**
   * @brief Construct a PcoreException with the given function name.
   * @param functionName The name of the function where the exception occurred.
   */
  explicit PcoreException(std::string functionName) : functionName(std::move(functionName)), message() {}

  const std::string functionName;
  std::string message;
};

  /**
   * @class PCore::NullPointerException
   * @brief Exception thrown when a null pointer is encountered in a function.
   *
   * The `NullPointerException` class is used to indicate a situation where a null pointer is encountered
   * in a function. It includes the name of the function and the name of the null pointer in the error message.
   */
class NullPointerException : public PcoreException {
 public:

  /**
   * @brief Construct a NullPointerException with the given function name and pointer name.
   * @param functionName The name of the function where the null pointer was encountered.
   * @param pointerName The name of the null pointer that caused the exception.
   */
  explicit NullPointerException(const std::string& functionName, const std::string& pointerName) noexcept
      : PcoreException(functionName), pointerName(pointerName) {
    message = "NullPointerException: In " + functionName + " pointer " + pointerName + " is null.\n";
  }

 private:
  const std::string pointerName;
};

/**
 * @class PCore::WrongDataFormException
 * @brief Exception thrown when the DataForm value is unexpected in a function.
 *
 * The `WrongDataFormException` class is used to indicate a situation where the `DataForm` value is unexpected
 * in a function. It includes a custom text message to provide additional details.
 */
class WrongDataFormException : public PcoreException {
 public:
 /**
   * @brief Construct a WrongDataFormException with the given function name and custom text message.
   * @param functionName The name of the function where the exception occurred.
   * @param text The custom text message describing the unexpected data form.
   */
  explicit WrongDataFormException(const std::string& functionName, const std::string& text) noexcept : PcoreException(functionName), text(text) {
    message = "Wrong DataForm: In " + functionName + ": " + text + "\n";
  }

 private:
  const std::string text;
};

/**
 * @class PCore::WrongValueException
 * @brief Exception thrown when a function receives an unexpected value.
 *
 * The `WrongValueException` class is used to indicate a situation where a function receives an unexpected value.
 * It includes a custom text message to provide additional details.
 */
class WrongValueException : public PcoreException {
 public:
  /**
   * @brief Construct a WrongValueException with the given function name and custom text message.
   * @param functionName The name of the function where the exception occurred.
   * @param text The custom text message describing the unexpected value.
   */
  explicit WrongValueException(const std::string& functionName, const std::string& text) noexcept : PcoreException(functionName), text(text) {
    message = "Wrong Value: In " + functionName + ": " + text + "\n";
  }

 private:
  const std::string text;
};

/**
 * @class PCore::ShouldNotBeCalledException
 * @brief Exception thrown when a function should not be called.
 *
 * The `ShouldNotBeCalledException` class is used to indicate a situation where a function should not be called,
 * but it is called unexpectedly. It includes the name of the function in the error message.
 */
class ShouldNotBeCalledException : public PcoreException {
 public:
  /**
   * @brief Construct a ShouldNotBeCalledException with the given function name.
   * @param functionName The name of the function that should not be called.
   */
  explicit ShouldNotBeCalledException(const std::string& functionName) noexcept : PcoreException(functionName) {
    message = functionName + " should not be called\n";
  }
};
}  // namespace PCore