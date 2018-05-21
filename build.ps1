docker run -e "FLOAT_ONLY=1" -e "IMAGE_NAME=image" --rm -it -v "E:/OwnCloud/Dropbox/Projekte, Events/2018 NodeMCU/nodemcu-firmware:/opt/nodemcu-firmware:rw" marcelstoer/nodemcu-build

docker run -e "FLOAT_ONLY=1" -e "IMAGE_NAME=image" --rm -it -v "E:/OwnCloud/Dropbox/Projekte, Events/2018 NodeMCU/nodemcu-firmware/:/opt/nodemcu-firmware" alpine ls /opt/nodemcu-firmware

docker run -e "FLOAT_ONLY=1" -e "IMAGE_NAME=image" --rm -it -v "E:/OwnCloud/Dropbox/Projekte, Events/2018 NodeMCU/nodemcu-firmware/:/opt/nodemcu-firmware" marcelstoer/nodemcu-build