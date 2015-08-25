
void HardFault_Handler(void)
{
	uint32_t fault = NVIC_FAULT_STAT_R;
	uint32_t addr = NVIC_MM_ADDR_R;
}