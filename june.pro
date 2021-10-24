TEMPLATE = subdirs


SUBDIRS += \
#    bluepower \
    june \
    tagsystem \
    device \
    influxdb \
     server \
    pluginloader \
    hwcom # \
#    junesmarthome



hwcom.file = hwcom/junehwcom.pro
server.file = server/juneserver.pro
pluginloader.file = plugins/pluginload/pluginloader.pro


#june.depends = tagsystem device influxdb
device.depends = tagsystem
server.depends = tagsystem influxdb pluginloader
hwcom.depends = device tagsystem
piclient.depends = tagsystem


