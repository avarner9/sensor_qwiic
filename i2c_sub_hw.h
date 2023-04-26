#include <stdint.h>
#include <stdbool.h>


void initialize_i2c_sub_hw(void);
void i2c_sub_hw_set_addr(uint8_t addr);
void process_i2c_sub_hw(void);

bool i2c_sub_hw_b_selected(void);
bool i2c_sub_hw_b_read_mode(void);
bool i2c_sub_hw_b_has_unread_bytes(void);
uint8_t i2c_sub_hw_get_byte(void);
bool i2c_sub_hw_b_wants_byte(void);
void i2c_sub_hw_send_byte(uint8_t data);

