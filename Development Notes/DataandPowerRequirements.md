#Power draw:
* 90mA draw from dust sensor(because of the heating resistor)
* 40mA draw from Arduino
* Negligble draw from the temp/humidity sensor

##Available Batteries
* 3.7V 800mAh (cheap stuff, so more like 700-750mAh) 
* 18650s at 3500mAh that I’d rather not part with.

##Notes
Arduino takes either regulated 5v or unregulated 7-12 V (on board regulator). So for the “bare bones” application, 2 * 3.7V LiPo in series would be the minimum. 2* 18650 batteries should do the trick.

For 24 hrs of operation the optimistic estimate is 3500 mAh regulated with one of these or similar if there are any lying around:
http://uk.rs-online.com/web/p/linear-voltage-regulators/7484893/

For unregulated operation (relying on the on-board regulator) it would require up to double that. If we run it with an USB power bank, it’d require even more (20 mA draw from the UART usb communication IC that turns on when USB is plugged in).

#Memory Use
On the memory front the UNO has 1024bytes and a spare MEGA2560 i have lying around has 4k bytes. The dust sensor can be polled once 30 seconds, so at maximum rate (which is ideal for comparing as we’ll have more data points) It’ll need 2880 bytes at 8bit precision.

I think a good compromise is using the uno to poll the sensors every 2 minutes till the batteries die/squirrels nest in the box.
