<div align="center">
  
# 💧 Smart Water Vending Machine
**The Next-Generation Automated Water Dispenser System**

[![Arduino Uno](https://img.shields.io/badge/Board-Arduino%20Uno-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![IoT Ready](https://img.shields.io/badge/IoT-ESP8266-2496ED?style=for-the-badge&logo=espressif&logoColor=white)](#)
[![Performance](https://img.shields.io/badge/Performance-Ultra%20Fast-success?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](#)

*ยกระดับตู้กดน้ำหยอดเหรียญของคุณให้เป็น "Smart Vending Machine" ด้วยโค้ดที่ถูกออกแบบมาเพื่อประสิทธิภาพสูงสุด*

</div>

---

## ✨ ทำไมต้อง Smart Water Vending?

เปลี่ยนตู้กดน้ำธรรมดาให้ทำงานได้อย่างรวดเร็ว เสถียร และล้ำสมัย พร้อมรองรับการเชื่อมต่อกับระบบเครือข่าย

🚀 **Ultra-Fast Processing** 
> ระบบได้รับการรีดประสิทธิภาพการทำงานสูงสุด (Non-blocking Architecture) กดปุ๊บน้ำไหลปั๊บ หยอดเหรียญแล้วจอแสดงผลทันที ไม่มีอาการหน่วงหรือค้าง

🛡️ **Enterprise-Grade Reliability** 
> หมดปัญหาหน้าจอกะพริบหรือระบบรวน! ด้วย Smart LCD Rendering และการจัดการหน่วยความจำระดับลึก (AVR Memory Optimization) เครื่องสามารถเปิดทำงานได้ตลอด 24 ชั่วโมง 7 วันโดยไม่มีสะดุด

🌐 **IoT Ready (Cloud Sync)**
> ล้ำหน้ากว่าด้วยการเชื่อมต่อแบบ Real-time ผสานการทำงานร่วมกับบอร์ด ESP-01 ระบบพร้อมส่งข้อมูลยอดขายและปริมาณน้ำคงเหลือเข้าสู่เซิร์ฟเวอร์แบบไร้สาย (Wi-Fi) ทันที!

⏱️ **Smart Time & Energy Management** 
> ประหยัดพลังงานอัจฉริยะ มาพร้อมระบบ Real-Time Clock (RTC) สั่งเปิด-ปิดไฟป้ายอัตโนมัติในช่วงเวลากลางคืน

---

## 💡 ไฮไลท์ทางเทคนิค
ถึงแม้ระบบจะเรียบง่ายแต่เบื้องหลังอัดแน่นไปด้วยเทคโนโลยี:
- **Zero-Delay Design:** ไม่มีการใช้ `delay()` ที่ทำให้ระบบช้าลง 
- **Safe Hardware Interrupts:** รับเหรียญได้อย่างแม่นยำ ไม่พลาดทุกยอดการเติม
- **SRAM Optimized:** ใช้ทรัพยากรบอร์ดเพียงเสี้ยวเดียวด้วยการทำ PROGMEM (`F()` Macro) 

---

## 🛠️ ฮาร์ดแวร์ที่รองรับ
1. **Arduino Uno R3**
2. **ESP-01 / ESP8266**
3. **DS3231 RTC Module**
4. **I2C LCD 20x4**
5. **Relay Module**
6. **Coin Acceptor**

## 🚀 เริ่มต้นใช้งานด่วน

1. **ดาวน์โหลด** โค้ดทั้งหมดลงในเครื่องของคุณ
2. **เชื่อมต่อสาย** ตาม `Config.h` (ระบุพินที่ใช้งานทั้งหมดไว้อย่างชัดเจน)
3. **อัปโหลด** ลงบอร์ด Arduino Uno
4. **พร้อมเปิดร้าน!** เครื่องพร้อมรับลูกค้าและเริ่มทำเงินให้คุณทันที 💸

<br>
<div align="center">
  <i>"ลงทุนน้อยกว่า แต่ได้เทคโนโลยีที่เหนือกว่า 💧"</i>
</div>
