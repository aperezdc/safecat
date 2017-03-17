# Makefile for safecat

default: it

alloc.a: \
makelib alloc.o alloc_re.o
	./makelib alloc.a alloc.o alloc_re.o

alloc.o: \
compile alloc.c alloc.h error.h
	./compile alloc.c

alloc_re.o: \
compile alloc_re.c alloc.h byte.h
	./compile alloc_re.c

auto-ccld.sh: \
conf-cc conf-ld warn-auto.sh
	( cat warn-auto.sh; \
	echo CC=\'`head -1 conf-cc`\'; \
	echo LD=\'`head -1 conf-ld`\'; \
	) > auto-ccld.sh

auto-str: \
load auto-str.o substdio.a error.a str.a
	./load auto-str substdio.a error.a str.a

auto-str.o: \
compile auto-str.c substdio.h readwrite.h exit.h
	./compile auto-str.c

auto_home.c: \
auto-str conf-root
	./auto-str auto_home `head -1 conf-root` > auto_home.c

auto_home.o: \
compile auto_home.c
	./compile auto_home.c

byte_chr.o: \
compile byte_chr.c byte.h
	./compile byte_chr.c

byte_copy.o: \
compile byte_copy.c byte.h
	./compile byte_copy.c

byte_cr.o: \
compile byte_cr.c byte.h
	./compile byte_cr.c

byte_diff.o: \
compile byte_diff.c byte.h
	./compile byte_diff.c

byte_zero.o: \
compile byte_zero.c byte.h
	./compile byte_zero.c

check: \
it instcheck
	./instcheck

clean: \
TARGETS
	rm -f `cat TARGETS`

compile: \
make-compile warn-auto.sh systype conf-includes
	( cat warn-auto.sh; ./make-compile "`cat systype`" ) > \
	compile
	chmod 755 compile

envread.o: \
compile envread.c env.h str.h
	./compile envread.c

error.a: \
makelib error.o error_str.o
	./makelib error.a error.o error_str.o

error.h: \
tryerrno.c compile load error.h1 error.h2
	( ( ./compile tryerrno.c && ./load tryerrno && \
	./tryerrno ) >/dev/null 2>&1 \
	&& cat error.h1 || cat error.h2 ) > error.h
	rm -f tryerrno.o tryerrno

error.o: \
compile error.c error.h
	./compile error.c

error_str.o: \
compile error_str.c error.h
	./compile error_str.c

fmt_uint64.o: \
compile fmt_uint64.c fmt.h uint64.h
	./compile fmt_uint64.c

hier.o: \
compile hier.c auto_home.h
	./compile hier.c

install: \
load install.o hier.o auto_home.o strerr.a substdio.a open.a error.a \
str.a
	./load install hier.o auto_home.o strerr.a substdio.a \
	open.a error.a str.a

install.o: \
compile install.c substdio.h strerr.h error.h open.h readwrite.h \
exit.h buffer.h
	./compile install.c

instcheck: \
load instcheck.o hier.o auto_home.o strerr.a substdio.a error.a str.a
	./load instcheck hier.o auto_home.o strerr.a substdio.a \
	error.a str.a

instcheck.o: \
compile instcheck.c strerr.h error.h readwrite.h exit.h
	./compile instcheck.c

it: \
maildir safecat man

find-systype: \
find-systype.sh auto-ccld.sh
	cat auto-ccld.sh find-systype.sh > find-systype
	chmod 755 find-systype

getln.a: \
makelib getln.o getln2.o
	./makelib getln.a getln.o getln2.o

getln.o: \
compile getln.c substdio.h byte.h stralloc.h gen_alloc.h getln.h
	./compile getln.c

getln2.o: \
compile getln2.c substdio.h stralloc.h gen_alloc.h byte.h getln.h
	./compile getln2.c

hassgact.h: \
trysgact.c compile load
	( ( ./compile trysgact.c && ./load trysgact ) >/dev/null \
	2>&1 \
	&& echo \#define HASSIGACTION 1 || exit 0 ) > hassgact.h
	rm -f trysgact.o trysgact

hostname.o: \
compile hostname.c
	./compile hostname.c

load: \
make-load warn-auto.sh systype
	( cat warn-auto.sh; ./make-load "`cat systype`" ) > load
	chmod 755 load

maildir: \
warn-auto.sh maildir.sh conf-root
	cat warn-auto.sh maildir.sh \
	| sed s}HOME}"`head -1 conf-root`"}g \
	> maildir
	chmod 755 maildir

