#include <stdint.h>
#include <stdbool.h>
#include <string.h>


static void * memcpy_start(void * dst, const void * src, size_t length);
static void * memset_start(void * ptr1, int c, size_t length);
int main(void);





extern const uint8_t _text_sec_end;
extern uint8_t _data_sec_start;
extern uint8_t _data_sec_end;
extern uint8_t _bss_sec_start;
extern uint8_t _bss_sec_end;


void start(void)
{
    memcpy_start(&_data_sec_start, &_text_sec_end, &_data_sec_end - &_data_sec_start);
    memset_start(&_bss_sec_start, 0, &_bss_sec_end - &_bss_sec_start);

    main();
    
    while (true)
    {
    }
}






static void * memcpy_start(void * dst, const void * src, size_t length)
{
    uint8_t * dst2 = dst;
    const uint8_t * src2 = src;
    for (size_t i = 0; i < length; i++)
        dst2[i] = src2[i];
    return dst;
}
static void * memset_start(void * ptr1, int c, size_t length)
{
    uint8_t * ptr2 = ptr1;
    for (size_t i = 0; i < length; i++)
        ptr2[i] = c;
    return ptr1;
}




uint32_t int_vec_table[0x2F] __attribute__((section(".intvectable") )) = 
{
    0x20001800,
    (uint32_t)&start,
    (uint32_t)&start,
    (uint32_t)&start,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&start,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};





