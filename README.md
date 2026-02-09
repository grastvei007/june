# june
The june automation project

Easy to share and use values between applications across the network.



# prepare build environment for Rasberry Pi
This guide can be use to compile Qt for Rasberry Pi https://www.tal.org/tutorials/building-qt-65-raspberry-pi-raspberry-pi-os

But this needs Qt 6.9.1 and then the following links should be download and compiled as in the guide.

- QtBase: https://download.qt.io/official_releases/qt/6.9/6.9.1/submodules/qtbase-everywhere-src-6.9.1.tar.xz
- websocket: https://download.qt.io/official_releases/qt/6.9/6.9.1/submodules/qtwebsockets-everywhere-src-6.9.1.tar.xz
- serialport: https://download.qt.io/official_releases/qt/6.9/6.9.1/submodules/qtserialport-everywhere-src-6.9.1.tar.xz
- httpserver: https://download.qt.io/official_releases/qt/6.9/6.9.1/submodules/qthttpserver-everywhere-src-6.9.1.tar.xz

It is also required to install WiringPi: https://github.com/WiringPi/WiringPi

- libgtest-dev

create this file for cmake to detect it is a raspberry pi: /opt/vc/include/bcm_host.h

# build on rasperry pi
When the build environment is installed, and the source code is cloned. Then from the root dir of the project:
	mkdir build
	cd build
	cmake -G Ninja ../
	cmake --build . --parallel 4

# Additionnal sotware for rasperry pi for logging values

- InfluxDb2
- Grafana (to view logged data)

# Install the build 
	make the following directories
	/opt/june/bin
	/opt/june/lib
	
	copy files from the build directory.
	
# Run plugins with the server
	in the .config dir create folder june and create server.conf there
	
	example server.conf
	[plugins]
	bmsd=false
	ds18820=true
	[global]
	plugindir=/opt/june/lib
	

	
