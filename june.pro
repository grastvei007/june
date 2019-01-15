TEMPLATE = subdirs


SUBDIRS += \
    tagsystem \
    device \
#    june \
#    influxdb \
    juneserver \
#    junetool \
    piclient \
#    heater \
#    junemodulerunner \
    junehwcom

tagsystem.subdir = tagsystem/tagsystem
device.subdir = device/device
piclient.subdir = piclient/piclient
junehwcom.subdir = junehwcom/junehwcom

june.depends = tagsystem device influxdb
device.depends = tagsystem
juneserver.depends = tagsystem
junehwcom.depends = device tagsystem

