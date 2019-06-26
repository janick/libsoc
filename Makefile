all:

install: | /usr/local/include/libsoc
	cp lib/include/libsoc_i2c.h /usr/local/include
	cp lib++/include/*.hh /usr/local/include/libsoc
	cp lib++/include/*.hh /usr/local/include/libsoc
	cp contrib/GFX/*.hh /usr/local/include/libsoc


/usr/local/include/libsoc:
	mkdir $@