maildir.0: \
maildir.1
	nroff -man maildir.1 > maildir.0

make-compile: \
make-compile.sh auto-ccld.sh
	cat auto-ccld.sh make-compile.sh > make-compile
	chmod 755 make-compile

make-load: \
make-load.sh auto-ccld.sh
	cat auto-ccld.sh make-load.sh > make-load
	chmod 755 make-load

makelib: \
warn-auto.sh systype
	( cat warn-auto.sh; \
	echo 'main="$$1"; shift'; \
	echo 'rm -f "$$main"'; \
	echo 'ar cr "$$main" $${1+"$$@"}'; \
	case "`cat systype`" in \
	sunos-5.*) ;; \
	unix_sv*) ;; \
	irix64-*) ;; \
	irix-*) ;; \
	dgux-*) ;; \
	hp-ux-*) ;; \
	sco*) ;; \
	*) echo 'ranlib "$$main"' ;; \
	esac \
	) > makelib
	chmod 755 makelib

man: \
safecat.0 maildir.0

open.a: \
makelib open_read.o open_trunc.o open_append.o
	./makelib open.a open_read.o open_trunc.o open_append.o

open_append.o: \
compile open_append.c open.h
	./compile open_append.c

open_read.o: \
compile open_read.c open.h
	./compile open_read.c

open_trunc.o: \
compile open_trunc.c open.h
	./compile open_trunc.c

safecat: \
load safecat.o getln.a str.a stralloc.a strerr.a substdio.a alloc.o \
alloc_re.o byte_copy.o byte_cr.o envread.o error.o error_str.o fmt_uint64.o \
hostname.o sig.o stat_dir.o str_diffn.o str_len.o substdio_copy.o \
substdi.o substdio.o taia_fmtfrac.o taia_now.o taia_tai.o tempfile.o \
writefile.o
	./load safecat getln.a str.a stralloc.a strerr.a substdio.a \
	alloc.o alloc_re.o byte_copy.o byte_cr.o envread.o error.o \
	error_str.o fmt_uint64.o hostname.o sig.o stat_dir.o str_diffn.o \
	str_len.o substdi.o substdio.o substdio_copy.o taia_fmtfrac.o \
	taia_now.o taia_tai.o tempfile.o writefile.o

safecat.0: \
safecat.1
	nroff -man safecat.1 > safecat.0

safecat.o: \
compile safecat.c uint32.h version.h sig.h tempfile.h stat_dir.h \
writefile.h
	./compile safecat.c

sig.o: \
compile sig.c hassgact.h
	./compile sig.c

setup: \
it install
	./install

stat_dir.o: \
compile stat_dir.c
	./compile stat_dir.c

str.a: \
makelib str_len.o byte_chr.o byte_diff.o byte_copy.o byte_cr.o \
byte_zero.o
	./makelib str.a str_len.o byte_chr.o byte_diff.o \
	byte_copy.o byte_cr.o byte_zero.o

str_diffn.o: \
compile str_diffn.c str.h
	./compile str_diffn.c

str_len.o: \
compile str_len.c str.h
	./compile str_len.c

stralloc.a: \
makelib stralloc_eady.o stralloc_pend.o stralloc_copy.o \
stralloc_opys.o stralloc_opyb.o stralloc_cat.o stralloc_cats.o \
stralloc_catb.o stralloc_arts.o stralloc_num.o
	./makelib stralloc.a stralloc_eady.o stralloc_pend.o \
	stralloc_copy.o stralloc_opys.o stralloc_opyb.o \
	stralloc_cat.o stralloc_cats.o stralloc_catb.o \
	stralloc_arts.o stralloc_num.o

stralloc_arts.o: \
compile stralloc_arts.c byte.h str.h stralloc.h gen_alloc.h
	./compile stralloc_arts.c

stralloc_cat.o: \
compile stralloc_cat.c byte.h stralloc.h gen_alloc.h
	./compile stralloc_cat.c

stralloc_catb.o: \
compile stralloc_catb.c stralloc.h gen_alloc.h byte.h
	./compile stralloc_catb.c

