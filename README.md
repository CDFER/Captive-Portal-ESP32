# ESP32 Cross Platform Captive Portal ✨

[![Hippocratic License HL3-CL-EXTR-FFD-MEDIA-MIL-MY-SV-TAL](https://img.shields.io/static/v1?label=Hippocratic%20License&message=HL3-CL-EXTR-FFD-MEDIA-MIL-MY-SV-TAL&labelColor=5e2751&color=bc8c3d)](https://firstdonoharm.dev/version/3/0/cl-extr-ffd-media-mil-my-sv-tal.html)

A ESP32 Captive Portal written in Arduino C++ (think airport Wi-Fi sign-in page) demo that works on all devices[^1].

This code is an example of a captive portal for the ESP32, using the AsyncTCP library. The code sets up a soft access point with the given SSID and no password and configures a DNS server to redirect all traffic to the captive portal web server running on the ESP32. The captive portal serves an HTML page with a message that all requests will be redirected to this page.

The code also includes some workarounds and documents limitations for different devices and browsers, such as a workaround for Windows 11 captive portal and limitations on the Safari (iOS) browser.

## ⚙️ Features

```
RAM:   [=         ]  11.6% (used 37976 bytes from 327680 bytes)
Flash: [==        ]  22.6% (used 711089 bytes from 3145728 bytes)
```

- About 0.1s reload time using modern browsers and systems
- Lots of comments that explain how it all works

## 🖼️ User Interface

![User interface](/images/banner.jpg)

## 📲 Quickstart with ESP Home Flasher tool on Windows, macOS, and Linux

This is a simple all-in-one GUI tool that can be downloaded from [here](https://github.com/esphome/esphome-flasher/releases/).

Download the firmware from the releases page and select the serial port from the dropdown menu. Press the "Flash ESP" button to flash the ESP32.

If you are running Windows, you will most likely need a driver from [here](https://www.wemos.cc/en/latest/ch340_driver.html) before your computer will show the ESP32 com port in the drop-down menu in ESPhome Flasher.

### Compile Yourself using PlatformIO

- Make sure Git client is installed on your system. You can install it from [here](https://github.com/git-guides/install-git).
- Download and install Visual Studio Code by Microsoft from [here](https://code.visualstudio.com/download).
- Open Visual Studio Code and go to the Extensions manager (the icon with the stacked blocks in the left bar).
- Search for "platformio" and install the PlatformIO extension.
- Download the source code by running a git clone (Git GUI can be found in your right-click menu) with the link: [https://github.com/CDFER/Captive-Portal-ESP32.git](https://github.com/CDFER/Captive-Portal-ESP32.git) in your projects folder.
- In VS Code, go to File -> Open Folder and open the root folder (the one that contains platformio.ini, NOT the src folder).
- Upload to the ESP32 using the right arrow button in the bottom left corner of VS Code (it takes a while for the first compile).

## Testing Status

| Status | Version | Connect | Popup | Serve Page | OS                     | Device Name        | Browser | Notes                 |
|--------|---------|---------|-------|------------|------------------------|--------------------|---------

|-----------------------|
| ✅      | 0.5.0   | ✅       | ✅     | ✅          | Win 11 Home (22H2)     | 13600k Custom PC   | Firefox |                       |
| ✅      | 0.5.0   | ✅       | ✅     | ✅          | Win 11 Home (22H2)     | 13600k Custom PC   | Chrome  |                       |
| ❌      | 0.5.0   | ❌       | ✅     | ✅          | Android 11 (OxygenOS11) | OnePlus 6          | Default | Cellular must be off  |
| ✅      | 0.5.0   | ✅       | ✅     | ✅          | Android 9 (OneUI1)     | Samsung A53        | Default |                       |
| ✅      | 0.5.0   | ✅       | ✅     | ✅          | Win 11 Home (22H2)     | XPS15 9550         | Firefox |                       |
| ✅      | 0.5.0   | ✅       | ✅     | ✅          | Win 11 Home (22H2)     | XPS15 9550         | Chrome  |                       |
| ✅      | 0.4.0   | ✅       | ✅     | ✅          | Ubuntu 22.04           | HP Pavilion PC     |         |                       |
| ✅      | 0.4.0   | ✅       | ✅     | ✅          | iOS 16.2               | iPhone X           |         |                       |
| ✅      | 0.4.0   | ✅       | ✅     | ✅          | Android 12             | Galaxy Tab A7 Lite |         |                       |
| ✅      | 0.3.0   | ✅       | ❌     | ✅          | macOS X (10.6.8)       | MacBook Air (2011) | Safari  |                       |
| ✅      | 0.3.0   | ✅       | ❌     | ✅          | Windows 7 Starter      | Toshiba NB200      | IE      |                       |
| ✅      | 0.3.0   | ✅       | ✅     | ✅          | iOS 9 (9.3.5)          | iPad Mini (2012)   | Default |                       |
| ✅      | 0.3.0   | ✅       | ✅     | ✅          | iOS 10 (10.3.3)        | iPhone 5c          | Default |                       |
| ✅      | 0.2.0   | ✅       | ✅     | ✅          |                        | iPhone X           | Default | thx @SNERTTT          |
| ✅      | 0.2.0   | ✅       | ✅     | ✅          |                        | Redmi Note 10      | Default | thx @SNERTTT          |
| ✅      | 0.2.0   | ✅       | ✅     | ✅          | iOS 16                 | iPhone XR          | Default |                       |
| ❌      | 0.2.0   | ✅       | ❌     | ✅          | MacOS Monterey (12.5.1)| MacBook Pro 16 2019| Chrome  |                       |
| ❌      | 0.2.0   | ✅       | ❌     | ✅          | MacOS Monterey (12.5.1)| MacBook Pro 16 2019| Safari  |                       |
| ✅      | 0.1.0   | ✅       | ✅     | ✅          | Win 10 Pro             | XPS15 9575         | Edge    |                       |
| ✅      | 0.1.0   | ✅       | ✅     | ✅          | Win 10 Edu             | XPS15 9570         | Edge    |                       |
| ✅      | 0.1.0   | ✅       | ✅     | ✅          | Android 12 (OneUI4.1)  | Samsung S20 FE 5G  | Default |                       |

### Did it work?

If you test this code on a device (even if it works), it would be really helpful if you fill out the form [here](https://forms.gle/ArLPTnwRA3QGTKyc6).

## Known Bugs/Limitations with Current Version

- OnePlus 6 phone (Oxygen OS 11) sometimes gets stuck on setting client-side IP address when cellular is on.
- On older devices, you may need to open a web browser for it to display.
- Maximum of 4 clients connected at the same time.
- macOS post macOS Big Sur no popup.

### Further Testing Required

- If you have a lot of tabs open in Windows 11 (and probably other OS), it increases the load on the ESP32 DNS server.
- HTML webpage being served multiple times.
- Test on other ESP32 chip variants (all testing so far is on the ESP32 D0WDQ6 chip in the ESP32S module).
- Test increasing the maximum number of clients connected from 4 to the maximum supported 10.

### Future Development Options to Explore (Help or suggestions are appreciated)

- Set client DHCP IP address range in private space (currently, clients must accept DHCP Server Range: 4.3.2.2 to 4.3.2.12).
- Support integrating the DHCP or IPv6 Router Advertisement (RA) options for Captive Portals on iOS 14+ and macOS Big Sur+. [More information](https://developer.apple.com/news/?id=q78sq5rv)
- Port [WLED-WebInstaller](https://github.com/Aircoookie/WLED-WebInstaller).
- RCF 7710 DHCP option for captive portal detection. [Issue](https://github.com/CDFER/Captive-Portal-ESP32/issues/5)

### My Reading List

- [iOS 7 Captive Portal Guide](https://www.linkedin.com/pulse/ios-7-captive-portal-guide-requirements-agathe-guib%C3%A9)
- [Apple Developer News: Support for Captive Portals](https://developer.apple.com/news/?id=q78sq5rv)

## ✌️ Other

To support this and my future work, you can now purchase one of my own handmade CO2 sensors through my website: [https://www.keastudios.co.nz](https://www.keastudios.co.nz).

This work was done as part of a project with Simon Ingram of Terrestrial Assemblages with the support of Govett-Brewster Art Gallery / Len Lye Centre.

Thanks to @me-no-dev and everyone at @Espressif Systems for making a really awesome chip and porting it to Arduino.

Thanks to @LTRTNZ for putting up with my never-ending shit, and @vincentd123 for helping me through this crazy year.

[^1]: Note: It might not work on all devices due to various reasons such as captive portal detection algorithms, browser compatibility, and device limitations.
