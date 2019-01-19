TEMPLATE = subdirs


SUBDIRS += \
    tagsystem \
    device \
#    june \
    influxdb \
     server \
#    junetool \
#    piclient \
#    heater \
#    junemodulerunner \
    hwcom \
    virtualAvr


hwcom.file = hwcom/junehwcom.pro
server.file = server/juneserver.pro

#june.depends = tagsystem device influxdb
device.depends = tagsystem
server.depends = tagsystem
hwcom.depends = device tagsystem

