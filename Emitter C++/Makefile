CC = g++
CFLAGS = -Wall -mfpu=neon -marm
EXEC_NAME = emitter_image cam listen control_PA
INCLUDE =
OPENCV=`pkg-config opencv --cflags --libs`
LIBS = -lwiringPi
OBJ_FILES = EncoderDiff.o Filter.o Insertion_preambule.o QPSK_mod.o Recording_sequence.o UpSampling.o emitter_image.o BitGenerator.o 


all : $(EXEC_NAME)

clean :
	rm -rf bin/*  *.o
	
cam: cam.o
	$(CC) -o cam cam.o $(OPENCV)
	mv cam ./bin/

listen: listen.o
	$(CC) -o listen listen.o 
	mv listen ./bin/
	
control_PA: control_PA.o
	$(CC) -o control_PA control_PA.o $(LIBS)
	mv control_PA ./bin/
		
emitter_image: $(OBJ_FILES)
	$(CC) -o emitter_image $(OBJ_FILES) $(OPENCV)
	mv emitter_image ./bin/

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

