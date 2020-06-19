# Commands
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -DNDEBUG -MMD
RM = rm -f
MKDIR = mkdir -p

# Source locations
SRC_DIR = ./src

# Output files
BIN_DIR = ./bin
OUTPUT = straights

OBJ_FILES = ${addsuffix .o, ${basename ${notdir ${wildcard ${SRC_DIR}/*.cpp}}}}
OBJ = ${addprefix ${BIN_DIR}/, ${OBJ_FILES}}

DEPENDS = ${OBJ:.o=.d}

.PHONY: all bin clean

all: straights

${BIN_DIR}/%.o: ${SRC_DIR}/%.cpp
	@echo "building $@ from $^..."
	@${CXX} ${CXXFLAGS} -c $< -o $@

straights: bin ${OBJ}
	@echo "linking straights..."
	@${CXX} ${CCXFLAGS} ${OBJ} -o ${OUTPUT}

-include ${DEPENDS}

bin:
ifeq (,${wildcard ${BIN_DIR}})
	@echo "creating binary directory..."
	@${MKDIR} ${BIN_DIR}
endif

clean:
	@echo "cleaning project..."
ifneq (,${wildcard ${BIN_DIR}})
	@${RM} ${BIN_DIR}/*
endif
	@${RM} ${OUTPUT}
