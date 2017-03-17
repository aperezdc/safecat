Summary: Secure spooling of emails to a qmail maildir
Name: safecat
Version: 1.13
Release: v1
License: BSD
Group: Applications/File
Source: http://www.pobox.com/~lbudney/linux/software/safecat/safecat-%{version}.tar.gz
Patch0: safecat-buildroot.patch
URL: http://www.pobox.com/~lbudney/linux/software/safecat.html
Packager: Vadim Druzhin <vdruzhin@mail.ru>
BuildRoot: /var/tmp/%{name}-%{version}-%{release}

%description 
safecat implements Dan Bernstein's maildir algorithm, copying standard
input safely to a specified directory. With safecat, the user is
offered two assurances. First, if safecat returns successfully, then
all data is guaranteed to be saved in the destination directory.
Second, if a file exists in the destination directory, placed there by
safecat, then the file is guaranteed to be complete.

To use safecat, you specify a destination directory, but not a file
name. Safecat picks the filename uniquely every time. That way many
safecat processes (and other programs) can write to the directory
simultaneously. If you want a particular filename, then you just
rename the file after safecat completes. In general you should use a
single, separate process to do things like renaming, collecting, and
deleting files. You can run the process as a daemon, a cron jobs, or
from a mail reader.


%prep
%setup

# BUILD_ROOT patch
%patch0

echo "/usr" > conf-root

%build
make

%install

if [ x"$RPM_BUILD_ROOT" != x"/" -a -d "$RPM_BUILD_ROOT" ]
  then
  rm -rf "$RPM_BUILD_ROOT"
  fi

mkdir -p "$RPM_BUILD_ROOT"
make setup check

%clean

if [ x"$RPM_BUILD_ROOT" != x"/" -a -d "$RPM_BUILD_ROOT" ]
  then
  rm -rf "$RPM_BUILD_ROOT"
  fi

%files
%defattr(-,root,root)
%doc CHANGES README INSTALL COPYING
/usr/bin/safecat
/usr/bin/maildir
/usr/man/man1/safecat.1.gz
/usr/man/man1/maildir.1.gz
/usr/man/cat1/safecat.0
/usr/man/cat1/maildir.0
