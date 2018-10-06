SUBDIRS = client server

.PHONY: all clean

all:

	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done

clean:

	for dir in $(SUBDIRS); do \
		rm tcp_$$dir; \
	done

	
