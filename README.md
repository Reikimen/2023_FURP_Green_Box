# 2023_FURP_Plant_Box
We, the FURP project team, had the requirement to manufacture a plant box capable of culturing lettuce properly. 

# The design notes of the plant box hardware Sys Bata.0.2
ver: 6.30 已敲定使用材料，用于7.10交付的硬件设计  
已删除废案  
PS: 因为本人使用的图床是SM.MS+Github，如果markdown中的图片无法打开，请科学上网
# Intro
本设计基于在7月10之前，我们FURP项目组要制造一个能够正常培养生菜的植物箱的要求。为了更好地继续项目制作的资料整理，在此整理了可用的资料和链接。我们计划先制作一个能够在本地使用单个或者多个MCU来控制的硬件系统，先使用Arduino IDE & vscode + platformIO 进行开发，后续再迁移到ESP-IDF框架里使用云服务。因为ESP-3Cmini这个板没有clk时钟pin脚，本地的控制计划使用能够I2C连接传感器的ESP8266开发板，而C3和S3已经不支持I2C了。ESP8266有足够的可编程引脚且有专用的扩展板。第一个阶段主要难点在于使用低电控制高电，还有如何获取一个可编程控制光照条件的LED灯源（功率足够，光强色温可调）。  

而在本地的控制实现后，主要难点将转变为，如何使用云服务来实现一个APP或者微信小程序的交互。 

此外，本计划书还将说明引脚的分配，并且给出分配理由。最后，还将附上函数的功能表，命名规则为"chatGpt"式，以方便日后的维护。如下为本设计的大致框架。
## timeline
- 6.28 下一次会议，(进实验室，采购回来的材料放的位置)
- 6.30 计划敲定选用的元件，因为部分元件功能相同，需要测试
- 7.10 Tony 要求的本地控制的方案，因为蔬菜种植需要时间

## Contents
- 0.0 ESP8266 基础信息
- 1.0 传感器
    - 1.1 温湿度传感器(sht30)
    - 1.2 CO2传感器
    - 1.3 PH传感器(不适用)
    - 1.4 光敏传感器
        - 1.4.1 光合有效辐射传感器
        - 1.4.2 DFROBOT光线传感器
    - 1.5 摄像（ESP32-CAM）
    - 1.6 水位传感器

- 2.0 被控元件
    - 2.1 开关 & 空占比控制电压
    - 2.2 照明灯
    - 2.3 加热模块（硅胶）
    - 2.4 制冷模块（半导体）
    - 2.5 风扇（机箱风扇）
    - 2.6 LCD1602

- 3.0 能耗监测
    - 3.1 ACS712-05B霍尔电流传感器
    - 3.2 DFRobot Gravity:I2C数字功率计模块
    - 3.3 能耗监测模块对传感器精度影响

- 4.0 系统框架图

- 5.0 引脚分配图

- 6.0 函数功能表 


# 0.0 ESP8266 基础信息
ESP8266-DevKitC ⼊⻔指南：https://www.espressif.com/sites/default/files/documentation/ESP8266-DevKitC_getting_started_guide__CN.pdf  
引脚功能详见ESP8266EX技术规格书 (主要参考资料)：https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_cn.pdf  

如下为管脚排布：

<div align = center>
<img height = '350' img src="https://cdn.jsdelivr.net/gh/Reikimen/Image@main/furp/ESP8266.png"/>
</div>

有用的博客：  
WiFi-ESP8266入门开发(十一)-使用PWM: https://blog.csdn.net/solar_Lan/article/details/79249083

# 1.0 传感器
## 1.1 温湿度传感器
目前使用的温湿度传感器更改为：SHT30 防水数字IIC湿度探头  
sht40 datasheet: https://sensirion.com/media/documents/33FD6951/640B22DB/Datasheet_SHT4x.pdf   
(sht40)需要安装arduino的库，因此不知道是否适合之后的使用

如下为引脚图，本次购买的均为A版

