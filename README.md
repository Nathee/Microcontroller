# Microcontroller
Lab Microcontroller

# Visual Studio Code

ดาวน์โหลด Visual Studio Code มาติดตั้ง https://code.visualstudio.com/

# PlatformIO IDE Extension

1.เปิด VS Code ขึ้นมา ที่ Tab Extension ทางซ้ายพิมพ์ค้นหา Extension ที่ชื่อ “PlatformIO IDE” จากนั้นกด install

![](https://playelek.com/wp-content/uploads/2017/11/piovscode.jpg)

2.รอการติดตั้งสักครู่ ซึ่งนอกจากจะติดตั้ง PlatformIO IDE แล้วยังจะมีการติดตั้ง extension ที่ชื่อ C/C++ มาด้วยสังเกตที่ Status Bar ด้านล่างจะแสดงสถานะว่ากำลังติดตั้ง

![](https://playelek.com/wp-content/uploads/2017/11/photo_2017-11-19_15-45-15_LI-1024x254.jpg)

3.จนมี popup ขึ้นมาว่า “Info Please reload for the installation changes to take effect.” คลิกที่ Reload ซึ่งจะทำการปิด VSCode แล้วโหลดขึ้นมาใหม่

![](https://playelek.com/wp-content/uploads/2017/11/photo_2017-11-19_15-45-19.jpg)

4.เมื่อ VSCode โหลดขึ้นมาใหม่ Tool Bar ของ PlO จะโหลดขึ้นมา (จะช้าหน่อยรอนิดหนึ่ง) ที่ status bar กดที่รูป home เพื่อโหลดหน้า PIO home ขึ้นมา

![](https://playelek.com/wp-content/uploads/2017/11/piohomeicon.jpg)

# การใช้งาน PIO IDE

1.เปิด VSCode ขึ้นมารอ PIO สักครู่ให้ PIO Toolbar โหลดขึ้นมา แล้วกดรูป home เพื่อเปิด PIO home ขึ้นมาแล้ว

![](https://playelek.com/wp-content/uploads/2017/11/vscodepiohome-1024x555.jpg)

2.คลิก “New Project” ในหน้า PIO Home จะขึ้นหน้าต่างให้สร้างโปรเจคสำหรับอุปกรณ์พิมพ์ค้นหาบอร์ดที่เราต้องการ เลือก Framework ในที่นี้ใช้ Arduino แล้วกดปุ่ม “Finish” เพื่อสร้างโปรเจค ในตัวอย่างเราใช้ DOIT esp32 Devkit (ดูเกี่ยวกับบอร์ดนี้ได้ที่ แกะกล่อง DOIT ESP32 DEVKIT V1 และ PINOUT)

![](https://playelek.com/wp-content/uploads/2017/11/pionewproject-1024x546.jpg)

3.หากในข้อ 2. ตรง Location เลือก Use default location โฟลเดอร์ของโปรเจคที่เราสร้างขึ้นจะอยู่ใน C:\Users\<Usernamre>\Documents\PlatformIO\Projects ทำการเปิดโปรเจคที่เราสร้างขึ้นมาโดยใน PIO home จะมีรายชื่อโปรเจคที่เราสร้างขึ้นคลิก “Open” โปรเจคที่เราต้องการ

![](https://playelek.com/wp-content/uploads/2017/11/openpioproject.jpg)

4.เมื่อเปิดโปรเจคขึ้นมาจะเห็นว่าในโปรเจคที่เราสร้างนั้นมีโครงสร้างโฟลเดอร์ดังรูป

![](https://playelek.com/wp-content/uploads/2017/11/pioproject.jpg)

5.เปิดไฟล์ชื่อ “main.cpp” ที่อยู่ในโฟลเดอร์ “src” นี่คือไฟล์ที่เราต้องแก้ไข

![](https://playelek.com/wp-content/uploads/2017/11/maincpp.jpg)

6.เราลองเขียนโปรแกรมง่ายๆ อย่างให้ไฟบนบอร์ดติดดับ เสร็จแล้วก็ Build โปรแกรมกดปุ่ม Build หรือคีย์ลัดคือ Ctrl+Alt+b (เหมือนใน ArduinoIDE ที่กดปุ่ม Verify เสร็จแล้ว Upload แหละค่ะ)

![](https://playelek.com/wp-content/uploads/2017/11/buildupload.jpg)

7.รอ Build สักครู่สังเกตใน Terminal จนขึ้น SUCCESS เป็นอัน Build เสร็จ

![](https://playelek.com/wp-content/uploads/2017/11/buildpio.jpg)

8.ต่ออุปกรณ์เข้ากับคอมพิวเตอร์ คลิก Upload หรือคีย์ลัด ctl+alt+u รออัพโหลด สังเกตดูใน Terminal จนขึ้น SUCCESS ( ปกติใน Arduino IDE เราต้องเลือก COM port ที่อุปกรณ์ต่ออยู่ แต่ใน PIO จะ Auto Detect ให้เลย)

![](https://playelek.com/wp-content/uploads/2017/11/uploadpio.jpg)

![](https://playelek.com/wp-content/uploads/2017/08/blinkesp32.gif)

#เกี่ยวกับ serial monitor

หลายครั้งใน arduino ide เราจะใช้ serial monitor ในการแสดงผลต่างๆ ซึ่งต้องกำหนดค่า  baud rate ทีนี้ใน PIO นั้นเราต้องไปกำหนดในไฟล์ที่ชื่อว่า platformio.ini  โดยเพิ่มบรรทัดที่กำหนดค่า monitor_baud ที่เราต้องการลงไปเช่น

monitor_baud = 115200

![](https://playelek.com/wp-content/uploads/2017/11/serialmonitor.jpg)

ใน PIO release 3.5.3 option monitor_baud  เปลี่ยนชื่อเป็น monitor_speed  แนะนำให้ใช้ monitor_speed  เพราะหลัง release 3.6.0  monitor_baud จะใช้ไม่ได้แล้ว ดังนั้นจะเป็น

monitor_speed = 115200

**ยกตัวอย่าง**  เช่น เราเขียนโปรแกรม wifi scan ในไฟล์ “main.cpp” จากนั้นก็กำหนดค่า monitor_baud ในไฟล์ “platformio.ini” หลังจากนั้นก็  Build แล้ว Upload ไปยังบอร์ดตามปกติ

เราทำการมอนิเตอร์ค่าโดยคลิกที่ Serial Monitor หรือคีย์ลัด Ctl+Alt+s

![](https://playelek.com/wp-content/uploads/2017/11/serialmonitorc.jpg)

ซึ่งจะแสดง Monitor ในแท็บ Terminal

![](https://playelek.com/wp-content/uploads/2017/11/tersm.jpg)

References

http://docs.platformio.org/en/latest/ide/vscode.html#ide-vscode

https://playelek.com/install-pio-ide-vscode/
