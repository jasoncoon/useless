# Arduino Controlled Moody Useless Machine #

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/eUkolWt0YG0/0.jpg)](http://www.youtube.com/watch?v=eUkolWt0YG0)

I have a [Useless Machine by Spikenzie Labs](http://www.spikenzielabs.com/Catalog/index.php?cPath=51), and it's been very entertaining for my kids and I, but it does the same thing every time and gets old quickly.  I wanted to build a programmable, Arduino controlled useless machine that has an attitude.  I've [seen](http://www.instructables.com/id/Arduino-Useless-Box/) [many](http://www.lamja.com/?p=451) [online](http://www.instructables.com/id/How-to-build-another-useless-machine-easy-to-make-/), but couldn't find a kit to build one, so I set out to build one "from scratch".

Since I'm new to using servos, I wanted something that would "just work", so of course I turned to [Adafruit](https://www.adafruit.com).  I've been wanting to try out their new line of Feather microcontroller boards, and saw that they now have a [Servo FeatherWing (shield)](https://www.adafruit.com/products/2928).  I debated which Feather board to use, and decided on the [32u4](https://www.adafruit.com/products/2771), since it's fairly inexpensive, simple, and likely has the lowest power consumption.  I don't need Wi-Fi, BLE, etc.

### Construction ###

I really like the physical construction/layout and "animations" of this (Useless Box by Sally71](https://www.youtube.com/watch?v=tGCW8xftdOA).  I managed to find a [Wooden Recipe Box](http://www.michaels.com/artminds-wooden-recipe-box/10397769.html) at Michaels with similar dimensions.  It seemed large enough to contain all of the electronics, and has a magnet to keep the lid closed instead of a latch like most of their other boxes.

### Software ###

My code is currently a heavily modified version of ["Moody Useless Machine" by Lamja Electronics](http://www.lamja.com/?p=451).  I had to modify it to use the Adafruit Servo Driver library, change the pulse length (positions) for the servos I used, and my very different physical layout.

### Parts ###

Cost   | Name | Description
------ | ---- | -----------
$12.00 | [TowerPro SG-5010 standard servo](https://www.adafruit.com/product/155)               | Servo for the arm that turns off the switch.
$5.95  | [TowerPro SG-92R Micro servo](https://www.adafruit.com/product/169)                   | Servo for the arm that opens the door/hatch.
$19.95 | [Adafruit Feather 32u4](https://www.adafruit.com/products/2771)                       | Any microcontroller should work.
$9.95  | [8-Channel PWM or Servo FeatherWing](https://www.adafruit.com/products/2928)          | Any servo shield/breakout should work, and may not even be required.
$2.95  | [4 x AA Battery Holder with On/Off Switch](https://www.adafruit.com/products/830)     | To power the servo shield.
$9.95  | [Lithium Ion Polymer Battery - 3.7v 1200mAh](https://www.adafruit.com/products/258)   | To power the microcontroller.
$5.99  | [Wooden Recipe Box](http://www.michaels.com/artminds-wooden-recipe-box/10397769.html) | 
$3.49  | [SPST Flat Lever Toggle Switch](https://www.radioshack.com/products/spst-6amp-lever)  | 
       | Various bits of thin wood.                                                            | For servo support, arms, etc.
$70.23 | Total

I'm going to try to reduce the parts cost by $30 by replacing the Feather with a [5V Pro Trinket](https://www.adafruit.com/product/2000) and omitting the Servo FeatherWing and lithium battery.  I think the 6V (4 x AA) battery pack can power both the Trinket and servos.  I might add a capacitor to prevent the Trinket from seeing a voltage drop when driving the servos.

### Software & Libraries ###

* [Arduino](https://www.arduino.cc/en/Main/Software)
* [Adafruit Servo Driver](https://learn.adafruit.com/16-channel-pwm-servo-driver/using-the-adafruit-library)