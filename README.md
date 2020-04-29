srsGUI
========

srsGUI is a free and open-source graphics library for SDR using Qt and Qwt. The library provides a number of useful plots for graphing real and complex numbers. Each plot is designed to be frequently updated with new data.

srsGUI is provided under the LGPLv3 license.

Current Features: 
 * Real plot - simple line plot.
 * Complex plot - plot including real, imaginary, magnitude and phase values.
 * Scatter plot - 2-D scatter plot for complex-valued data.
 * Waterfall plot - includes a line plot and waterfall plot showing past values using a colour legend.

Download & Install Instructions
=================================

Requirements: Boost (thread, unit_test_framework, system), QT5 and Qwt6

To install Boost, QT5 and Qwt6, use your distribution packet management system.
For instance in ubuntu you can run: ```sudo apt-get install libboost-system-dev libboost-test-dev libboost-thread-dev libqwt-qt5-dev qtbase5-dev```


Finally, to download and build srsGUI, just run: 
```
git clone https://github.com/srsLTE/srsGUI.git
cd srsgui
mkdir build
cd build
cmake ../
make 
```

The library can also be installed using the command ```sudo make install```. 

Running srsGUI Examples
========================

The library includes a number of tests which illustrate use of both C and C++ interfaces. These can be found in the test folder. After building the library, these tests can be executed using ```make test```
