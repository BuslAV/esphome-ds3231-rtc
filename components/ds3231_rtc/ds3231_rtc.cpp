#include "ds3231_rtc.h"

namespace esphome {
namespace ds3231_rtc {

static uint8_t dec_to_bcd(uint8_t val) {
  return (val / 10 * 16) + (val % 10);
}

static uint8_t bcd_to_dec(uint8_t val) {
  return (val >> 4) * 10 + (val & 0x0F);
}

void DS3231RTC::setup() {
  ESP_LOGCONFIG("ds3231_rtc", "Setting up DS3231 RTC...");
  Wire.begin();
}

void DS3231RTC::update() {
  Wire.beginTransmission(0x68);
  Wire.write(0x00); // начать с регистра 0
  Wire.endTransmission();

  if (Wire.requestFrom(0x68, 7) != 7) {
    ESP_LOGE("ds3231_rtc", "Failed to read time from DS3231");
    return;
  }

  uint8_t second = bcd_to_dec(Wire.read());
  uint8_t minute = bcd_to_dec(Wire.read());
  uint8_t hour = bcd_to_dec(Wire.read());
  uint8_t weekday = bcd_to_dec(Wire.read());
  uint8_t day = bcd_to_dec(Wire.read());
  uint8_t month = bcd_to_dec(Wire.read());
  uint16_t year = bcd_to_dec(Wire.read()) + 2000;

  uint32_t unix_time = ::make_unixtime(year, month, day, hour, minute, second);
  this->publish_time(unix_time);
}

void DS3231RTC::set_time(uint32_t year, uint32_t month, uint32_t day,
                         uint32_t hour, uint32_t minute, uint32_t second) {
  Wire.beginTransmission(0x68);
  Wire.write(0x00); // начать с регистра 0
  Wire.write(dec_to_bcd(second));
  Wire.write(dec_to_bcd(minute));
  Wire.write(dec_to_bcd(hour));
  Wire.write(dec_to_bcd(day));
  Wire.write(dec_to_bcd(month));
  Wire.write(dec_to_bcd(year - 2000));
  Wire.write(dec_to_bcd(1)); // день недели (можно игнорировать)
  Wire.endTransmission();

  ESP_LOGI("ds3231_rtc", "Time set: %04u-%02u-%02u %02u:%02u:%02u",
           year, month, day, hour, minute, second);
}

}  // namespace ds3231_rtc
}  // namespace esphome