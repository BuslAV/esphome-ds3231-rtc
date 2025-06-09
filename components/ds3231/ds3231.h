#pragma once
#include "esphome/components/time/real_time_clock.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace ds3231 {

class DS3231 : public time::RealTimeClock, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  
  // Запись времени в RTC
  void write_time(struct tm *time) override;
  
 protected:
  // Чтение времени из RTC
  bool read_time(struct tm *time) override;
  
  uint8_t bcd_to_byte_(uint8_t bcd);
  uint8_t byte_to_bcd_(uint8_t byte);
};
}  // namespace ds3231
}  // namespace esphome