# ESP32 Cross Platform Captive Portal Example 
## Built using Platformio and the Arduino C++ core

A ESP32 Captive Portal (think airport wifi sign in page) example that works on all devices (or that's the goal).

When you connect to the wifi "captive" password "12345678" it should take you straight to <http://4.3.2.1/> and display a green page with some simple text.

| Status | Version   | Connect | Popup | Serve Page | OS                      | Device Name         | Browser | Notes                |
|--------|-----------|---------|-------|------------|-------------------------|---------------------|---------|----------------------|
| ✅      | V0.3.0    | ✅       | ✅     | ✅          | Win 11 Home (22H2)      | XPS15 9550          | Firefox |                      |
| ✅      | V0.3.0    | ✅       | ✅     | ✅          | Win 11 Home (22H2)      | XPS15 9550          | Chrome  |                      |
| ❌      | V0.3.0    | ❌       | ✅     | ✅          | Android 11 (OxygenOS11) | Oneplus 6           | Default | Cellular must be off |
| ✅      | V0.3.0    | ✅       | ✅     | ✅          | MacOSX (10.6.8)         | Macbook Air (2011)  | Safari  |                      |
| ✅      | V0.3.0    | ✅       | ✅     | ✅          | Windows 7 Starter       | Toshiba NB200       | IE      |                      |
| ✅      | V0.3.0    | ✅       | ✅     | ✅          | iOS 9 (9.3.5)           | iPad mini (2012)    | Default |                      |
| ✅      | V0.3.0    | ✅       | ✅     | ✅          | Android 9 (OneUI1)      | Samsung A53         | Default |                      |
| ✅      | V0.3.0    | ✅       | ✅     | ✅          | iOS 10 (10.3.3)         | iPhone 5c           | Default |                      |
| ✅      | V0.2.0    | ✅       | ✅     | ✅          | iOS 16                  | iPhone XR           | Default |                      |
| ❌      | V0.2.0    | ✅       | ❌     | ✅          | MacOS Monterey (12.5.1) | Macbook Pro 16 2019 | Chrome  |                      |
| ❌      | V0.2.0    | ✅       | ❌     | ✅          | MacOS Monterey (12.5.1) | Macbook Pro 16 2019 | Safari  |                      |
| ✅      | V0.1      | ✅       | ✅     | ✅          | Win 10 Pro              | XPS15 9575          | Edge    |                      |
| ✅      | V0.1      | ✅       | ✅     | ✅          | Win 10 Edu              | XPS15 9570          | Edge    |                      |
| ✅      | V0.1      | ✅       | ✅     | ✅          | Android 12 (OneUI4.1)   | Samsung S20 FE 5G   | Default |                      |

## Quickstart with ESP Home Flasher tool on Windows, MacOS and Linux

This is a simple GUI-based tool that can be downloaded from here: <https://github.com/esphome/esphome-flasher/releases/>

If running Windows, you will most likely need a driver from here: <https://www.wemos.cc/en/latest/ch340_driver.html> before your computer will show the COM port in ESPhome Flasher.

## Did it work?

If you test this code on a device (even if it works) it would be really helpful if you fill out the form here: <https://forms.gle/ArLPTnwRA3QGTKyc6>

## Known Bugs/limitations with current version

- Oneplus 6 phone (Oxygen OS 11) sometimes gets stuck on setting client side IP address when cellular is on
- On older devices you may need to open a web browser for it to display
- max of 4 clients connected at the same time
- MacOS post macOS Big Sur no pop up

### Further testing required

- If you have a lot of tabs open in Windows 11 (and probably other OS) it increases the load on the ESP32 DNS server.
- HTML Webpage being served multiple times
- Other ESP32 chip variants (all testing so far is on the ESP32 D0WDQ6 chip in the ESP32S module)
- Test increasing the max clients connected up from 4 to max supported 10

### Future features that I'm looking to try and add (Help or suggestions are appreciated):

- add CORS for a REST API compatability https://docs.aws.amazon.com/apigateway/latest/developerguide/how-to-cors.html
- Set client DHCP IP address range in private space (currently clients must accept DHCP Server Range: 4.3.2.2 to 4.3.2.12)
- Support integrating the DHCP or IPv6 Router Advertisement (RA) options for Captive Portals on iOS 14+ and macOS Big Sur+ https://developer.apple.com/news/?id=q78sq5rv
- Port https://github.com/Aircoookie/WLED-WebInstaller

### Compile yourself using PlatformIO

- Make sure Git client is installed on your system.
- Download and install Visual Studio Code by Microsoft.
- Open VS Code and go to the Extensions manager (the icon with the stacked blocks in the left bar)
- Search for platformio ide and install the PlatformIO extension
- Download the source code by executing git clone https://github.com/CDFER/Captive-Portal-ESP32.git. in some folder.
- In VS Code Go to File -> Open Folder and open that root folder (the one that contains platformio.ini, NOT the src folder)
- Upload to the esp32 using the right arrow button in the bottom left corner of vs code

Made with love by Chris Dirks (@cd_fer) in Aotearoa New Zealand