接线方式为D2(GPIO4)接SHT30 的 SDA，D1(GPIO5)接SHT30 的 SCL，然后SHT30是3.3V驱动  
<div align = center>
<a href="https://sm.ms/image/r3wBQYuFz4Lt7Nm" target="_blank">
<img height = '400' img src="https://s2.loli.net/2023/06/23/r3wBQYuFz4Lt7Nm.png" ></a>
</div>
目前，温度传感模块没有定制线长，焊接杜邦线，使用I2C的方式连接到ESP8266上。 

以下为一些可以借鉴的博客：  
ESP8266/32 (Arduino)驱动SHT30获取温湿度：https://blog.csdn.net/qq_43415898/article/details/115529460  
Arduino ESP8266实现无线温湿度监测：https://blog.csdn.net/mbjxking/article/details/117406101  

## 1.2 CO2传感器
因为datasheet付费下载，附上链接。  
JW01-CO2-V2.2数字信号空气质量模块规格书: https://max.book118.com/html/2022/0607/5143210143004240.shtm   
以下为一些基本的属性：
<a href="https://sm.ms/image/wYq8TIDLE9n4ZCm" target="_blank"><img src="https://s2.loli.net/2023/06/23/wYq8TIDLE9n4ZCm.png" ></a>
可能有用的资料：  
淘宝上别的商家提供的教程：https://pan.baidu.com/s/1_tPl6m6C32AkPFusqbmOpw?pwd=426d  
博客，micropython中使用jw01二氧化碳传感器获取数据: https://blog.csdn.net/limaning/article/details/131156686 （树莓派pico）

## 1.3 PH传感器(不适用)
选用的PH传感器为，可充型  
目前江帆正在跟店家交涉要资料，如下为链接和密码  
Password：z5cp
Link：https://pan.baidu.com/s/1_DIqaSk_0aHw_fzwgiEt0w  
因为根据资料，PH传感器不能长时间浸液体使用，因此目前不考虑使用

## 1.4 光敏传感器
### 1.4.1 光合有效辐射传感器
PS：这个链接里购买只需要259RMB：  
https://item.taobao.com/item.htm?spm=a21n57.1.0.0.59f1523cDI8vUo&id=712234238518&ns=1&abbucket=0#detail

<div align = center>
<img height="340" img src="https://s2.loli.net/2023/06/25/tIZH1cUwzs3WN45.png"/>
</div>
使用的资料暂未找到，需要去跟店家要，并且不知道它的型号，下周找PHD使用他的传感器

### 1.4.2 DFROBOT光线传感器
DFROBOT光线传感器：
https://wiki.dfrobot.com.cn/_SKU_SEN0228_Gravity_Digital_Ambient_Light_Sensor%E6%95%B0%E5%AD%97%E7%8E%AF%E5%A2%83%E5%85%89%E4%BC%A0%E6%84%9F%E5%99%A8

供电电压：3.3~5V  
工作电流：45uA  
关断模式：0.5uA  
接口：I2C  
I2C地址：0x10  


## 1.5 摄像（ESP32-CAM）
安信可提供的资料:  
安信可官网：https://docs.ai-thinker.com/esp32-cam  
摄像头使用说明：https://docs.ai-thinker.com/_media/esp32_camera%E5%9B%BA%E4%BB%B6%E6%9B%B4%E6%96%B0%E8%AF%B4%E6%98%8E.pdf  
ESP32-CAM规格书：https://docs.ai-thinker.com/_media/esp32/docs/esp32-cam_product_specification_zh.pdf  
博客，教程ESP32-CAM摄像头开发demo 局域网拍照、实时视频、人脸识别: https://aithinker.blog.csdn.net/article/details/108000974  
开发者社区：  
博客，ESP32-CAM：规格、引脚排列和用户指南：https://blog.csdn.net/feiduoxuetang/article/details/119881722  
博客，安信可ESP32-CAM摄像头开发demo--局域网拍照、实时视频、人脸识别：[ESP32-CAM]
<div align = center>
<img height="350" img src="https://cdn.jsdelivr.net/gh/Reikimen/Image@main/furp/ESP32-CAM-Pins.png"/>
</div>

