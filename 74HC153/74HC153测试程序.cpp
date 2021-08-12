//74HC153测试程序

#include "StdAfx.h"
#include "testdef.h"
#include "data.h"
#include "math.h"

void PASCAL 74HC153()
{
    //CON-TEST
    SET_DPS(1, 0, V, 45, MA);                             //选DPS1，VCC=0V
    PMU_CONDITIONS(FIMV, 0.1, MA, 3, V);                  //加流测压，加0.1MA电流，钳位电压设为3V
    if (PMU_MEASURE("1-7,41-47", 5, "CON_", V, 1.5, 0.2)) // 测量结果大于1.5V为开路，小于0.2V为短路
        BIN(1);                                           //测试除电源和地以外的所有管脚；并设置5ns的延迟；测试项命名为"CON_"；电压上下限设置为1.5v、0.1v；分箱号为1.

    PMU_CONDITIONS(FIMV, -0.1, MA, -2, V); // 加-0.1MA电流，钳位电压设为-2V
    if (PMU_MEASURE("1-7,41-47", 5, "CON_", V, 1.5, 0.2))
        BIN(1);

    //FUN-TEST1 VCC=4.75V(min)
    SET_DPS(1, 4.75, V, 50, MA);    //设置DPS为4.75V
    SET_INPUT_LEVEL(2, 0.8);   //设置输入高低电平
    SET_OUTPUT_LEVEL(2.4, 0.4);  //设置输出比较高低电平
    SET_PERIOD(800);             //设置测试周期为800ns
    SET_TIMING(50, 600, 700);    //设置输入管脚时序时间和输出管脚采样时间
    FORMAT(NRZ0, "1-6,42-47"); //设置输入管脚格式

    // 运行测试图形【注意要把FUN图形名加上】【最后一个参数不要写0】
    if (!RUN_PATTERN("FUN", 0, 1, 0, 900000)) // 运行第0段图形，失效返回，不设置地址板转换使用，设置图形运行的时间长度，单位ms
        BIN(2);

    //FUN-TEST2 VCC=5.25V(max)
    SET_DPS(1, 5.25, V, 50, MA);    //设置DPS为5.25V
    SET_INPUT_LEVEL(2, 0.8);   //设置输入高低电平
    SET_OUTPUT_LEVEL(2.4, 0.4);  //设置输出比较高低电平
    SET_PERIOD(800);             //设置测试周期为800ns
    SET_TIMING(50, 600, 700);    //设置输入管脚时序时间和输出管脚采样时间
    FORMAT(NRZ0, "1-6,42-47"); //设置输入管脚格式

    // 运行测试图形【注意要把FUN图形名加上】【最后一个参数不要写0】
    if (!RUN_PATTERN("FUN", 0, 1, 0, 900000))
        BIN(2);

    //VOH-TEST，使输出端为逻辑高电平时，加流测压
    SET_DPS(1, 4.75, V, 50, MA); //VCC(MIN)
    SET_INPUT_LEVEL(2, 0.8);  //设置输入高低电平
    SET_OUTPUT_LEVEL(2.4, 0.4);  //设置输出比较高低电平
    SET_PERIOD(800);             //设置测试周期为800ns
    SET_TIMING(50, 600, 700);    //设置输入管脚时序时间和输出管脚采样时间
    FORMAT(NRZ0, "1-6,42-47"); //设置输入管脚格式

    RUN_PATTERN(1, 1, 0, 0);     
    PMU_CONDITIONS(FIMV,-800,UA,8,V); //这里钳位电压怎么选？？？
    if (!PMU_MEASURE("7,41",5,"VOH_",V,No_UpLimit,2.4)) //通道号输入；延迟5ms；上限1ua。下限0ua
        BIN(3);

    //VOL-TEST
    RUN_PATTERN(2, 1, 0, 0);                        
    PMU_CONDITIONS(FIMV,20,UA,8,V); //这里钳位电压怎么选？？？
    if (!PMU_MEASURE("7,41",5,"VOL_",V,0.4,No_LoLimit)) //通道号输入；延迟5ms；上限1ua。下限0ua
        BIN(4);

   //VIK-TEST
    SET_DPS(1, 4.75, V, 50, MA); //VCC(MIN)                    
    PMU_CONDITIONS(FIMV,-12,MA,-2,V); //这里钳位电压怎么选？？？
    if (!PMU_MEASURE("1-6,42-47",5,"VIK_",V,-1.5,No_LoLimit)) //通道号输入；延迟5ms；上限1ua。下限0ua
        BIN(5);

    //各管脚电流Ii
    SET_DPS(1, 5.25, V, 50, MA); //VCC(MAX)
    SET_INPUT_LEVEL(2, 0.8);  //设置输入高低电平
    SET_OUTPUT_LEVEL(2.4, 0.4);  //设置输出比较高低电平
    SET_PERIOD(800);             //设置测试周期为800ns
    SET_TIMING(50, 600, 700);    //设置输入管脚时序时间和输出管脚采样时间
    FORMAT(NRZ0, "1-6,42-47"); //设置输入管脚格式

    RUN_PATTERN(4, 1, 0, 0); 
    PMU_CONDITIONS(FVMI,5.5,V,10,UA);  
    if (PMU_MEASURE("1-6,42-47", 5, "Ii_", MA, 1, No_LoLimit))
        BIN(6);  

    //IIH测试，Vcc为5.25V时
    SET_DPS(1, 5.25, V, 50, MA); //VCC(MAX)
    RUN_PATTERN(5, 1, 0, 0);
    PMU_CONDITIONS(FVMI,2.4,V,60,UA);  
    if (PMU_MEASURE("1-6,42-47", 5, "IIH_", UA, 40, No_LoLimit))
        BIN(7);  

    //IIL测试，Vcc为5.25V时
    SET_DPS(1, 5.25, V, 50, MA); //VCC(MAX)
    RUN_PATTERN(6, 1, 0, 0);
    PMU_CONDITIONS(FVMI,0.4,V,0,MA);  
    if (PMU_MEASURE("1-6,42-47", 5, "IIL_", UA, -1.6, No_LoLimit))
        BIN(8); 

    //IOS测试，Vcc为5.25V时
    SET_DPS(1, 5.25, V, 50, MA); //VCC(MAX)
    RUN_PATTERN(5, 1, 0, 0);     
    PMU_CONDITIONS(FIMV,-800,UA,8,V); //这里钳位电压怎么选？？？
    if (!PMU_MEASURE("7,41",5,"IOS_",MA,-18,-57)) //通道号输入；延迟5ms；上限1ua。下限0ua
        BIN(9);

    //ICCH测试，Vcc为5.25V时
    SET_DPS(1, 5.25, V, 50, MA); //VCC(MAX)
    RUN_PATTERN(6, 1, 0, 0);     
    if (!DPS_MEASURE(1,R200MA,5,"ICC_",MA,36,60)) //通道号输入；延迟5ms；上限1ua。下限0ua
        BIN(10);
}
