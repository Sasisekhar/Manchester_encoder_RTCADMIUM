setup:
	. ${IDF_PATH}/export.sh
	idf.py set-target esp32s3


embedded:
	idf.py build
	idf.py flash
	idf.py monitor

clean:
	idf.py clean