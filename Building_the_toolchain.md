#Building the toolchain

##as root:
```
apt-get install git autoconf build-essential gperf bison flex texinfo libtool libncurses5-dev wget gawk libc6-dev-amd64
mkdir /opt/Espressif
chown $username /opt/Espressif 
```
(replace $username with the name of the local user)

##as local user:
```
/opt/Espressif
git clone -b lx106 git://github.com/jcmvbkbc/crosstool-NG.git 
cd crosstool-NG
./bootstrap && ./configure --prefix=`pwd` && make && make install
./ct-ng xtensa-lx106-elf
./ct-ng build
```

#Setting up the SDK
download esp8266_sdk_v0.9.1.zip:  http://rghost.net/download/58019758/eff3feb46a2047a0de0d56479d21fab434429fea/esp8266_sdk_v0.9.1.zip

download esp-0.0.2.zip from the forum: http://filez.zoobab.com/esp8266/esptool-0.0.2.zip

extract esp8266_sdk_v0.9.1.zip to /opt/Espressif/ESP8266_SDK

extract esp-0.0.2.zip in to /opt/Espressif/ESP8266_SDK/

#Installing ESP tool
Download the deb for esptool from the git repo

#Prepping the at example
comment the line #include user_config.h from /opt/Espressif/ESP8266_SDK/include/osapi.h
```
cd ~
mkdir esp_sources
cd esp_sources
cp -R /opt/Espressif/ESP8266_SDK/examples/at at
cd at
wget -O Makefile https://raw.githubusercontent.com/zarya/esp8266-wiki/master/example.Makefile
make
```
If the compiler gives a error remove ```#include<stdlib.h>``` from ```user/at_ipCmd.c```

#Uploading
now upload the files in firmware directory to the module with esptool.py ( https://github.com/themadinventor/esptool/ )
```
esptool.py --port /dev/tty.usbmodem0E102EE1 write_flash 0x00000 0x00000.bin
esptool.py --port /dev/tty.usbmodem0E102EE1 write_flash 0x40000 0x40000.bin
```
