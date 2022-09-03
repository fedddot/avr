#include <stdio.h>

#include "register.h"
#include "gpio.h"
#include "sysclk.h"

reg_t MCUCR = 0;
reg_t PORTA = 0;
reg_t DDRA = 0;
reg_t PINA = 0;
reg_t CLKPR = 0x04;
reg_bit_number_t pud_bit = BIT4;

void GPIO_test(void);
void SysCLK_test(void);

int main() {

    GPIO_test();
    SysCLK_test();

    return 0;
}

void GPIO_test(void) {
    reg_bit_number_t bit_num = BIT2;
    gpio_pin_cfg_t toset_cfg = GPIO_PIN_CFG_UNDEFINED;
    gpio_pin_cfg_t set_cfg = GPIO_PIN_CFG_UNDEFINED;

    GPIO gpio = GPIO(Register(&PORTA), Register(&DDRA), Register(&PINA));    
    gpio.set_mcucr_reg(Register(&MCUCR), pud_bit);

    printf("GPIO test:\n");
    bit_num = BIT2; toset_cfg = GPIO_PIN_CFG_OUTPUT;
    set_cfg = gpio.set_pin_cfg(bit_num, toset_cfg);
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit_num, toset_cfg, set_cfg);
    printf("\tMCUCR = %d; PORTA = %d; DDRA = %d; PINA = %d;\n", MCUCR, PORTA, DDRA, PINA);
    bit_num = BIT2; toset_cfg = GPIO_PIN_CFG_INPUT_HiZ;
    set_cfg = gpio.set_pin_cfg(bit_num, toset_cfg);
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit_num, toset_cfg, set_cfg);
    printf("\tMCUCR = %d; PORTA = %d; DDRA = %d; PINA = %d;\n", MCUCR, PORTA, DDRA, PINA);
    bit_num = BIT2; toset_cfg = GPIO_PIN_CFG_INPUT_PU;
    set_cfg = gpio.set_pin_cfg(bit_num, toset_cfg);
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit_num, toset_cfg, set_cfg);
    printf("\tMCUCR = %d; PORTA = %d; DDRA = %d; PINA = %d;\n", MCUCR, PORTA, DDRA, PINA);
}

void SysCLK_test(void) {
    const sysclk_freq_t f_osc = 8000000;
    const fuse_feature_status_t ckdiv8 = FUSE_FEATURE_ENABLED;
    SysCLK clk;

    printf("SysCLK test:\n");
    clk =  SysCLK(f_osc, ckdiv8, Register(&CLKPR));
    printf("\tclk created with: SysCLK(%d, %d, Register(&CLKPR))\n", f_osc, ckdiv8);
    printf("\tclk.get_f_osc() = %lu\n", clk.get_f_osc());
    printf("\tclk.get_clk_sys() = %lu\n", clk.get_clk_sys());
    printf("\tclk.get_clk_cpu() = %lu\n", clk.get_clk_cpu());
    printf("\tclk.get_clk_io() = %lu\n", clk.get_clk_io());
}