#include "DeserializedPpgMetaData.h"

DeserializedPpgMetaData::DeserializedPpgMetaData() {
  this->color = Color::COLOR_NONE;
  this->wavelength_nm = 0;
}

void DeserializedPpgMetaData::setColor(Color color) {
  this->wavelength_nm = 0;
  this->color = color;
}

void DeserializedPpgMetaData::setWavelength(uint32_t wavelength) {
  this->color = Color::COLOR_NONE;
  this->wavelength_nm = wavelength;
}

Color DeserializedPpgMetaData::getColor() {
  return this->color;
}

uint32_t DeserializedPpgMetaData::getWavelength() {
  return this->wavelength_nm;
}

bool DeserializedPpgMetaData::isEqual(
    DeserializedPpgMetaData& deserializedPpgMetaData) {
  return this->color == deserializedPpgMetaData.color &&
         this->wavelength_nm == deserializedPpgMetaData.wavelength_nm;
}

SerializedPpgMetaData DeserializedPpgMetaData::serialize() {
  SerializedPpgMetaData serializedPpgMetaData = SerializedPpgMetaData();
  if (this->color != Color::COLOR_NONE) {
    serializedPpgMetaData.set_color(this->color);
  }
  if (this->wavelength_nm != 0) {
    serializedPpgMetaData.set_wavelength(this->wavelength_nm);
  }
  return serializedPpgMetaData;
}

void DeserializedPpgMetaData::deserialize(
    SerializedPpgMetaData& serializedPpgMetaData) {
  this->color = serializedPpgMetaData.color();
  this->wavelength_nm = serializedPpgMetaData.wavelength();
}