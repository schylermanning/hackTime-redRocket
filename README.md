# Hacktime
HackTime Don't Read Me!!!!!!!

or

// notes for setup from Schyler Manning

++++++++++++++++++++++++++++++++++++++++++++++++
Steps Used to Connect to Arduino via Serial:
++++++++++++++++++++++++++++++++++++++++++++++++
- Install FTDI drivers
—- https://cdn.sparkfun.com/assets/learn_tutorials/7/4/FTDIUSBSerialDriver_v2_3.dmg
AND Install the Chinese FTDI drivers
- CH341SER_MAC
—- http://www.wch.cn/download/CH341SER_MAC_ZIP.html ((note this may be blocked on local network))

http://linksprite.com/wiki/index.php5?title=LinkNode_D1

- Install Arduino from the Arduino website. https://www.arduino.cc/en/Main/ArduinoMotorShieldR3
- Start Arduino and open Preferences window.
- Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install esp8266 platform
- Select the ( WeMos D1(Retired)) ESP8266 board from Tools > Board menu after installation.
—- Because the LinkNode D1 has not been added into the offcial ESP8266 Arduino core repository yet, so you can't find LinkNode D1 board on the boards list, but you can use the WeMos D1(Retired), this board is fully compotiable with LinkNode D1.
- Connect LinkNode D1 to your PC
- Check your serial port which your PC recognize
wch.cn
CH341SER_MAC.ZIP下载页面-江苏沁恒股份有限公司
江苏沁恒股份有限公司是技术主导型的高新技术企业，核心业务是接口类、SOC/MCU类集成电路及嵌入式软件的研发和销售，产品主要应用于物联网、金融税控、信息安全、工业控制等领域。 江苏沁恒股份有限公司是技术主导型的高新技术企业，核心业务是接口类、SOC/MCU类集成电路及嵌入式软件的研发和销售，产品主要应用于物联网、金融税控、信息安全、工业控制等领域

// if you have issues with the board manager make sure you copied in the correct path.
http://arduino.esp8266.com/stable/package_esp8266com_index.json