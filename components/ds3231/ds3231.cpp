#include "ds3231.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ds3231 {

static const char *const TAG = "ds3231";

void DS3231::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DS3231...");
  // Инициализация - можно добавить проверку связи
}

void DS3231::update() {
  struct tm time;
  if (this->read_time(&time)) {
    ESP_TIME_IS_VALID(time) {
      this->time_->sync_time(time);
    }
  }
}

void DS3231::dump_config() {
  ESP_LOGCONFIG(TAG, "DS3231:");
  LOG_I2C_DEVICE(this);
}

bool DS3231::read_time(struct tm *time) {
  uint8_t data[7];
  if (this->read_bytes(0x00, data, 7) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Failed to read from DS3231");
    return false;
  }

  time->tm_sec = bcd_to_byte_(data[0] & 0x7F);
  time->tm_min = bcd_to_byte_(data[1] & 0x7F);
  time->tm_hour = bcd_to_byte_(data[2] & 0x3F); // 24-hour mode
  time->tm_wday = bcd_to_byte_(data[3] & 0x07) - 1; // DS3231: 1-7, tm: 0-6
  time->tm_mday = bcd_to_byte_(data[4] & 0x3F);
  time->tm_mon = bcd_to_byte_(data[5] & 0x1F) - 1; // DS3231: 1-12, tm: 0-11
  time->tm_year = bcd_to_byte_(data[6]) + 100; // DS3231: 00-99, tm: years since 1900

  return true;
}

void DS3231::write_time(struct tm *time) {
  uint8_t data[7];
  data[0] = byte_to_bcd_(time->tm_sec);
  data[1] = byte_to_bcd_(time->tm_min);
  data[2] = byte_to_bcd_(time->tm_hour); // 24-hour mode
  data[3] = byte_to_bcd_(time->tm_wday + 1); // Convert to 1-7 range
  data[4] = byte_to_bcd_(time->tm_mday);
  data[5] = byte_to_bcd_(time->tm_mon + 1); // Convert to 1-12 range
  data[6] = byte_to_bcd_(time->tm_year - 100); // Convert to 00-99 range

  if (this->write_bytes(0x00, data, 7) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Failed to write to DS3231");
  }
}

uint8_t DS3231::bcd_to_byte_(uint8_t bcd) {
  return (bcd >> 4) * 10 + (bcd & 0x0F);
}

uint8_t DS3231::byte_to_bcd_(uint8_t byte) {
  return ((byte / 10) << 4) | (byte % 10);
}

}  // namespace ds3231
}  // namespace esphome