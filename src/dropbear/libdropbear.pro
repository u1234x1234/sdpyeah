
TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static
VPATH += dropbear dropbear/libtomcrypt dropbear/libtommath
INCLUDEPATH += dropbear dropbear/libtomcrypt/src/headers/ dropbear/libtommath

QMAKE_CFLAGS += -DDROPBEAR_CLIENT

SOURCES += \
		test.cpp \
# dropbear common
		dbutil.c buffer.c \
		dss.c bignum.c \
		signkey.c rsa.c dbrandom.c \
		queue.c \
		atomicio.c compat.c fake-rfc2553.c \
		ltc_prng.c ecc.c ecdsa.c crypto_desc.c \
		gensignkey.c gendss.c genrsa.c \
# dropbear client
		cli-main.c cli-auth.c cli-authpasswd.c cli-kex.c \
		cli-session.c cli-runopts.c cli-chansession.c \
		cli-authpubkey.c cli-tcpfwd.c cli-channel.c cli-authinteract.c \
		cli-agentfwd.c \
# dropbear client-server
		common-session.c packet.c common-algo.c common-kex.c \
		common-channel.c common-chansession.c termcodes.c loginrec.c \
		tcp-accept.c listener.c process-packet.c \
		common-runopts.c circbuffer.c curve25519-donna.c list.c netio.c

HEADERS += test.h \
# dropbear headers
		options.h dbutil.h session.h packet.h algo.h ssh.h buffer.h kex.h \
		dss.h bignum.h signkey.h rsa.h dbrandom.h service.h auth.h \
		debug.h channel.h chansession.h config.h queue.h sshpty.h \
		termcodes.h gendss.h genrsa.h runopts.h includes.h \
		loginrec.h atomicio.h x11fwd.h agentfwd.h tcpfwd.h compat.h \
		listener.h fake-rfc2553.h ecc.h ecdsa.h
