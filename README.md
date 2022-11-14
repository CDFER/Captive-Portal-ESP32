# ESP32 Cross Platform Captive Portal Example

A ESP32 Captive Portal (think airport wifi sign in page) example that works on all devices (or that's the goal).

When you connect to the wifi "captive" password "12345678" it should take you straight to http://4.3.2.1/ and display some simple text.

| Status | Issue    | Version | Device Name             | Browser | OS                      |
|--------|----------|---------|-------------------------|---------|-------------------------|
| ✅      |          | V0.2.0  | Iphone XR               | Default | iOS 16                  |
| ✅      |          | V0.2.0  | XPS15 9550              | Firefox | Win 11 Home             |
| ✅      |          | V0.2.0  | XPS15 9550              | Chrome  | Win 11 Home             |
| ✅      |          | V0.2.0  | Samsung A53             | Default | Android 9 (OneUI1)      |
| 🤷      | Cellular | V0.2.0  | Onplus 6                | Default | Android 11 (OxygenOS11) |
| ✅      |          | V0.1    | XPS15 9575              | Edge    | Win 10 Pro              |
| ✅      |          | V0.1    | XPS15 9570              | Edge    | Win 10 Edu              |
| ✅      |          | V0.1    | Samsung S20 FE 5G       | Default | Android 12 (OneUI4.1)   |
| ❌      | No Popup | V0.1    | Macbook Pro 16inch 2019 | Chrome  | MacOS Monterey (12.5.1) |
| ❌      | No Popup | V0.1    | Macbook Pro 16inch 2019 | Safari  | MacOS Monterey (12.5.1) |


## Quickstart with ESP Home Flasher tool on Windows, MacOS and Linux

This is a simple GUI-based tool that can be downloaded from here: https://github.com/esphome/esphome-flasher/releases/

If running Windows, you will most likely need a driver from here: https://www.wemos.cc/en/latest/ch340_driver.html before your computer will show the COM port in ESPhome Flasher.


## Did it work?
If you test this code on a device (even if it works) it would be really helpful if you fill out the form here: https://forms.gle/ArLPTnwRA3QGTKyc6



## Known Bugs with current version
- Oneplus 6 phone (Oxygen OS 11) sometimes gets stuck on setting client side IP address when cellular is on


### Further testing required
- If you have a lot of tabs open in Windows 11 (and probably other desktop OS) it increases the load on the ESP32 DNS server.
- HTML Webpage being served multiple times
- Other ESP32 chip variants (all testing so far is on the ESP32 D0WDQ6 chip in the ESP32S module)
- Test increasing the max clients connected up from 4 to max supported 10


### Future Dev Options to look into (Help or suggestions are appreciated):
- Set client DHCP IP address range in private space (currently clients must accept DHCP Server Range: 4.3.2.2 to 4.3.2.12)
- Support integrating the DHCP or IPv6 Router Advertisement (RA) options for Captive Portals on iOS 14+ and macOS Big Sur+ https://developer.apple.com/news/?id=q78sq5rv
- Port https://github.com/Aircoookie/WLED-WebInstaller


### Compile yourself using PlatformIO highly recommended
- Make sure Git client is installed on your system.
- Download and install Visual Studio Code by Microsoft.
- Open VS Code and go to the Extensions manager (the icon with the stacked blocks in the left bar)
- Search for platformio ide and install the PlatformIO extension
- Download the source code by executing git clone https://github.com/CDFER/Captive-Portal-ESP32.git. in some folder.
- In VS Code Go to File -> Open Folder and open that root folder (the one that contains platformio.ini, NOT the src folder)
- Upload to the esp32 using the right arrow button in the bottom left corner of vs code