stralloc_cats.o: \
compile stralloc_cats.c byte.h str.h stralloc.h gen_alloc.h
	./compile stralloc_cats.c

stralloc_copy.o: \
compile stralloc_copy.c byte.h stralloc.h gen_alloc.h
	./compile stralloc_copy.c

stralloc_eady.o: \
compile stralloc_eady.c alloc.h stralloc.h gen_alloc.h \
gen_allocdefs.h
	./compile stralloc_eady.c

stralloc_num.o: \
compile stralloc_num.c stralloc.h gen_alloc.h
	./compile stralloc_num.c

stralloc_opyb.o: \
compile stralloc_opyb.c stralloc.h gen_alloc.h byte.h
	./compile stralloc_opyb.c

stralloc_opys.o: \
compile stralloc_opys.c byte.h str.h stralloc.h gen_alloc.h
	./compile stralloc_opys.c

stralloc_pend.o: \
compile stralloc_pend.c alloc.h stralloc.h gen_alloc.h \
gen_allocdefs.h
	./compile stralloc_pend.c

strerr.a: \
makelib strerr_sys.o strerr_die.o
	./makelib strerr.a strerr_sys.o strerr_die.o

strerr_die.o: \
compile strerr_die.c substdio.h subfd.h substdio.h exit.h strerr.h
	./compile strerr_die.c

strerr_sys.o: \
compile strerr_sys.c error.h strerr.h
	./compile strerr_sys.c

subfderr.o: \
compile subfderr.c readwrite.h substdio.h subfd.h substdio.h
	./compile subfderr.c

subfdin.o: \
compile subfdin.c readwrite.h substdio.h subfd.h substdio.h
	./compile subfdin.c

subfdins.o: \
compile subfdins.c readwrite.h substdio.h subfd.h substdio.h
	./compile subfdins.c

subfdout.o: \
compile subfdout.c readwrite.h substdio.h subfd.h substdio.h
	./compile subfdout.c

subfdouts.o: \
compile subfdouts.c readwrite.h substdio.h subfd.h substdio.h
	./compile subfdouts.c

substdi.o: \
compile substdi.c substdio.h byte.h error.h
	./compile substdi.c

substdio.a: \
makelib substdio.o substdi.o substdo.o subfderr.o subfdout.o \
subfdouts.o subfdin.o subfdins.o substdio_copy.o
	./makelib substdio.a substdio.o substdi.o substdo.o \
	subfderr.o subfdout.o subfdouts.o subfdin.o subfdins.o \
	substdio_copy.o

substdio.o: \
compile substdio.c substdio.h
	./compile substdio.c

substdio_copy.o: \
compile substdio_copy.c substdio.h
	./compile substdio_copy.c

substdo.o: \
compile substdo.c substdio.h str.h byte.h error.h
	./compile substdo.c

systype: \
find-systype trycpp.c
	./find-systype > systype

taia_fmtfrac.o: \
compile taia_fmtfrac.c taia.h tai.h uint64.h
	./compile taia_fmtfrac.c

taia_now.o: \
compile taia_now.c taia.h tai.h uint64.h
	./compile taia_now.c

taia_tai.o: \
compile taia_tai.c taia.h tai.h uint64.h
	./compile taia_tai.c

tempfile.o: \
compile tempfile.c
	./compile tempfile.c

uint32.h: \
tryulong32.c compile load uint32.h1 uint32.h2
	( ( ./compile tryulong32.c && ./load tryulong32 && \
	./tryulong32 ) >/dev/null 2>&1 \
	&& cat uint32.h2 || cat uint32.h1 ) > uint32.h
	rm -f tryulong32.o tryulong32

uint64.h: \
tryulong64.c compile load uint64.h1 uint64.h2
	( ( ./compile tryulong64.c && ./load tryulong64 && \
	./tryulong64 ) >/dev/null 2>&1 \
	&& cat uint64.h2 || cat uint64.h1 ) > uint64.h
	rm -f tryulong64.o tryulong64

version.h: \
conf-version
	@echo 'static const char *const version_string="$$Version:' \
	`head -1 conf-version` 'built' `date +"%b %d, %Y"` at \
	`date +"%H:%M"`'$$";' > version.h

writefile.o: \
compile writefile.c
	./compile writefile.c
