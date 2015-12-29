TEMPLATE = subdirs
SUBDIRS = \
		src/dropbear/dropbear_subdirs.pro \
#		src/app

CONFIG += ordered

include(deployment.pri)
