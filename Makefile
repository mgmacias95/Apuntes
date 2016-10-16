all: fbd ed ac ies fr

ies: 
	make -C ./IES/parcial1
	make -C ./IES/parcial2

fbd:
	make -C ./FBD

ed:
	make -C ./ED

ac:
	make -C ./AC

fr:
	make -C ./FR

ise:
	make -C ./ISE

clean:
	make clean -C ./FBD
	make clean -C ./ED 
	make clean -C ./AC 
	make clean -C ./IES/parcial1
	make clean -C ./IES/parcial2
	make clean -C ./FR
