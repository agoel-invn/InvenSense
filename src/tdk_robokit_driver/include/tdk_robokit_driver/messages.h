#include<stdint.h>

/** @brief Command IDs
 */
enum PacketType {
	PKT_TYPE_RESERVED                      = 0x00,

	/* COMMAND packets (HOST -> DEVICE) */
	PKT_TYPE_CMD_GET_PROTOCOL_VERSION      = 0x01,
	PKT_TYPE_CMD_SOFT_RESET                = 0x02,
	PKT_TYPE_CMD_RESET_SENSOR              = 0x03,
	PKT_TYPE_CMD_RESET_PDALGO              = 0x04,
	PKT_TYPE_CMD_ENABLE_PDALGO             = 0x05,
	PKT_TYPE_CMD_ENABLE_IQSTREAM           = 0x06,
	PKT_TYPE_CMD_START                     = 0x07,
	PKT_TYPE_CMD_STOP                      = 0x08,
	PKT_TYPE_CMD_ENABLE_ASIC_DATA          = 0x09,
	PKT_TYPE_CMD_ENABLE_IMU                = 0x0a,
	PKT_TYPE_CMD_ENABLE_FLOOR_ALGO         = 0x0b,
	PKT_TYPE_CMD_ENABLE_CLIFF_ALGO         = 0x0c,

	PKT_TYPE_CMD_ENABLE_MAG                = 0x50,
	PKT_TYPE_CMD_ENABLE_PRES               = 0x51,
	PKT_TYPE_CMD_ENABLE_TEMP               = 0x52,
	PKT_TYPE_CMD_ENABLE_AUDIO              = 0x53,
	PKT_TYPE_CMD_ENABLE_ROBO_START_STOP    = 0x54,
	PKT_TYPE_CMD_UPDATE_ROBO_STATE         = 0x55,
	PKT_TYPE_CMD_CTRL_MOTOR                = 0x56,

	PKT_TYPE_CMD_GET_SENSOR_PARAM          = 0x20,
	PKT_TYPE_CMD_GET_VERSION               = 0x21,
	PKT_TYPE_CMD_GET_SENSORS               = 0x22,
	PKT_TYPE_CMD_GET_ALGO_CONFIG           = 0x23,
	PKT_TYPE_CMD_GET_STATUS                = 0x24,
	PKT_TYPE_CMD_GET_FLOOR_ALGO_CONFIG     = 0x25,
	PKT_TYPE_CMD_GET_CLIFF_ALGO_CONFIG     = 0x26,
	PKT_TYPE_CMD_GET_SENSORS_TRIGGER_MODE  = 0x28,

	PKT_TYPE_CMD_SET_ALGO_CONFIG           = 0x30,
	PKT_TYPE_CMD_SET_ODR                   = 0x31,
	PKT_TYPE_CMD_SET_RANGE_MM              = 0x32,
	PKT_TYPE_CMD_SET_SAMPLE_RANGE          = 0x33,
	PKT_TYPE_CMD_SET_PULSE_LENGTH          = 0x34,
	PKT_TYPE_CMD_SET_LOW_GAIN_RXLEN        = 0x35,
	PKT_TYPE_CMD_SET_FLOOR_ALGO_CONFIG     = 0x38,
	PKT_TYPE_CMD_SET_ENABLE_RX_PRE_TRIGGER = 0x39,
	PKT_TYPE_CMD_SET_CLIFF_ALGO_CONFIG     = 0x3A,
	PKT_TYPE_CMD_SET_DEBUG                 = 0x40,
	PKT_TYPE_CMD_SET_SENSOR_CONFIG         = 0x57,
	PKT_TYPE_CMD_GET_SENSOR_CONFIG         = 0x58,

