TEMPLATE = subdirs
SUBDIRS = \
		src/dropbear \
		src/app

CONFIG += ordered

include(deployment.pri)
