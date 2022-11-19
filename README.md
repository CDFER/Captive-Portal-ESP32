# ESP32 Cross Platform Captive Portal ✨

[![Hippocratic License HL3-CL-EXTR-FFD-MEDIA-MIL-MY-SV-TAL](https://img.shields.io/static/v1?label=Hippocratic%20License&message=HL3-CL-EXTR-FFD-MEDIA-MIL-MY-SV-TAL&labelColor=5e2751&color=bc8c3d)](https://firstdonoharm.dev/version/3/0/cl-extr-ffd-media-mil-my-sv-tal.html)

A ESP32 Captive Portal written in Arudino C++ (think airport wifi sign in page) demo that works on all devices[^1].

## ⚙️ Features
```
RAM:   [=         ]  11.6% (used 37976 bytes from 327680 bytes)
Flash: [==        ]  22.6% (used 711089 bytes from 3145728 bytes)
```
- about 0.1s reload time using modern browsers and systems
- Lots of comments that explain how it all works

## 🖼️ User interface
![User interface](/images/banner.jpg)

## 📲 Quickstart with ESP Home Flasher tool on Windows, MacOS and Linux

This is a simple all in one GUI tool that can be downloaded from here: <https://github.com/esphome/esphome-flasher/releases/>

Download the firmware from the releases page and chuck it in select the serial port from the dropdown and press flash ESP

If running Windows , you will most likely need a driver from here: <https://www.wemos.cc/en/latest/ch340_driver.html> before your computer will show the ESP32 com port in the drop down menu in ESPhome Flasher.

### Compile yourself using PlatformIO

- Make sure Git client is installed on your system. https://github.com/git-guides/install-git
- Download and install Visual Studio Code by Microsoft. https://code.visualstudio.com/download
- Open Visual Studio Code and go to the Extensions manager (the icon with the stacked blocks in the left bar)
- Search for platformio and install the PlatformIO extension
- Download the source code by running a git clone (git gui can be found in your right click menu) with the link: https://github.com/CDFER/Captive-Portal-ESP32.git in your projects folder.
- In VS Code Go to File -> Open Folder and open that root folder (the one that contains platformio.ini, NOT the src folder)
- Upload to the esp32 using the right arrow button in the bottom left corner of vs code (it takes awhile for the first compile)


## Testing Status

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
| ✅      | V0.2.0    | ✅       | ✅     | ✅          |                         | iPhone X            | Default | thx @SNERTTT         |
| ✅      | V0.2.0    | ✅       | ✅     | ✅          |                         | Redmi Note 10       | Default | thx @SNERTTT         |
| ✅      | V0.2.0    | ✅       | ✅     | ✅          | iOS 16                  | iPhone XR           | Default |                      |
| ❌      | V0.2.0    | ✅       | ❌     | ✅          | MacOS Monterey (12.5.1) | Macbook Pro 16 2019 | Chrome  |                      |
| ❌      | V0.2.0    | ✅       | ❌     | ✅          | MacOS Monterey (12.5.1) | Macbook Pro 16 2019 | Safari  |                      |
| ✅      | V0.1      | ✅       | ✅     | ✅          | Win 10 Pro              | XPS15 9575          | Edge    |                      |
| ✅      | V0.1      | ✅       | ✅     | ✅          | Win 10 Edu              | XPS15 9570          | Edge    |                      |
| ✅      | V0.1      | ✅       | ✅     | ✅          | Android 12 (OneUI4.1)   | Samsung S20 FE 5G   | Default |                      |

### Did it work?

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


### Future Dev Options to look into (Help or suggestions are appreciated):

- Set client DHCP IP address range in private space (currently clients must accept DHCP Server Range: 4.3.2.2 to 4.3.2.12)
- Support integrating the DHCP or IPv6 Router Advertisement (RA) options for Captive Portals on iOS 14+ and macOS Big Sur+ https://developer.apple.com/news/?id=q78sq5rv
- Port https://github.com/Aircoookie/WLED-WebInstaller


## ✌️ Other

This work was done as part of a project with Simon Ingram of Terrestrial Assemblages with the support of Govett-Brewster Art Gallery / Len Lye Centre

Thanks to @me-no-dev and everyone at @Espressif Systems for making a really awesome chip and porting it to arduino

Thanks to @LTRTNZ and @vincentd123 for putting up with my never ending shit and @Vincent for helping me through this crazy year


[^1]: devices from the last 10 years, or that's the goal of this project :)
