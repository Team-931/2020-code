/*----------------------------------------------------------------------------*/
/* Copyright (c) 2008-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AnalogEncoder.h"

#include <utility>

#include <hal/FRCUsageReporting.h>

#include "frc/DigitalInput.h"
#include "frc/WPIErrors.h"
#include "frc/smartdashboard/SendableBuilder.h"
#include "frc/smartdashboard/SendableRegistry.h"

using namespace frc;

AnalogEncoder::AnalogEncoder(int aChannel, bool reverseDirection) {
  m_aSource = std::make_shared<DigitalInput>(aChannel);
  InitEncoder(reverseDirection);
  auto& registry = SendableRegistry::GetInstance();
  registry.AddChild(this, m_aSource.get());
}

AnalogEncoder::AnalogEncoder(DigitalSource* aSource,
                 bool reverseDirection)
    : m_aSource(aSource, NullDeleter<AnalogInput>()) {
  if (m_aSource == nullptr)
    wpi_setWPIError(NullParameter);
  else
    InitEncoder(reverseDirection);
}

AnalogEncoder::AnalogEncoder(DigitalSource& aSource, 
                 bool reverseDirection)
    : m_aSource(&aSource, NullDeleter<AnalogInput>()) {
  InitEncoder(reverseDirection);
}

AnalogEncoder::AnalogEncoder(std::shared_ptr<DigitalSource> aSource,
                 bool reverseDirection)
    : m_aSource(aSource) {
  if (m_aSource == nullptr)
    wpi_setWPIError(NullParameter);
  else
    InitEncoder(reverseDirection);
}

AnalogEncoder::~AnalogEncoder() {
}

int AnalogEncoder::Get() const {
  return m_aSource->GetVoltage();
}

void AnalogEncoder::Reset() {
  
}

double AnalogEncoder::GetPeriod() const {
  return 1; // todo: fix
}
/*
void AnalogEncoder::SetMaxPeriod(double maxPeriod) {
  if (StatusIsFatal()) return;
  int32_t status = 0;
  HAL_SetEncoderMaxPeriod(m_encoder, maxPeriod, &status);
  wpi_setHALError(status);
}
*//*
bool AnalogEncoder::GetStopped() const {
  if (StatusIsFatal()) return true;
  int32_t status = 0;
  bool value = HAL_GetEncoderStopped(m_encoder, &status);
  wpi_setHALError(status);
  return value;
}
*//*
bool AnalogEncoder::GetDirection() const {
  if (StatusIsFatal()) return false;
  int32_t status = 0;
  bool value = HAL_GetEncoderDirection(m_encoder, &status);
  wpi_setHALError(status);
  return value;
}
*//*
int AnalogEncoder::GetRaw() const {
  if (StatusIsFatal()) return 0;
  int32_t status = 0;
  int value = HAL_GetEncoderRaw(m_encoder, &status);
  wpi_setHALError(status);
  return value;
}

int AnalogEncoder::GetEncodingScale() const {
  int32_t status = 0;
  int val = HAL_GetEncoderEncodingScale(m_encoder, &status);
  wpi_setHALError(status);
  return val;
}
 */
double AnalogEncoder::GetDistance() const {
  return mDistancePerPulse * Get();
}
 
double AnalogEncoder::GetRate() const {
  return mDistancePerPulse / GetPeriod(); // todo: fix
}
/* 
void AnalogEncoder::SetMinRate(double minRate) {
  if (StatusIsFatal()) return;
  int32_t status = 0;
  HAL_SetEncoderMinRate(m_encoder, minRate, &status);
  wpi_setHALError(status);
}
 */
void AnalogEncoder::SetDistancePerPulse(double distancePerPulse) {
   mDistancePerPulse = distancePerPulse;
  }

double AnalogEncoder::GetDistancePerPulse() const {
  return mDistancePerPulse;
}

void AnalogEncoder::SetReverseDirection(bool reverseDirection) {
  mReversed = reverseDirection;
}
/*
void AnalogEncoder::SetSamplesToAverage(int samplesToAverage) {
  if (samplesToAverage < 1 || samplesToAverage > 127) {
    wpi_setWPIErrorWithContext(
        ParameterOutOfRange,
        "Average counter values must be between 1 and 127");
    return;
  }
  int32_t status = 0;
  HAL_SetEncoderSamplesToAverage(m_encoder, samplesToAverage, &status);
  wpi_setHALError(status);
}

int AnalogEncoder::GetSamplesToAverage() const {
  int32_t status = 0;
  int result = HAL_GetEncoderSamplesToAverage(m_encoder, &status);
  wpi_setHALError(status);
  return result;
}
*/
double AnalogEncoder::PIDGet() {
 // if (StatusIsFatal()) return 0.0;
  switch (GetPIDSourceType()) {
    case PIDSourceType::kDisplacement:
      return GetDistance();
    case PIDSourceType::kRate:
      return GetRate();
    default:
      return 0.0;
  }
}

void AnalogEncoder::SetIndexSource(int channel, AnalogEncoder::IndexingType type) {
  // Force digital input if just given an index
  m_indexSource = std::make_shared<DigitalInput>(channel);
  SendableRegistry::GetInstance().AddChild(this, m_indexSource.get());
  SetIndexSource(*m_indexSource.get(), type);
}
/*
void AnalogEncoder::SetIndexSource(const DigitalSource& source,
                             AnalogEncoder::IndexingType type) {
  int32_t status = 0;
  HAL_SetEncoderIndexSource(
      m_encoder, source.GetPortHandleForRouting(),
      (HAL_AnalogTriggerType)source.GetAnalogTriggerTypeForRouting(),
      (HAL_EncoderIndexingType)type, &status);
  wpi_setHALError(status);
}
*//*
void AnalogEncoder::SetSimDevice(HAL_SimDeviceHandle device) {
  HAL_SetEncoderSimDevice(m_encoder, device);
}
*//*
int AnalogEncoder::GetFPGAIndex() const {
  int32_t status = 0;
  int val = HAL_GetEncoderFPGAIndex(m_encoder, &status);
  wpi_setHALError(status);
  return val;
}
*/
void AnalogEncoder::InitSendable(SendableBuilder& builder) {
  int32_t status = 0;
  HAL_EncoderEncodingType type = HAL_GetEncoderEncodingType(m_encoder, &status);
  wpi_setHALError(status);
  if (type == HAL_EncoderEncodingType::HAL_Encoder_k4X)
    builder.SetSmartDashboardType("Quadrature Encoder");
  else
    builder.SetSmartDashboardType("Encoder");

  builder.AddDoubleProperty("Speed", [=]() { return GetRate(); }, nullptr);
  builder.AddDoubleProperty("Distance", [=]() { return GetDistance(); },
                            nullptr);
  builder.AddDoubleProperty("Distance per Tick",
                            [=]() { return GetDistancePerPulse(); }, nullptr);
}

void AnalogEncoder::InitEncoder(bool reverseDirection) {
  mReversed = reverseDirection;
  SendableRegistry::GetInstance().AddLW(this, "Encoder",
                                        m_aSource->GetChannel());
}
/*
double AnalogEncoder::DecodingScaleFactor() const {
  if (StatusIsFatal()) return 0.0;
  int32_t status = 0;
  double val = HAL_GetEncoderDecodingScaleFactor(m_encoder, &status);
  wpi_setHALError(status);
  return val;
}
*/