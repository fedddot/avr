#ifndef _GPIO_H_
#define _GPIO_H_

#include "register.h" // Register
#include "gpio_types.h" // gpio_status, gpio_pin_cfg, gpio_params_struct
                        // TODO: find a way to move to the src file!

typedef enum gpio_status gpio_status_t;  
typedef enum gpio_pin_cfg gpio_pin_cfg_t;
typedef struct gpio_params_struct gpio_params_t;

class GPIO {
private:
    gpio_params_t gpio_params;
public:
    //  constructors
    GPIO();
    GPIO(gpio_params_t _gpio_params);        
    //  configuration
    gpio_pin_cfg_t set_pin_cfg(reg_bits_t _pin_number, gpio_pin_cfg_t _pin_cfg);
    gpio_pin_cfg_t get_pin_cfg(reg_bits_t _pin_number);
    //  i/o operations
    reg_bit_value_t set_pin(reg_bits_t _pin_number, reg_bit_value_t _value);
    reg_bit_value_t get_pin(reg_bits_t _pin_number);
    //  setters/getters
    void set_gpio_params(gpio_params_t _gpio_params);
    gpio_params_t get_gpio_params(void);
    //  status
    gpio_status_t get_registers_status(void);
};    

#endif // _GPIO_H_