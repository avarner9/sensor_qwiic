#include <stdint.h>
#include <stdbool.h>


void initialize_i2c_dom(void);
void process_i2c_dom(void);

bool i2c_dom_is_busy(void);
void i2c_dom_read(uint8_t sub_addr, uint8_t reg_num, uint8_t num_bytes);
void i2c_dom_write(uint8_t sub_addr, uint8_t reg_num, const uint8_t * buffer_, uint8_t num_bytes);
void i2c_dom_get_data(uint8_t * buffer_, size_t buffer_length);
bool i2c_dom_get_int(void);
