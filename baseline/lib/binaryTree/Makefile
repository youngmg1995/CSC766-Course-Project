################################################################################
############################# GENERAL DIRECTORIES ##############################
################################################################################
# globals binary /bin
# APP                 := run-binaryTree
TEST				:= test-binaryTree

# dirs Root app
ROOT_DIR			:= .

# dir root/managed_folders
SRC_DIR           	:= $(ROOT_DIR)/src
INC_DIR			  	:= $(ROOT_DIR)/include
OBJ_DIR				:= $(ROOT_DIR)/obj
BIN_DIR			  	:= $(ROOT_DIR)/bin

# unit test directories
TEST_SRC_DIR		:= .
TEST_OBJ_DIR		:= $(OBJ_DIR)/test



################################################################################
############################ COMPILATION PARAMETERS ############################
################################################################################
# compliler
CC			:= gcc

# flags
# CFLAGS   =  -O3 -Wall -m64 -fopenmp -g
INC_FLAG	:= -I$(INC_DIR)
CFLAGS		:= -O3 -Wall $(INC_FLAG)
LFLAGS		:= -lm 



################################################################################
############################ COMPILATION VARIABLES #############################
################################################################################
SRC_FILES				:= $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES				:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INC_FILES				:= $(wildcard $(INC_DIR)/*.h)
ALL_HEADER_FILES		:= $(INC_FILES_ALGO)

TEST_SRC_FILES			:= $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJ_FILES			:= $(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC_FILES))



################################################################################
################################### BUILDING ###################################
################################################################################
.PHONY: build
build: build-binaryTree

.PHONY: build-directories
build-directories :
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

.PHONY: build-binaryTree
build-binaryTree : build-directories $(OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-binaryTree: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: test-directories
test-directories :
	@mkdir -p $(TEST_OBJ_DIR)

.PHONY: build-test
build-test : build-binaryTree test-directories $(BIN_DIR)/$(TEST)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> test-binaryTree: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

$(BIN_DIR)/$(TEST) :  $(TEST_OBJ_FILES) $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS)

$(TEST_OBJ_DIR)/%.o : $(TEST_SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c -o $@ $<


################################################################################
################################### TESTING ####################################
################################################################################
.PHONY: test
test: test-binaryTree

.PHONY: test-binaryTree
test-binaryTree : build-test
	$(BIN_DIR)/$(TEST)


################################################################################
################################### CLEANING ###################################
################################################################################

.PHONY: clean
clean: clean-all

.PHONY: clean-all
clean-all: clean-build clean-test

.PHONY: clean-build
clean-build:
	@rm -fr $(OBJ_DIR)
	@rm -fr $(BIN_DIR)

.PHONY: clean-test
clean-test:
	@rm -fr $(TEST_OBJ_DIR)
	@rm -fr $(BIN_DIR)/$(TEST)



################################################################################
##################################### ALL ######################################
################################################################################

.PHONY: all
all: build-all



################################################################################
################################# END OF FILE ##################################
################################################################################