## 1.6 水位传感器
<div align = center>
<img height="250" img src="https://s2.loli.net/2023/06/27/IpnCbctMyzTEsGj.jpg"/>
</div>
<div align = center>
<img height="294" img src="https://s2.loli.net/2023/06/27/hCgnMpGA9VvHFua.jpg"/>
</div>


# 2.0 被控元件
## 2.1 开关 & 空占比控制电压
关于低电压控制高电压，PHD给出的建议是使用MOS管来控制电路的开合，可以自行打PCB来控制。但是网上找到的资料就只有如下链接内的（资料之间都是互相抄的），并且不清楚安全性。

博客，mos 控制交流_如何用单片机控制220V交流电的通断：https://blog.csdn.net/weixin_39793553/article/details/111706552  

<div align = center> 
<img height="400" img src="https://cdn.jsdelivr.net/gh/Reikimen/Image@main/furp/81647b8ec3cd185623201ad31ea13b5.png"/>
</div>

<div align = center> 
<img height="700" img src="https://cdn.jsdelivr.net/gh/Reikimen/Image@main/furp/045ecad11abbb2627e1b60c63d54ba4.png"/>
</div>

## 2.2 照明灯
原计划，购买了6根0.5m防水的LED植物粉光灯带。使用2根照明，4根照明，6根照明进行粗糙的3级补光照明。分别记为一档，二档，三档照明。  

设计方案B(6.27):
首先使用电源适配器获得稳定的，能够提供大电流的5VDC电源,改变空占比。

然后使用可编程的RGB灯带，使用MCU来控制颜色。与白色的LED灯带混用，来打造一个偏红和偏蓝的灯源。PS：单一颜色的LED，例如红色LED灯能提供的波长范围较小，只有+-10nm不到的频谱区间  

<div align = center> 
<img height="350" img src="https://s2.loli.net/2023/06/27/QYnZvi9RFrdK8ly.jpg"/>
</div>

<div align = center> 
<img height="600" img src="https://s2.loli.net/2023/06/27/dUAJf5OGF3MiQpa.jpg"/>
</div>



## 2.3 加热模块（硅胶）
硅胶加热板安装方式

1.在平坦和光滑的工件上可以用压敏胶来粘接。

2.压敏胶的使用温度为：150℃连续，230℃瞬间。功率密度不超过0.9W/c㎡的场合。

3.涂复压敏胶的硅橡胶加热器在工厂出厂后半年内使用，否则会影响胶水的使用性能。

4.小型工件可以来工厂预制和硫化，可以确保加热板的使用寿命。

硅胶加热板使用说明

1.使用该类电热器件须注意，其持续使用工作温度应小于240℃，瞬时不超过300℃。

2.硅胶电热器件可工作与受压状态，即用辅助压板使其紧贴受热表面。热传导良好，在工作区温度不超过240℃时，其电流密度可达3W/c㎡ 。

3.粘贴式安装工况下，允许工作温度小于150℃。

4.若是空中干烧况，受材料耐温限制，其电力密度应小于1 W/c㎡；非持续工况，电力密度可达1.4 W/c㎡ 。

5.工作电压选取以大功率-高电压、小功率-低电压为原则，特殊需要可以列外。

硅胶加热板制作工艺

不锈钢云母加热器是采用Cr20Ni80为发热体绕制在预制好绝缘体的云母上。然后用金属不锈钢皮、铁皮或铜皮为导热体制作而成。可以做成圈板等其它异性型产品。

## 2.4 制冷模块（半导体）
半导体制冷只能做到局部的降温。

## 2.5 风扇
### 2.5.2 机箱风扇
购买的为，双风扇带调速器  
购买链接：https://item.taobao.com/item.htm?spm=a230r.1.14.32.53497bc3hta7z1&id=702562582969&ns=1&abbucket=15#detail

<div align = center>
<img height = '300' img src="https://s2.loli.net/2023/06/25/EyAIST6tDBekdiF.png"/>
</div>

