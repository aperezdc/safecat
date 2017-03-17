# 
# Example spec file for cdplayer app... 
# 
Summary: Secure File Wiping and Deletion
Name: safecat
Version: 1.9
Release: 1
Copyright: BSD
Group: Applications/File
Source: http://www.pobox.com/~lbudney/linux/software/safecat/safecat-%{version}.tar.gz
URL: http://www.pobox.com/~lbudney/linux/software/safecat.html
Distribution: RedHat 7.2 Contrib
Packager: Len Budney <lbudney@pobox.com>
#Buildroot: /tmp/safecat-%{version}

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
echo /usr > conf-root
#mkdir -p %{buildroot}

%build
make

%install
make setup check

%clean
#rm -rf $RPM_BUILD_ROOT

%files
%attr(-,root,root) %doc CHANGES README INSTALL COPYING
%attr(-,root,root) /usr/bin/safecat
%attr(-,root,root) /usr/bin/maildir
%attr(-,root,root) /usr/man/man1/safecat.1
%attr(-,root,root) /usr/man/man1/maildir.1
%attr(-,root,root) /usr/man/cat1/safecat.0
%attr(-,root,root) /usr/man/cat1/maildir.0
