#!/usr/bin/env sh

RootPath="$(
	cd "$(dirname "$0")"
	pwd -P
)/.";
cd $RootPath

BuildDir="build-$(uname)"

if [ "$1" = "--get-build-directory" ]; then
	echo $BuildDir
	exit 0
fi

if [ "$(uname)" = "Linux" ]; then
	ConanConfigFile="linux.txt";
	CMakeType="Unix Makefiles"
else
	ConanConfigFile="windows.txt";
	CMakeType="Visual Studio 15 Win64"
fi

if [ ! -d $BuildDir ]; then
	mkdir $BuildDir
fi
(
	cd $BuildDir
	conan remote add bincrafter https://api.bintray.com/conan/bincrafters/public-conan

	conan install .. --build=missing --profile ../ConanPlatformSettings/$ConanConfigFile
	if [ ! -z $1 ]; then
		cmake .. -G "$CMakeType" -DCMAKE_BUILD_TYPE=$@
		cmake --build . --config $@
	else
		cmake .. -G "$CMakeType" -DCMAKE_BUILD_TYPE=Debug
		cmake --build . --config Debug
	fi
) && echo "OK" || echo "KO";