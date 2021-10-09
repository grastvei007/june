TEMPLATE = subdirs


SUBDIRS += \
#    bluepower \
    june \
    tagsystem \
    device \
    influxdb \
     server \
    hwcom # \
#    junesmarthome



hwcom.file = hwcom/junehwcom.pro
server.file = server/juneserver.pro


#june.depends = tagsystem device influxdb
device.depends = tagsystem
server.depends = tagsystem
hwcom.depends = device tagsystem
piclient.depends = tagsystem


