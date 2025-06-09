# ESPHome DS3231 RTC Component

Этот репозиторий содержит external_component для ESPHome, позволяющий использовать модуль реального времени **DS3231** как источник точного времени.

## ✅ Возможности

- Чтение текущего времени с DS3231
- Установка времени через вызов сервиса
- Поддержка часовых поясов
- Обновление раз в минуту (настраивается)

## 🔧 Как использовать

Добавь в свой `configuration.yaml`:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/ваш-логин/esphome-ds3231-rtc.git 
    refresh: 1min