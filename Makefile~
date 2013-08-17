QMAKE=qmake
LRELEASE=lrelease

ifdef KDE_SUPPORT

# KDE paths, change if necessary

KDE_INCLUDE_PATH=`kde-config --prefix`/include/
KDE_LIB_PATH=`kde-config --prefix`/lib/
KDE_LIBS=-lkio

QMAKE_OPTS=DEFINES+=KDE_SUPPORT INCLUDEPATH+=$(KDE_INCLUDE_PATH) \
           LIBS+="$(KDE_LIBS) -L$(KDE_LIB_PATH)"

endif

src/exmplayer:
	+cd src && $(QMAKE) $(QMAKE_OPTS) && $(DEFS) make
	cd src && $(LRELEASE) exmplayer.pro

clean:
	if [ -f src/Makefile ]; then cd src && make distclean; fi


