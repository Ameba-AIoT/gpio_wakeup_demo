#include "gpio_wakeup_demo.h" 
void gpio_wakeup_demo_thread(void)
{
    int i = 0;
    RTK_LOGI(TAG, "gpio_wakeup_demo_thread start!\r\n");   
    GPIO_InitTypeDef GPIO_InitStruct = {
             .GPIO_Pin = WAKEUP_GPIO,
             .GPIO_PuPd = GPIO_PuPd_UP,
             .GPIO_Mode = GPIO_Mode_INT,
             .GPIO_ITTrigger = GPIO_INT_Trigger_EDGE,
             .GPIO_ITPolarity = GPIO_INT_POLARITY_ACTIVE_LOW,
     };
     GPIO_INTConfig(WAKEUP_GPIO, DISABLE);
     GPIO_Init(&GPIO_InitStruct);
     InterruptRegister(GPIO_INTHandler, GPIOA_IRQ, (u32)GPIOA_BASE, 3);
     InterruptEn(GPIOA_IRQ, 3);
     GPIO_UserRegIrq(WAKEUP_GPIO, gpio_irq_handler, &GPIO_InitStruct);
     SOCPS_SetAPWakeEvent(WAKE_SRC_GPIOA, ENABLE);
     GPIO_INTConfig(WAKEUP_GPIO, ENABLE);
     while (1)
    {        
        rtos_time_delay_ms(1000);
        RTK_LOGI(TAG, "gpio_wakeup_demo_thread delay 1s!\r\n");
        if(GPIO_ReadDataBit(WAKEUP_GPIO))
        {
            RTK_LOGI(TAG, "gpio_wakeup_demo_thread is going to sleep!\r\n");
            for(i = 5; i >= 0; i--)
            {
                rtos_time_delay_ms(500);
                RTK_LOGI(TAG, "%d!\r\n", i);            
            }
            
            GPIO_INTConfig(WAKEUP_GPIO, ENABLE);
            pmu_release_wakelock(PMU_OS);  
        }
        
    }
    rtos_task_delete(NULL); 
}
void gpio_irq_handler(void *id, u32 event)
{
    UNUSED(id);

    u32 GPIO_Pin = (event >> 16);
    u8 port_num = PORT_NUM(GPIO_Pin);
    GPIO_TypeDef *GPIO = (GPIO_TypeDef *)(GPIO_REG_BASE + port_num * 0x400);

    /* 0:AP; 1:NP */
    RTK_LOGI(TAG, "Core %d GPIO_IRQ_HANDLED %x!\n", SYS_CPUID(), GPIO_Pin);

    RTK_LOGI(TAG, "GPIO_INT_STATUS = 0x%x\n", GPIO->GPIO_INT_STATUS);

    GPIO_INTConfig(GPIO_Pin, DISABLE);
    pmu_acquire_wakelock(PMU_OS);
} 