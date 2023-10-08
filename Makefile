MAKE=make
TAR=tar
MV=mv

# compiler les sources
all:
	$(MAKE) -C src
	$(MAKE) -C tests
	$(MAKE) -C tests_perso

# nettoyer les sources
clean:
	$(MAKE) -C src clean
	$(MAKE) -C tests clean
	$(MAKE) -C tests_perso clean

# compiler les tests
tests: all
	$(MAKE) -C tests all

test: all
	$(MAKE) -C tests test

test_all: all
	$(MAKE) -C tests test_all

archive:
	$(MAKE) -C src clean
	$(TAR) -cvjf ../`basename $$PWD`.tar.bz2 --exclude `basename $$PWD`/`basename $$PWD` --exclude .git --exclude *.tar.bz2 --exclude *.tar.gz --exclude googletest-release-* --exclude build* --exclude googletest-usr -C .. `basename $$PWD`
	$(MV) ../`basename $$PWD`.tar.bz2 ./

googletest:
	$(MAKE) -C tests googletest

distclean: clean testclean
	$(MAKE) -C src distclean

tests_perso: all
	$(MAKE) -C tests_perso all

# nettoyage
testclean:
ifeq ($(TESTS_C_DIR_EXISTS), 1)
	$(MAKE) -C tests_c clean
endif
	$(MAKE) -C tests clean

.PHONY: clean all googletest test test_all tests_perso distclean
