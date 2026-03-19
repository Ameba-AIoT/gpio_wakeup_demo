#ifndef _DEMO_H_
#define _DEMO_H_

#include <stdio.h>
#include "ameba_soc.h"
#include "platform_stdlib.h"
#include "basic_types.h"
#include "os_wrapper.h"
#include "log.h"

#define TAG     "app_main" 
//wakeup gpio pin
#define WAKEUP_GPIO _PB_30

void gpio_wakeup_demo_thread(void);
void gpio_irq_handler(void *id, u32 event);

#endif