	/* RESPONSE packets (DEVICE -> HOST) */
	PKT_TYPE_RESP_GET_PROTOCOL_VERSION     = 0x81,
	PKT_TYPE_RESP_SOFT_RESET               = 0x82,
	PKT_TYPE_RESP_RESET_SENSOR             = 0x83,
	PKT_TYPE_RESP_RESET_PDALGO             = 0x84,
	PKT_TYPE_RESP_ENABLE_PDALGO            = 0x85,
	PKT_TYPE_RESP_ENABLE_IQSTREAM          = 0x86,
	PKT_TYPE_RESP_START                    = 0x87,
	PKT_TYPE_RESP_STOP                     = 0x88,
	PKT_TYPE_RESP_ENABLE_ASIC_DATA         = 0x89,
	PKT_TYPE_RESP_ENABLE_IMU               = 0x8a,
	PKT_TYPE_RESP_ENABLE_FLOOR_ALGO        = 0x8b,
	PKT_TYPE_RESP_ENABLE_CLIFF_ALGO        = 0x8c,
	PKT_TYPE_RESP_ENABLE_MAG               = 0xd0,
	PKT_TYPE_RESP_ENABLE_PRES              = 0xd1,
	PKT_TYPE_RESP_ENABLE_TEMP              = 0xd2,
	PKT_TYPE_RESP_ENABLE_AUDIO             = 0xd3,
	PKT_TYPE_RESP_ENABLE_ROBO_START_STOP   = 0xd4,
	PKT_TYPE_RESP_CTRL_MOTOR               = 0xd6,
	PKT_TYPE_RESP_SET_SENSOR_CONFIG        = 0xd7,
	PKT_TYPE_RESP_GET_SENSOR_CONFIG        = 0xd8,

	PKT_TYPE_RESP_GET_SENSOR_PARAM         = 0xa0,
	PKT_TYPE_RESP_GET_VERSION              = 0xa1,
	PKT_TYPE_RESP_GET_SENSORS              = 0xa2,
	PKT_TYPE_RESP_GET_ALGO_CONFIG          = 0xa3,
	PKT_TYPE_RESP_GET_STATUS               = 0xa4,
	PKT_TYPE_RESP_GET_FLOOR_ALGO_CONFIG    = 0xa5,
	PKT_TYPE_RESP_GET_CLIFF_ALGO_CONFIG    = 0xa6,
	PKT_TYPE_RESP_GET_SENSORS_TRIGGER_MODE = 0xa8,
	
	PKT_TYPE_RESP_SET_ALGO_CONFIG          = 0xb0,
	PKT_TYPE_RESP_SET_ODR                  = 0xb1,
	PKT_TYPE_RESP_SET_RANGE_MM             = 0xb2,
	PKT_TYPE_RESP_SET_SAMPLE_RANGE         = 0xb3,
	PKT_TYPE_RESP_SET_PUSLE_LENGTH         = 0xb4,
	PKT_TYPE_RESP_SET_LOW_GAIN_RXLEN       = 0xb5,
	PKT_TYPE_RESP_SET_FLOOR_ALGO_CONFIG    = 0xb8,
	PKT_TYPE_RESP_SET_ENABLE_RX_PRE_TRIGGER= 0xb9,
	PKT_TYPE_RESP_SET_CLIFF_ALGO_CONFIG    = 0xba,
	PKT_TYPE_RESP_SET_DEBUG                = 0xc0,

	/* Update state (HOST -> DEVICE) */
	PKT_TYPE_UPDATE_ROBO_STATE             = 0x50,

	/* ASYNCRONOUS packets (DEVICE -> HOST) */
	PKT_TYPE_ASYNC_GRV_DATA                = 0xee,
	PKT_TYPE_ASYNC_ROBOVAC_STOP            = 0xef,
	PKT_TYPE_ASYNC_AUDIO_DATA              = 0xf0,
	PKT_TYPE_ASYNC_TEMP_DATA               = 0xf1,
	PKT_TYPE_ASYNC_MAG_DATA                = 0xf2,
	PKT_TYPE_ASYNC_PRES_DATA               = 0xf3,
	PKT_TYPE_ASYNC_CLIFF_ALGO_OUT          = 0xf7,
	PKT_TYPE_ASYNC_FLOOR_ALGO_OUT          = 0xf8,
	PKT_TYPE_ASYNC_IMU_DATA                = 0xf9,
	PKT_TYPE_ASYNC_CH_DATA                 = 0xfa,
	PKT_TYPE_ASYNC_PD_OUT                  = 0xfb,
	PKT_TYPE_ASYNC_STATUS                  = 0xfc,
	PKT_TYPE_ASYNC_DEBUG_MESSAGE           = 0xfd,
};

typedef struct sensor_enable{
    uint8_t enable_flag;
}sensor_enable_t;

typedef struct odr_ms{
    uint8_t sensor_id;
    int32_t odr_ms;
}odr_ms_t;

typedef union cmd_param{
    sensor_enable_t enable_disable;
    odr_ms_t        odr_in_ms;
}cmd_param_t;

// funtion definition
int sendData(const uint8_t* data, uint16_t data_len);
void serial_protocol_init();