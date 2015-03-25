#!/bin/bash
rpm -ivh http://pkgs.repoforge.org/rpmforge-release/rpmforge-release-0.5.3-1.el6.rf.x86_64.rpm

yum install git gcc-c++ autoconf automake libtool wget python ncurses-devel zlib-devel libjpeg-devel openssl-devel e2fsprogs-devel sqlite-devel libcurl-devel pcre-devel speex-devel ldns-devel libedit-devel

git clone https://freeswitch.org/stash/scm/fs/freeswitch.git

./bootstrap.sh -j
./configure -C
make -j 8 && make install
make cd-sounds-install
make cd-moh-install

cp add_user.sh remove_user.sh /usr/local/freeswitch/conf/directory/default

chmod +x add_user.sh remove_user.sh

add_user.sh 10000 10999

/usr/local/freeswitch/bin/freeswitch
