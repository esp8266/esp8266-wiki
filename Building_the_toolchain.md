#Building the toolchain

##as root:
```
apt-get install git autoconf build-essential gperf bison flex texinfo libtool libncurses5-dev wget gawk libc6-dev-amd64
mkdir /opt/Espressif
chown $username /opt/Espressif (replace $username with the name of the local user)
```

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

#Making the ESP tool
```
cd esptool
```
change the line TARGET_ARCH to LINUX
```
make
```

#Prepping the at example
comment the line #include user_config.h from /opt/Espressif/ESP8266_SDK/include/osapi.h
```
cd ~
mkdir esp_sources
cd esp_sources
cp -R /opt/Espressif/ESP8266_SDK/examples/at at
cd at
wget -O Makefile https://gist.githubusercontent.com/zarya/7e1a08160bf3b7ac220f/raw/a58ed9a1243dece92b671062bb16555844b326ab/gistfile1.mak
make
```

#Uploading
now upload the files in firmware directory to the module with esptool.py ( https://github.com/themadinventor/esptool/ )
```
esptool.py --port /dev/tty.usbmodem0E102EE1 write_flash 0x00000 0x00000.bin
esptool.py --port /dev/tty.usbmodem0E102EE1 write_flash 0x40000 0x40000.bin
```
