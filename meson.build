project('safecat', 'c', version: '1.13', license: 'BSD')

cc = meson.get_compiler('c')
if cc.has_argument('-Wno-misleading-indentation')
  add_project_arguments('-Wno-misleading-indentation', language: 'c')
endif

config = configuration_data()
config.set('VERSION', meson.project_version())
config.set('SIZEOF_LONG_LONG', cc.sizeof('long long'))
config.set('SIZEOF_LONG', cc.sizeof('long'))
config.set10('HAVE_ERRNO_H', cc.has_header('errno.h'))
config.set10('HAVE_STDINT_H', cc.has_header('stdint.h'))
config.set10('HAVE_SIGACTION', cc.has_function('sigaction'))

configure_file(configuration: config,
	input: 'version.h.in', output: 'version.h')
configure_file(configuration: config,
	input: 'error_no.h.in', output: 'error_no.h')
configure_file(configuration: config,
	input: 'uint64.h.in', output: 'uint64.h')
configure_file(configuration: config,
	input: 'hassgact.h.in', output: 'hassgact.h')

executable('safecat',
	'alloc.c',
	'alloc_re.c',
	'byte_copy.c',
	'byte_cr.c',
	'envread.c',
	'error.c',
	'error_str.c',
	'fmt_uint64.c',
	'hostname.c',
	'safecat.c',
	'sig.c',
	'stat_dir.c',
	'str_diffn.c',
	'str_len.c',
	'stralloc_cat.c',
	'stralloc_catb.c',
	'stralloc_cats.c',
	'stralloc_eady.c',
	'stralloc_opyb.c',
	'stralloc_opys.c',
	'stralloc_pend.c',
	'strerr_die.c',
	'strerr_sys.c',
	'subfderr.c',
	'subfdouts.c',
	'substdi.c',
	'substdio.c',
	'substdo.c',
	'substdio_copy.c',
	'taia_fmtfrac.c',
	'taia_now.c',
	'taia_tai.c',
	'tempfile.c',
	'writefile.c',
	install: true)

install_man('safecat.1')