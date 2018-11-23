#!/usr/bin/env sh

RootPath="$(
	cd "$(dirname "$0")"
	pwd -P
)/..";
cd $RootPath

buildType=""
read buildType

echo "Build $buildType..."

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
  echo "usage: $0 [--nodocker {...}]"
  echo " --nodocker: don't use docker (Windows)"
  echo " ...: cmake -build config=$buildType __VA_ARGS__"
  exit 0
elif [ "$1" = "--nodocker" ]; then
  ./.buildTools/_start_compile.sh $buildType ${@:2}
else
  docker run \
	-v $(pwd):/repo \
	-v $(pwd)/.cache:/root/.conan \
	-t \
		epitechcontent/epitest-docker \
			/bin/bash -c "/repo/.buildTools/_start_compile.sh $buildType $@"
fi