#!/usr/bin/env sh

BuildDir="build-$(uname)"

if [ "$1" = "--get-build-directory" ]; then
	echo $BuildDir
	exit 0
fi

if [ ! -d $BuildDir ]; then
	mkdir $BuildDir
fi
(
	cd $BuildDir
	conan remote add bincrafter https://api.bintray.com/conan/bincrafters/public-conan

	conan install .. --build=missing --profile ../conanPlatformSettings/linux.txt
	if [ ! -z $1 ]; then
		cmake .. -DCMAKE_BUILD_TYPE=$@
		cmake --build . --config $@
	else
		cmake .. -DCMAKE_BUILD_TYPE=Debug
		cmake --build . --config Debug
	fi
) && echo "OK" || echo "KO";