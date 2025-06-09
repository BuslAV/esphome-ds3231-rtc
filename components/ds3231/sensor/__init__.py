import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import time
from esphome.const import CONF_ID
import esphome.final_validate as fv

ds3231_rtc_ns = cg.esphome_ns.namespace('ds3231_rtc')
DS3231RTC = ds3231_rtc_ns.class_('DS3231RTC', cg.PollingComponent, time.RealTimeClock)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DS3231RTC),
    cv.Optional("update_interval", default="60s"): cv.update_interval,
})

FINAL_VALIDATE_SCHEMA = fv.validate_timezone_name()

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await time.register_time(var, config)