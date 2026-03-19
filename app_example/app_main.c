#include "gpio_wakeup_demo.h"


void app_example(void)
{  
   
    RTK_LOGI(TAG, "gpio_wakeup_demo_thread creat!\r\n");   
    if (rtos_task_create(NULL, "gpio_wakeup_demo_thread", (rtos_task_t) gpio_wakeup_demo_thread, NULL, 1024 * 4, 1) != RTK_SUCCESS) 
    {
       RTK_LOGE(TAG, "\n\r%s rtos_task_create(init_thread) failed", __FUNCTION__);
    }
    
}
