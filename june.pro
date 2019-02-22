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
    virtualAvr \
    testpanel


hwcom.file = hwcom/junehwcom.pro
server.file = server/juneserver.pro
testpanel.file = tools/testpanel.pro

#june.depends = tagsystem device influxdb
device.depends = tagsystem
server.depends = tagsystem
hwcom.depends = device tagsystem
testpanel.depends = tagsystem
virtualAvr.depends = device tagsystem

