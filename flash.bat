REM run in anaconda shell
esptool --port COM3 write_flash -fm dio 0x00000 .\bin\nodemcu_float_image.bin
