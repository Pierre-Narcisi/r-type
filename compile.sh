docker run \
	-v $(pwd):/repo \
	-v $(pwd)/.cache:/root/.conan \
	-it \
		epitechcontent/epitest-docker \
			/bin/bash -c "/repo/_compile.sh"