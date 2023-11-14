setup:
	. ${IDF_PATH}/export.sh
	idf.py set-target esp32s3


embedded:
	idf.py build
	idf.py flash -p /dev/ttyACM0
	idf.py monitor -p /dev/ttyACM0

clean:
	idf.py clean