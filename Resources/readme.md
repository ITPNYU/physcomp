# Physical Computing Remote Learning Tools

Here are some tools for sharing circuits, code, and fabrication techniques with your classmates and instructors when you can't be physically in the same place together. 

These have been collected from a number of sources. Thanks especially to the tangible tactics group, a loose collection of faculty and staff from  [Ryerson University School of Media](https://www.ryerson.ca/rta/About/), [OCAD University Digital Futures](https://www.ocadu.ca/academics/undergraduate-studies/digital-futures) program, [Sheridan College Interaction design](https://academics.sheridancollege.ca/programs/bachelor-of-interaction-design) program, [NYU ITP/IMA](https://itp.nyu.edu), and others.  

## Video Tools

How to share your circuits live via Video

### Webcams

[epocCam](https://www.kinoni.com/) - an app for iOS and Android that converts your mobile phone into a wireless camera for your computer. You run an app on your phone and on your personal computer, and your phone shows up as just another camera available to any Zoom, FaceTime, Skype, etc. Steve Daniels recommends you buy the app. It spares you a ton of ads AND give better reolsution / connection control.  Delete the free version when you get the pay version.

## USB Microscope Cameras
* [A basic one](https://www.amazon.ca/gp/product/B00XNYXQHE)
* [A fancier one](https://www.amazon.ca/STPCTOU-Wireless-Microscope-50X-1000X-Handheld/dp/B07YL3HZCB)
* an [even fancier one](https://www.amazon.ca/Jiusion-Microscope-Resolution-Magnification-Compatible/dp/B081F64YLB)


## Tripods and mounting tools

* [Glif](https://www.studioneat.com/products/glif) - a tripod head for mobile phones
* a [less expensive alternative](https://smile.amazon.com/gp/product/B072KNBV21/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) from Amazon
* [Gorillapod flexible tripods](https://joby.com/us-en/gorillapod-flexible-camera-tripods/)
* [Gooseneck phone holder](https://www.amazon.com/Phone-Holder-Bed-Gooseneck-Mount/dp/B07PLF1KMB/) from Amazon
* [Gooseneck phone holder with Selfie Ring Light](https://www.amazon.com/dp/B07BTH1F3M/) from Amazon


### Document cameras

* [IPevo document cameras](https://www.ipevo.com/products/vz-r
). We have used these on the floor at ITP. They are good for circuit sharing in a studio or classroom setup.

## Text Tools

* [codeshare.io](https://codeshare.io/) A shared code editing site. It's very barebones, but it's fast and easy to get set up and edit together in real time. 
* Microsoft [Visual Studio Code](https://code.visualstudio.com/) is a decent text editor that is optimized for screen readers. If you have the Arduino IDE installed on your machine, the [Arduino Plugin for VS Code](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) makes a good screen reader-friendly editor. The Arduino plugin gives you access to most of the tools in the Arduino IDE: boards manager, library manager, examples, compile and upload, and serial monitor. The [VS Live Share Plugin](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare) allows you to share code live with other users over a network in real time as well. Setup time for a group is not fast, though, and requires a login.
* [github](https://github.com/) - Github is the most common code management platform used at ITP. It's very useful for managing code and circuit drawing versioning among a group. You're probably using it right now, if you're reading this. 
* [p5live](https://teddavis.org/p5live/) - allows you to share p5.js sketches and code in realtime. 

## Drawing Tools

When drawing circuits, using common [electronic schematic symbols] and sharing your drawings in editable formats like SVG (scalable vector graphics) makes it easier to share materials. Many beginners find schematics abstract at first, so breadboard-friendly drawing programs are handy as well.

* [mural.co](https://www.mural.co/) A shared drawing board. There are many others available, but this one is particularly useful because it supports SVG import, meaning you can import parts that you export from other circuit drawing programs like Fritzing or Eagle. It also has a library of standard electrical schematic symbols, making it easy to share circuit drawing exercises in real time.
* [Fritzing](https://fritzing.org/) is a circuit and schematic drawing program designed for electronics beginners. It supports drawing in breadboard view, schematic view, or printed circuit board (PCB) view. It can export many different image formats, and can be extended by making your own parts files. Many suppliers of hobbyist elextrinics parts make their parts available as Fritzing files, including [Sparkfun](https://github.com/sparkfun/Fritzing_Parts) and [Adafruit](https://github.com/adafruit/Fritzing-Library), and others.  Though it's no longer free, it's still [open source](https://github.com/fritzing/fritzing-app), and the work is self-financed by the maintainer, so the price is a good deal. 
* [Tinkercad](https://www.tinkercad.com/learn/circuits) is another berginner-friendly circuit drawing environment. It's not apparent how to import parts into it, however.
* [Inkscape](https://inkscape.org/) is a free and open source vector drawing tool.
* [Affinity Designer](https://affinity.serif.com/en-us/designer/) is a vector drawing tool similar to [Adobe Illustrator](https://www.adobe.com/products/illustrator.html), but less expensive with most of the same features. 
* [Sketch](https://www.sketch.com/) is another popular vector drawing tool among graphic designers. 

## Connected tools

The [TS04 Multimeter](https://www.generaltools.com/ts04-digitalmultimeter) ([Amazon Canada link](https://www.amazon.ca/General-Tools-TS04-Multimeter-Auto-Ranging/dp/B01FHQ3V8O), thanks Steve Daniels) is a multimeter that connects to an Android/iOS app that works through a screen reader. It is possible to [write your own HTML interface](https://github.com/tigoe/TS04-Bluetooth-Meter) for the TS04 meter as well, using the web-bluetooth JavaScript framework. Here are some [details on the TS04 protocol](https://www.tigoe.com/pcomp/code/javascript/1309/). You can connect to the connect to the TS04 meter from [this link](https://htmlpreview.github.io/?https://raw.githubusercontent.com/tigoe/TS04-Bluetooth-Meter/master/index.html) if you have one. This only works on the Chrome browser, as of this writing. 

##  Keyboard Control 

[Arduino sketch to control Zoom](https://github.com/ITPNYU/physcomp/tree/master/Labs/LabKeyboardZoom/KeyboardPushbuttonZoomControl) via a USB-native Arduino

