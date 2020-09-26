TEMPLATE = subdirs


SUBDIRS += \
    june \
    tagsystem \
    device \
#    june \
    influxdb \
     server \
#    junetool \
    piclient \
    hwcom


hwcom.file = hwcom/junehwcom.pro
server.file = server/juneserver.pro


#june.depends = tagsystem device influxdb
device.depends = tagsystem
server.depends = tagsystem
hwcom.depends = device tagsystem
piclient.depends = tagsystem


