# ESP32 Cross Platform Captive Portal 

An ESP32 Captive Portal example that works on all devices (or that's the goal).
When you connect to the wifi "captive" password "12345678" it should take you straight to http://4.3.2.1/ and show the text "Hooray"

| Status | Version | Device Name                          | Default Browser           | OS                        |
|--------|---------|--------------------------------------|---------------------------|---------------------------|
|    ✅   | V0.2.0  | Iphone 11                            | Default Captive (safari?) |                           |
|    ✅   | V0.2.0  | XPS15 9550                           | Firefox                   | Win 11 Home               |
|    ✅   | V0.2.0  | Samsung A53 0F 32GB (Spark Carrier)  | Default Captive (chrome?) | Android 9 (oneui 1)       |
|    ✅   | V0.1    | Samsung A53 0F 32GB (Spark Carrier)  | Default Captive (chrome?) | Android 9 (oneui 1)       |
|    🤷   | V0.1    | Onplus 6 (A6000) on Skinny NZ        | Default Captive (chrome?) | Android 11 (oxygen os 11) |
|    ✅   | V0.1    | XPS15 9575 (2 in 1)                  | Edge                      | Win 10 Pro                |
|    ✅   | V0.1    | XPS15 9550                           | Firefox                   | Win 11 Home               |
|    ✅   | V0.1    | XPS15 9550                           | Chrome                    | Win 11 Home               |
|    ✅   | V0.1    | XPS15 9570                           | Edge                      | Win 10 Edu                |
|    ✅   | V0.1    | Samsung S20 FE 5G                    | Default Captive (chrome?) | Android 12 (one UI 4.1)   |
|    ❌   | V0.1    | Macbook Pro 16inch 2019              | Chrome                    | MacOS Monterey (12.5.1)   |
|    ❌   | V0.1    | Macbook Pro 16inch 2019              | Safari                    | MacOS Monterey (12.5.1)   |
|    ✅   | V0.1    | XPS15 9550                           | Firefox                   | Win 11 Home               |
|    ✅   | V0.1    | XPS15 9550                           | Firefox                   | Win 11 Home               |

A list of all tested devices can be seen here: https://docs.google.com/spreadsheets/d/1588-0fG21-aaR2pWJNQjufwgPaIDbHX_0geHEn1yDHk/edit?usp=sharing

## Quickstart with ESP Home Flasher tool on Windows, MacOS and Linux

This is a simple GUI-based tool that can be downloaded from here: https://github.com/esphome/esphome-flasher/releases/
If running Windows, you will most likely need a driver from here: https://www.wemos.cc/en/latest/ch340_driver.html before your computer will show the COM port in ESPhome Flasher.


## Did it work?
If you test this code on a device (even if it works) it would be really helpful if you fill out the form here: https://forms.gle/ArLPTnwRA3QGTKyc6



## Known Bugs at the moment

- Oneplus 6 phone (Oxygen OS 11) sometimes gets stuck on setting client side IP address when cellular is on


### Further testing required
- If you have a lot of tabs open in Windows 11 (and probably other desktop OS) it increases the load on the ESP32 DNS server.


### Future Dev Options to look into (Help or suggestions are appreciated):
- Set client DHCP IP address range in private space (currently clients much accept to use 4.3.2.2 as their ip)
- Support integrating the DHCP or IPv6 Router Advertisement (RA) options for Captive Portals on iOS 14+ and macOS Big Sur+ https://developer.apple.com/news/?id=q78sq5rv
- Port https://github.com/Aircoookie/WLED-WebInstaller