根据目前的设计来看，双风扇机箱风扇是合适的，并且可以做到无极调节。  
但是我打算把它自带的适配器换成自己的12V电压的适配器，并且使用空占比来调节风扇功率（参考2.1）

### 2.6 LCD1602
常用的液晶显示屏，I2C连接

# 3.0 能耗监测
## 3.1 ACS712-05B霍尔电流传感器
如下为datasheet链接：[ACS712]  
博客，ACS712工作原理（20A为例）、设计及PCB布线：[ACS712工作原理（20A为例）、设计及PCB布线]

<div align = center>
<img height = '300' img src="https://s2.loli.net/2023/06/25/k82hDzeMmQHtXsS.png"/>
</div>

## 3.2 DFRobot Gravity:I2C数字功率计模块
DFROBOT的资料：
https://wiki.dfrobot.com.cn/_SKU_SEN0291__Gravity_I2C%E6%95%B0%E5%AD%97%E5%8A%9F%E7%8E%87%E8%AE%A1#.E6.9B.B4.E5.A4.9A

## 3.3 传感模块对传感器精度影响
需要对比验证，根据实验具体情况具体分析 (江帆)

# 4.0 系统框架 *未定
flowchart  
  
7.10 系统组成 
一个LCD显示屏  
一个温湿度传感器  
一个二氧化碳传感器  
一个光敏传感器  
一个水位传感器  
220转5V8A电源适配器 + PWM放大模块 + 5-10 个照明灯带 + 能耗检测模块  
硅胶加热板(待调参) + MOS开关  
制冷模块+ MOS开关  
220转12V2A电源适配器 + PWM放大模块 俩个风扇 + 能耗检测模块  


# 5.0 引脚分配图 *未定

|对应元件|功能|引脚|*|引脚|功能|对应元件|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|日奈|宫子|伊吕波|*|美游|未花|小梓|
|日奈|宫子|伊吕波|*|美游|未花|小梓|


# 6.0 函数功能表 *未定
|函数名|函数作用|备注|
|:---|:---|:---|
|日奈|伊吕波|未花|
|日奈|伊吕波|未花|

  
  
  


# 备注：
我发现 DFROBOT 它提供的资料非常完整详细，包括datasheet，示例，以及操作教程等。如果之后购买元件，找它家买，它有个官网，https://www.dfrobot.com.cn/  
还有比如它的二氧化碳传感器模块：
[DFROBOT的二氧化碳传感器](https://wiki.dfrobot.com.cn/_SKU_SEN0159_CO2_%E4%BA%8C%E6%B0%A7%E5%8C%96%E7%A2%B3%E4%BC%A0%E6%84%9F%E5%99%A8%E6%A8%A1%E5%9D%97_V2)  








<!--链接-->
[ESP32-CAM]:https://aithinker.blog.csdn.net/article/details/108000974?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-108000974-blog-119881722.235%5Ev38%5Epc_relevant_sort_base2&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-108000974-blog-119881722.235%5Ev38%5Epc_relevant_sort_base2&utm_relevant_index=1  

[ACS712]:https://pdf1.alldatasheet.com/datasheet-pdf/view/168326/ALLEGRO/ACS712.html

[鱼缸风扇]:https://item.taobao.com/item.htm?id=706275939995&ali_refid=a3_430582_1006:1681220755:N:VPZbyjFm9B%2FIS43eeDd0Vb2Ozm4nW%2FMy:9bb9616dedbfcb7db77ebfef5eb30af8&ali_trackid=1_9bb9616dedbfcb7db77ebfef5eb30af8&spm=a21n57.1.0.0#detail


[ACS712工作原理（20A为例）、设计及PCB布线]:https://blog.csdn.net/liulangqingchun444/article/details/124118521?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-124118521-blog-84340808.235%5Ev38%5Epc_relevant_anti_t3&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-124118521-blog-84340808.235%5Ev38%5Epc_relevant_anti_t3&utm_relevant_index=1
