CC		= g++
MAIN	= src/main/main.cc

CLASSES_FOLDER	= src/classes
MAIN_FOLDER	= src/main
BIN_FOLDER = bin

SOURCES = \
		ItemPrediction.o\
		Predictors.o\
		Helpers.o\
		TopMatches.o\
		Rating.o\
		RatingList.o\
		UserItemMatrix.o\
		Similarity.o\
		Algorithms.o\

LDFLAGS	= -c
CFLAGS	= -Wall -std=c++14 -g -Wdelete-non-virtual-dtor -Wno-unknown-pragmas
PROGRAM	= recommender
OBJECTS	= (SOURCES: .cc = .o)

INPUT	= ratings.csv
TARGET	= targets.csv
OUTPUT	= submission.csv

all : $(PROGRAM)

ItemPrediction.o : $(CLASSES_FOLDER)/ItemPrediction/ItemPrediction.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/ItemPrediction/ItemPrediction.cc

Predictors.o : $(CLASSES_FOLDER)/Predictors/Predictors.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/Predictors/Predictors.cc

TopMatches.o : $(CLASSES_FOLDER)/TopMatches/TopMatches.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/TopMatches/TopMatches.cc

Algorithms.o : $(CLASSES_FOLDER)/Algorithms/Algorithms.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/Algorithms/Algorithms.cc

Similarity.o : Algorithms.o $(CLASSES_FOLDER)/Similarity/Similarity.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/Similarity/Similarity.cc

UserItemMatrix.o : $(CLASSES_FOLDER)/UserItemMatrix/UserItemMatrix.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/UserItemMatrix/UserItemMatrix.cc

RatingList.o : $(CLASSES_FOLDER)/RatingList/RatingList.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/RatingList/RatingList.cc

Helpers.o : ItemPrediction.o $(CLASSES_FOLDER)/Helpers/Helpers.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/Helpers/Helpers.cc

Rating.o : $(CLASSES_FOLDER)/Rating/Rating.cc
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLASSES_FOLDER)/Rating/Rating.cc

recommender: Helpers.o ItemPrediction.o Predictors.o TopMatches.o Similarity.o Algorithms.o UserItemMatrix.o RatingList.o Rating.o $(MAIN) 
	$(CC) $(CFLAGS) $(SOURCES) $(MAIN) -o $(BIN_FOLDER)/$(PROGRAM)
	rm ./*.o
	cp bin/$(PROGRAM) .

clean:
	rm *.o bin/$(PROGRAM)

run2:
	bin/$(PROGRAM) data/$(INPUT) data/$(TARGET) > data/$(OUTPUT)

run:
	./$(PROGRAM) $(INPUT) $(TARGET) > $(OUTPUT)

make:
	$(CC) $(CFLAGS)\
		src/classes/ItemPrediction/ItemPrediction.cc\
		src/classes/Predictors/Predictors.cc\
		src/classes/Rating/Rating.cc\
		src/classes/Helpers/Helpers.cc\
		src/classes/RatingList/RatingList.cc\
		src/classes/UserItemMatrix/UserItemMatrix.cc\
		src/classes/TopMatches/TopMatches.cc\
		src/classes/Algorithms/Algorithms.cc\
		src/classes/Similarity/Similarity.cc\
		src/main/main.cc\
		-o bin/$(PROGRAM)
		cp bin/$(PROGRAM) .
