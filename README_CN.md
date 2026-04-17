* [English Version](./README.md)

### Ameba RTL8721Dx 系列 SoC 的 GPIO 唤醒示例（FreeRTOS）

🚀 本示例基于 RTL8721Dx 系列 SoC，演示系统进入低功耗模式后，通过 GPIO 下降沿信号唤醒 CPU 的完整流程。

- 📎 开发板链接  [🛒 淘宝](https://item.taobao.com/item.htm?id=904981157046) | [📦 Amazon](https://www.amazon.com/-/zh/dp/B0FB33DT2C/)
- 📄 [芯片详情](https://aiot.realmcu.com/zh/module/rtl8721dx.html)
- 📚 [GPIO 唤醒文档](https://aiot.realmcu.com/cn/latest/rtos/ps/powertest/index.html#gpio)

---

### ✨ 功能特点

✅ 上电后，系统先进行倒计时，然后进入休眠模式  
✅ 配置指定 GPIO 为唤醒源，当检测到 **下降沿** 时唤醒 CPU，并执行对应中断处理  
✅ GPIO 电平恢复后，系统再次进入休眠倒计时，实现「周期性休眠 → 唤醒 → 再休眠」循环

---

### 工作原理

1️⃣ 开机后进行倒计时，期间释放功耗锁并配置 GPIO 唤醒源；  
2️⃣ 当配置的 GPIO 检测到 **下降沿** 时触发唤醒信号，系统从低功耗模式唤醒；  
3️⃣ 可通过电流表观测电流变化：  
   - 倒计时期间，功耗维持在 mA 级别；  
   - 进入休眠后，功耗下降至 µA 级别；  
   - GPIO 唤醒瞬间电流拉升回 mA 级并维持运行，直至再次进入休眠模式

4️⃣ 同时观察串口 log 输出，并与电流表实际量测数据对比，参考下图：  

![alt text](image.png)

---

### 🔌 硬件接线

- 需要使用特定 EVB（评估板）；  
- 从模块端直接供电，确保测到的电流为模块实际功耗；  
- 连接方式参考下图：  

![alt text](image-1.png)

---

### 🚀 快速开始

1️⃣ **选择SDK**  
   - 设置`env.sh`（`env.bat`）路径：`source {sdk}/env.sh`  
   - 将`{sdk}`替换为[ameba-rtos SDK](https://github.com/Ameba-AIoT/ameba-rtos)根目录中`env.sh`的绝对路径。如果SDK路径没有改变，此步骤仅需执行一次。

   ⚡ **注意**：本示例仅支持 SDK 版本 **≥ v1.2**

2️⃣ **编译**  
   - 在当前工程目录下执行：  
     ```bash
     source env.sh
     ameba.py build -p
     ```

3️⃣ **烧录固件**
   >请将命令中的 `COMx` 替换为实际串口号（例如 `COM5`）
   ```bash
   ameba.py flash --p COMx --image km4_boot_all.bin 0x08000000 0x8014000 --image km0_km4_app.bin 0x08014000 0x8200000
   ```
   ⚡ **Note**: 项目目录中提供的预编译bin文件也可以用如下方式烧录：
   ```bash
   ameba.py flash --p COMx --image ../km4_boot_all.bin 0x08000000 0x8014000 --image ../km0_km4_app.bin 0x08014000 0x8200000
   ```

4️⃣ **打开串口监视**  
   - `ameba.py monitor --port COMx --b 1500000`


5️⃣ **触发唤醒并对比实验结果** 🔁  

- 按下开发板上的 `RESET` 按钮，启动示例程序；  
- 观察串口日志中的倒计时、进入休眠及 GPIO 唤醒打印；  
- 同时结合官方 demo 截图与电流表读数，对比低功耗与唤醒时的功耗变化。

---

### 📝 日志示例

```plaintext
日志示例：
18:20:02.550  ROM:[V1.1]
18:20:02.550  FLASH RATE:1, Pinmux:0
18:20:02.550  IMG1(OTA1) VALID, ret: 0
18:20:02.550  IMG1 ENTRY[f800779:0]
18:20:02.550  [BOOT-I] KM4 BOOT REASON 0: Initial Power on
18:20:02.550  [BOOT-I] KM4 CPU CLK: 240000000 Hz
18:20:02.550  [BOOT-I] KM0 CPU CLK: 96000000 Hz
18:20:02.550  [BOOT-I] PSRAM Ctrl CLK: 240000000 Hz 
18:20:02.550  [BOOT-I] IMG1 ENTER MSP:[30009FDC]
18:20:02.550  [BOOT-I] Build Time: Mar  3 2026 16:51:41
18:20:02.550  [BOOT-I] IMG1 SECURE STATE: 1
18:20:02.550  [FLASH-I] FLASH CLK: 80000000 Hz
18:20:02.550  [FLASH-I] Flash ID: c8-40-17 (Capacity: 64M-bit)
18:20:02.550  [FLASH-I] Flash Read 4IO
18:20:02.550  [FLASH-I] FLASH HandShake[0x2 OK]
18:20:02.550  [BOOT-I] Init APM PSRAM
18:20:02.550  [PSRAM-I] Cal win size 32
18:20:02.550  [BOOT-I] KM0 XIP IMG[0c000000:ad40]
18:20:02.550  [BOOT-I] KM0 SRAM[20068000:860]
18:20:02.550  [BOOT-I] KM0 PSRAM[0c00b5a0:20]
18:20:02.551  [BOOT-I] KM0 ENTRY[20004d00:60]
18:20:02.551  [BOOT-I] KM4 XIP IMG[0e000000:1cc40]
18:20:02.551  [BOOT-I] KM4 SRAM[2000b000:480]
18:20:02.551  [BOOT-I] KM4 PSRAM[0e01d0c0:20]
18:20:02.551  [BOOT-I] KM4 ENTRY[20004d80:40]
18:20:02.551  [BOOT-I] IMG2 BOOT from OTA 1, Version: 1.1 
18:20:02.551  [BOOT-I] Image2Entry @ 0xe00a0ad ...
18:20:02.551  [APP-I] KM4 APP START
18:20:02.551  [APP-I] VTOR: 30007000, VTOR_NS:30007000
18:20:02.551  [APP-I] IMG2 SECURE STATE: 1
18:20:02.551  [MAIN-I] IWDG refresh on!
18:20:02.551  [MAIN-I] KM0 OS START 
18:20:02.551  [CLK-I] [CAL4M]: delta:1 target:320 PPM: 3125 PPM_Limit:30000 
18:20:02.551  [CLK-I] [CAL131K]: delta:26 target:2441 PPM: 10651 PPM_Limit:30000 
18:20:02.551  [LOCKS-I] KM4 init_retarget_locks
18:20:02.551  [APP-I] BOR arises when supply voltage decreases under 2.57V and recovers above 2.7V.
18:20:02.551  [MAIN-I] KM4 MAIN 
18:20:02.551  [VER-I] AMEBA-RTOS SDK VERSION: 1.2.0
18:20:02.551  [MAIN-I] File System Init Success 
18:20:02.551  [app_main-I] gpio_wakeup_demo_thread creat!
18:20:02.551  [MAIN-I] KM4 START SCHEDULER 
18:20:02.551  [app_main-I] gpio_wakeup_demo_thread start!
18:20:03.542  [app_main-I] gpio_wakeup_demo_thread is going to sleep!
18:20:04.037  [app_main-I] 10!
18:20:04.550  [app_main-I] 9!
18:20:05.045  [app_main-I] 8!
18:20:05.541  [app_main-I] 7!
18:20:06.052  [app_main-I] 6!
18:20:06.548  [app_main-I] 5!
18:20:07.044  [app_main-I] 4!
18:20:07.540  [app_main-I] 3!
18:20:08.052  [app_main-I] 2!
18:20:08.548  [app_main-I] 1!
18:20:09.044  [app_main-I] 0!
18:20:09.044  APPG
18:20:09.044  NPPG
18:20:12.285  NPPW
18:20:12.285  APPW
18:20:12.285  [app_main-I] Core 1 GPIO_IRQ_HANDLED 3e!
18:20:12.285  [app_main-I] GPIO_INT_STATUS = 0x0
18:20:22.280  [app_main-I] gpio_wakeup_demo_thread is going to sleep!
...

```