# ESP32 Cross Platform Captive Portal 

A ESP32 Captive Portal example that actually works on all devices (or that is the goal).
When you connect to the wifi "captive" password "12345678" it should take you straight to http://4.3.2.1/ and show the text "Hooray"

## I need you help!
If you test this code on a device (even if it works) fill out the form here: https://forms.gle/ArLPTnwRA3QGTKyc6

A list of all tested devices can be seen here: https://docs.google.com/spreadsheets/d/1588-0fG21-aaR2pWJNQjufwgPaIDbHX_0geHEn1yDHk/edit?usp=sharing

## Known Bugs at the moment

- Oneplus 6 phone (Oxygen OS 11) sometimes gets stuck on setting client side IP address when cellular is on


### Further testing requierd
- If you have a lot of tabs open in Windows 11 (and probabilly other desktop OS) it increases the load on the ESP32 DNS server.


### Future Dev Options to look into (Help or suggestions are apreciated):
- Set client DHCP IP address range in private space (currenly clients much accept to use 4.3.2.2 as thier ip)
- Support integrating the DHCP or IPv6 Router Advertisement (RA) options for Captive Portals on iOS 14+ and macOS Big Sur+ https://developer.apple.com/news/?id=q78sq5rv
- Port https://github.com/Aircoookie/WLED-WebInstaller
