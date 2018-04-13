CC		= g++
MAIN	= src/main/main.cc

CLASSES_FOLDER	= src/classes
MAIN_FOLDER	= src/main

SOURCES = $(CLASSES_FOLDER)/Rating/Rating.cc\
		$(CLASSES_FOLDER)/RatingList/RatingList.cc\
		$(CLASSES_FOLDER)/UserItemMatrix/UserItemMatrix.cc\
		$(CLASSES_FOLDER)/TopMatches/TopMatches.cc\
		$(CLASSES_FOLDER)/Similarity/Similarity.cc\
		$(CLASSES_FOLDER)/Algorithms/Algorithms.cc
		#$(CLASSES_FOLDER)/ItemPrediction/ItemPrediction.cc\

LDFLAGS	= -c
CFLAGS	= -Wall -std=c++14 -g -Wdelete-non-virtual-dtor -Wno-unknown-pragmas
PROGRAM	= recommender
OBJECTS	= (SOURCES: .cc = .o)

INPUT	= data/ratings.csv
TARGET	= data/targets.csv
OUTPUT	= data/submission.csv

all : $(PROGRAM)

ItemPrediction.o : $(CLASSES_FOLDER)/ItemPrediction/ItemPrediction.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/ItemPrediction/ItemPrediction.cc

TopMatches.o : $(CLASSES_FOLDER)/TopMatches/TopMatches.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/TopMatches/TopMatches.cc

Algorithms.o : $(CLASSES_FOLDER)/Algorithms/Algorithms.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/Algorithms/Algorithms.cc

UserItemMatrix.o : $(CLASSES_FOLDER)/UserItemMatrix/UserItemMatrix.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/UserItemMatrix/UserItemMatrix.cc

RatingList.o : $(CLASSES_FOLDER)/RatingList/RatingList.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/RatingList/RatingList.cc

Rating.o : $(CLASSES_FOLDER)/Rating/Rating.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/Rating/Rating.cc


recommender: ItemPrediction.o TopMatches.o Algorithms.o UserItemMatrix.o RatingList.o Rating.o $(MAIN) 
	$(CC) $(CFLAGS) $(SOURCES) $(MAIN) -o bin/$(PROGRAM)

clean:
	rm *.o $(PROGRAM)

run:
	bin/$(PROGRAM) $(INPUT) $(TARGET) > $(OUTPUT)