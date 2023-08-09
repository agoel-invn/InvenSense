#include <stdint.h>
#include "sensor_node.h"

__attribute__((weak)) void imu_data_cmd_handler(uint8_t *data){
    ;
}
__attribute__((weak)) void grv_data_cmd_handler(uint8_t *data){
    ;
}
__attribute__((weak)) void temp_data_cmd_handler(uint8_t *data){
    ;
}
__attribute__((weak)) void mag_data_cmd_handler(uint8_t *data){
    ;
}
__attribute__((weak)) void pres_data_cmd_handler(uint8_t *data){
    ;
}
__attribute__((weak)) void chirp_data_cmd_handler(uint8_t *data){
    ;
}
__attribute__((weak)) void audio_data_cmd_handler(uint8_t *data, uint8_t data_size){
    ;
}