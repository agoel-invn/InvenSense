#ifdef __cplusplus 
extern "C" {
#endif

void imu_data_cmd_handler(uint8_t *data);
void grv_data_cmd_handler(uint8_t *data);
void temp_data_cmd_handler(uint8_t *data);
void mag_data_cmd_handler(uint8_t *data);
void pres_data_cmd_handler(uint8_t *data);
void chirp_data_cmd_handler(uint8_t *data);
void audio_data_cmd_handler(uint8_t *data, uint8_t data_size);

#ifdef __cplusplus
}
#endif
