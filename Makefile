QMAKE=qmake

ifdef KDE_SUPPORT

# KDE paths, change if necessary

KDE_INCLUDE_PATH=`kf5-config --prefix`/include/KF5
KDE_LIB_PATH=`kf5-config --prefix`/lib/kf5/
KDE_LIBS=-lKF5KIOCore

QMAKE_OPTS=DEFINES+=KDE_SUPPORT INCLUDEPATH+=$(KDE_INCLUDE_PATH) \
           LIBS+="$(KDE_LIBS) -L$(KDE_LIB_PATH)"

endif

src/exmplayer:
	+cd src && $(QMAKE) $(QMAKE_OPTS) && $(DEFS) make

clean:
	if [ -f src/Makefile ]; then cd src && make distclean; fi


