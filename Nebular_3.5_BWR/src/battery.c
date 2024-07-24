#include <stdint.h>
#include "tl_common.h"

#include "battery.h"

RAM volatile unsigned int adc_dat_buf[8];

void adc_bat_init(void)
{
	adc_power_on_sar_adc(0);
	gpio_set_output_en(GPIO_PB7, 1);
	gpio_set_input_en(GPIO_PB7, 0);
	gpio_write(GPIO_PB7, 1);
	adc_set_sample_clk(5);
	adc_set_left_right_gain_bias(GAIN_STAGE_BIAS_PER100, GAIN_STAGE_BIAS_PER100);
	adc_set_chn_enable_and_max_state_cnt(ADC_MISC_CHN, 2);
	adc_set_state_length(240, 0, 10);
	analog_write(anareg_adc_res_m, RES14 | FLD_ADC_EN_DIFF_CHN_M);
	adc_set_ain_chn_misc(B7P, GND);
	adc_set_ref_voltage(ADC_MISC_CHN, ADC_VREF_1P2V);
	adc_set_tsample_cycle_chn_misc(SAMPLING_CYCLES_6);
	adc_set_ain_pre_scaler(ADC_PRESCALER_1F8);
	adc_power_on_sar_adc(1);
}

uint16_t get_battery_mv()
{
	uint16_t temp;
	int i, j;
	adc_bat_init();
	adc_reset_adc_module();
	u32 t0 = clock_time();

	uint16_t adc_sample[8] = {0};
	u32 adc_result;
	for (i = 0; i < 8; i++)
	{
		adc_dat_buf[i] = 0;
	}
	while (!clock_time_exceed(t0, 25))
		;
	adc_config_misc_channel_buf((uint16_t *)adc_dat_buf, 8 << 2);
	dfifo_enable_dfifo2();

	for (i = 0; i < 8; i++)
	{
		while (!adc_dat_buf[i])
			;
		if (adc_dat_buf[i] & BIT(13))
		{
			adc_sample[i] = 0;
		}
		else
		{
			adc_sample[i] = ((uint16_t)adc_dat_buf[i] & 0x1FFF);
		}
		if (i)
		{
			if (adc_sample[i] < adc_sample[i - 1])
			{
				temp = adc_sample[i];
				adc_sample[i] = adc_sample[i - 1];
				for (j = i - 1; j >= 0 && adc_sample[j] > temp; j--)
				{
					adc_sample[j + 1] = adc_sample[j];
				}
				adc_sample[j + 1] = temp;
			}
		}
	}
	dfifo_disable_dfifo2();
	u32 adc_average = (adc_sample[2] + adc_sample[3] + adc_sample[4] + adc_sample[5]) / 4;
	adc_result = adc_average;
	return (adc_result * 1175) >> 10;
}

uint8_t get_battery_level(uint16_t battery_mv)
{
	uint8_t battery_level = (battery_mv - 2200) / (31 - 22);
	if (battery_level > 100)
		battery_level = 100;
	if (battery_mv < 2200)
		battery_level = 0;
	return battery_level;
}