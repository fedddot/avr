#include <stdio.h>

#include "register.h"
#include "gpio.h"
#include "sysclk.h"
#include "mcu_spreg.h"
#include "fuses.h"

reg_t SREG = 0;
reg_t MCUCR = 0;
reg_t CLKPR = 0x04;

reg_t PORTA = 0;
reg_t DDRA = 0;
reg_t PINA = 0;

reg_t FUSE_LOW = 0xEE;

void PrintRegisters(void);

void GPIO_test(void);
void SysCLK_test(void);
void SREG_test(void);
void FUSELowReg_test(void);

int main() {

    GPIO_test();
    SysCLK_test();
    SREG_test();
    FUSELowReg_test();

    return 0;
}

void PrintRegisters(void) {
    printf("\t\tSREG = 0x%x, MCUCR = 0x%x, CLKPR = 0x%x,\n", SREG, MCUCR, CLKPR);
    printf("\t\tPORTA = 0x%x, DDRA = 0x%x, PINA = 0x%x,\n", PORTA, DDRA, PINA);
    printf("\t\tFUSE_LOW = 0x%x,\n", FUSE_LOW);
}

void GPIO_test(void) {
    reg_bit_number_t bit_num = BIT2;
    gpio_pin_cfg_t toset_cfg = GPIO_PIN_CFG_UNDEFINED;
    gpio_pin_cfg_t set_cfg = GPIO_PIN_CFG_UNDEFINED;

    GPIO gpio = GPIO(Register(&PORTA), Register(&DDRA), Register(&PINA));    
    gpio.set_mcucr_reg(MCUCReg(&MCUCR));

    printf("GPIO test:\n");
    bit_num = BIT2; toset_cfg = GPIO_PIN_CFG_OUTPUT;
    set_cfg = gpio.set_pin_cfg(bit_num, toset_cfg);
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit_num, toset_cfg, set_cfg);
    PrintRegisters();
    bit_num = BIT2; toset_cfg = GPIO_PIN_CFG_INPUT_HiZ;
    set_cfg = gpio.set_pin_cfg(bit_num, toset_cfg);
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit_num, toset_cfg, set_cfg);
    PrintRegisters();
    bit_num = BIT2; toset_cfg = GPIO_PIN_CFG_INPUT_PU;
    set_cfg = gpio.set_pin_cfg(bit_num, toset_cfg);
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit_num, toset_cfg, set_cfg);
    PrintRegisters();
}

void SysCLK_test(void) {
    const sysclk_freq_t f_osc = 8000000;
    const fuse_feature_status_t ckdiv8 = FUSE_FEATURE_ENABLED;
    SysCLK clk;

    printf("SysCLK test:\n");
    clk =  SysCLK(f_osc, FUSELowReg(&FUSE_LOW), CLKPReg(&CLKPR));
    printf("\tclk created with: SysCLK(%d, %d, Register(&CLKPR))\n", f_osc, ckdiv8);
    printf("\tclk.get_f_osc() = %d\n", clk.get_f_osc());
    printf("\tclk.get_clk_sys() = %d\n", clk.get_clk_sys());
    printf("\tclk.get_clk_cpu() = %d\n", clk.get_clk_cpu());
    printf("\tclk.get_clk_io() = %d\n", clk.get_clk_io());
}

void SREG_test(void) {
    SReg sreg = SReg(&SREG);
    printf("SReg test:\n");
    printf("\tSREG before = %d\n", SREG);
    sreg.sei();
    printf("\tSREG after sei() = %d\n", SREG);
    printf("\tgei() = %d\n", sreg.gei());
    sreg.cli();
    printf("\tSREG after cli() = %d\n", SREG);
    printf("\tgei() = %d\n", sreg.gei());
}

void FUSELowReg_test(void) {
    FUSELowReg fuse_low = FUSELowReg(&FUSE_LOW);
    printf("FUSELowReg test:\n");
    printf("\tFUSE_LOW before = 0x%x\n", FUSE_LOW);
    fuse_low.set_fuse_bit(FUSE_LOW_CKDIV8, FUSE_BIT_VAL_UNPROGRAMMED);
    printf("\tFUSE_LOW after fuse_low.set_fuse_bit(FUSE_LOW_CKDIV8, FUSE_BIT_VAL_UNPROGRAMMED) = 0x%x\n", FUSE_LOW);
    fuse_low.set_fuse_bit(FUSE_LOW_CKDIV8, FUSE_BIT_VAL_PROGRAMMED);
    printf("\tFUSE_LOW after fuse_low.set_fuse_bit(FUSE_LOW_CKDIV8, FUSE_BIT_VAL_PROGRAMMED) = 0x%x\n", FUSE_LOW);
}

