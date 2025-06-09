import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import time, i2c
from esphome.const import CONF_ID

ds3231_ns = cg.esphome_ns.namespace('ds3231')
DS3231 = ds3231_ns.class_('DS3231', time.RealTimeClock, i2c.I2CDevice)

CONFIG_SCHEMA = time.TIME_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(DS3231),
}).extend(i2c.i2c_device_schema(0x68))