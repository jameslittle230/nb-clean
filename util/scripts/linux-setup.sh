#!/bin/bash

if [ $# -gt 0 ]; then
	echo "too many arguments!"
	exit 1
fi

# OLDPACKAGES="libboost1.48-dev libboost-python1.48-dev"

PACKAGES="build-essential cmake git-core cmake-curses-gui"

BITS=$(uname -m)

if [ "$BITS" == 'x86_64' ]; then
    echo ""
    echo "64 bit Linux is NOT SUPPORTED!"
    echo "The Northern Bites code base depends on too many 32-bit libraries."
    echo "Please switch to 32-bit or set up your system manually."
    echo "Exiting."
    exit 1
fi

echo ""
echo "Downloading and installing software"

sudo apt-get -y install $PACKAGES

naoqi_version=2.1.0.19
curl_address="https://files.jameslittle.me/robocup/$naoqi_version/"
nbites_dir=$PWD/../..
lib_dir=$nbites_dir/lib
version_dir=$lib_dir/$naoqi_version

naoqi=naoqi-sdk-$naoqi_version-linux32.tar.gz
atom=nbites-atom-toolchain-$naoqi_version.tar.gz

naoqi_local=$version_dir/naoqi-sdk-$naoqi_version-linux32
atom_local=$version_dir/atomtoolchain

echo ""
echo "Downloading NaoQi & Atom toolchain"

mkdir -p "$version_dir"
curl $curl_address$naoqi -o "$version_dir/$naoqi"
curl $curl_address$atom -o "$version_dir/$atom"

echo "Unpacking NaoQi"

cd "$lib_dir" || exit
tar -xzf "$version_dir/$naoqi" -C .

mkdir atomtoolchain
tar -xzf "$version_dir/$atom" -C atomtoolchain --strip-components 1

rm -r $naoqi_version

cd "$nbites_dir" || return

echo ""
echo "Configuring bash."

nbites_bash=$nbites_dir/util/scripts/nbites.bash
touch nbites_bash

echo "export NBITES_DIR=$nbites_dir" >> "$nbites_bash"
echo "export AL_DIR=$naoqi_local" >> "$nbites_bash"
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$nbites_dir/ext/lib" >> "$nbites_bash"
echo "export PATH=$nbites_dir/ext/bin:$PATH" >> "$nbites_bash"

{ echo ""; echo "#added by linux-setup.sh for RoboCup purposes"; }  >> ~/.bashrc
echo "source $nbites_bash" >> ~/.bashrc
source ~/.bashrc
echo ""

echo ""
echo "One last IMPORTANT step: Restart your terminal. Then you're good to go!"
