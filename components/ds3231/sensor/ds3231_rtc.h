#pragma once

#include "esphome/core/component.h"
#include "esphome/components/time/real_time_clock.h"
#include <Wire.h>

namespace esphome {
namespace ds3231_rtc {

class DS3231RTC : public PollingComponent, public time::RealTimeClock {
 public:
  void setup() override;
  void update() override;

  void set_time(uint32_t year, uint32_t month, uint32_t day,
                uint32_t hour, uint32_t minute, uint32_t second);

 protected:
  static uint8_t dec_to_bcd(uint8_t val);
  static uint8_t bcd_to_dec(uint8_t val);
};

}  // namespace ds3231_rtc
}  // namespace esphome