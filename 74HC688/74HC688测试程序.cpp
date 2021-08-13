/*
 * @Date: 2021-08-12 22:08:04
 * @LastEditors: Jiang Hankun
 * @LastEditTime: 2021-08-13 16:14:20
 */
//74HC153测试程序

#include "StdAfx.h"
#include "testdef.h"
#include "data.h"
#include "math.h"

void PASCAL 74HC688()
{
    // 1. 连接性测试
    SET_DPS(1, 0, V, 45, MA);                               // 选DPS1，VCC=0V
    PMU_CONDITIONS(FIMV, 0.1, MA, 3, V);                    // 加流测压，加0.1MA电流，钳位电压设为3V
    if (PMU_MEASURE("1-7,41-47", 5, "CON_", V, 1.5, 0.2))   // 测量结果大于1.5V为开路，小于0.2V为短路
        BIN(1);                                             // 测试除电源和地以外的所有管脚；并设置5ns的延迟；测试项命名为"CON_"；电压上下限设置为1.5v、0.1v；分箱号为1.

    PMU_CONDITIONS(FIMV, -0.1, MA, -2, V);                  // 加流测压，加-0.1MA电流，钳位电压设为-2V
    if (PMU_MEASURE("1-7,41-47", 5, "CON_", V, 1.5, 0.2))
        BIN(1);


    // 2. 功能性测试，如果通过，侧面证明了 VIH 和 VIL 的正确性
    // Vcc = 2.0V (Min in Recommended operating conditions)
    SET_DPS(1, 2, V, 50, MA);                   // 设置DPS为2V
    SET_INPUT_LEVEL(1.5, 0.5);                  // 设置输入高低电平
    SET_OUTPUT_LEVEL(1.9, 0.1);                 // 设置输出比较高低电平
    SET_PERIOD(800);                            // 设置测试周期为800ns
    SET_TIMING(50, 600, 700);                   // 设置输入管脚时序时间和输出管脚采样时间
    FORMAT(NRZ0, "2-9,39-47");                  // 设置输入管脚格式
    if (!RUN_PATTERN("FUN", 0, 1, 0, 900000))   // 运行第0段图形，失效返回，不设置地址板转换使用，设置图形运行的时间长度，单位ms
        BIN(2);    
    // Vcc = 6.0V (Max)
    SET_DPS(1, 6.0, V, 50, MA);                   
    SET_INPUT_LEVEL(4.2, 1.8);                 
    SET_OUTPUT_LEVEL(5.48, 0.26);                
    SET_PERIOD(800);                            
    SET_TIMING(50, 600, 700);                   
    FORMAT(NRZ0, "2-9,39-47");                 
    if (!RUN_PATTERN("FUN", 0, 1, 0, 900000))   
        BIN(2); 


    // 3. 直流参数测试

    // I_IK测试
    // 测试条件：Vi > Vcc+0.5V   测量值：MAX = 20mA
    // 选择 Vcc = 5V (MIN)
    SET_DPS(1, 5, V, 50, MA); 
    PMU_CONDITIONS(FVMI, 5+1 , V, 50, MA);                          // 加压测流
    if (!PMU_MEASURE("2-9,39-46", 5, "I_IK", MA, 20, No_LoLimit))   // 通道号输入；延迟5ms
        BIN(3);

    // I_OK 测试
    if (!PMU_MEASURE("47", 5, "I_OK", MA, 20, No_LoLimit))          // 通道号输入；延迟5ms
        BIN(4);  

    // I_O 测试
    PMU_CONDITIONS(FVMI, Vcc , V, 50, MA);
    if (!PMU_MEASURE("47", 5, "I_OK", MA, 20, No_LoLimit)) 
        BIN(5);
    
    // V_OH ，为了简单处理，只测量 Vcc=4.5V Io=-20uA 的情况
    SET_DPS(1, 4.5, V, 50, MA);
    SET_INPUT_LEVEL(3.15, 1.35);
    SET_OUTPUT_LEVEL(4.4, 0.1);
    SET_PERIOD(800);
    SET_TIMING(50, 600, 700);
    FORMAT(NRZ0, "2-9,39-47");
    RUN_PATTERN(1, 1, 0, 0);
    PMU_CONDITIONS(FIMV, -20, UA, 6, V);
    if (!PMU_MEASURE("2-9,39-46", 5, "I_IK", V, No_UpLimit, 4.4))
        BIN(6);

    // V_OL
    RUN_PATTERN(2, 1, 0, 0);
    PMU_CONDITIONS(FIMV, -20, UA, 6, V);
    if (!PMU_MEASURE("2-9,39-46", 5, "I_IK", V, 0.1, No_LoLimit))
        BIN(7);

    // Ii 各个管脚的电流
    RUN_PATTERN(3, 1, 0, 0); 
    PMU_CONDITIONS(FVMI,4.5,V,10,UA);  
    if (PMU_MEASURE("2-9,39-47", 5, "Ii_", MA, 1, No_LoLimit))
        BIN(6);     

    // Icc 不知道怎么测试

}
