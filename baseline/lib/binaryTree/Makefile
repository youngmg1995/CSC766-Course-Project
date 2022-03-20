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

# core directories
CORE_SRC_DIR		:= $(SRC_DIR)/core
CORE_INC_DIR		:= $(INC_DIR)/core
CORE_OBJ_DIR		:= $(OBJ_DIR)/core

# unit tests directories
TEST_SRC_DIR		:= $(SRC_DIR)/test
TEST_INC_DIR		:= $(INC_DIR)/test
TEST_OBJ_DIR		:= $(OBJ_DIR)/test



################################################################################
############################ COMPILATION PARAMETERS ############################
################################################################################
# compliler
CC			:= gcc

# include directories
CORE_INC	:= -I$(CORE_INC_DIR)
TEST_INC	:= -I$(CORE_INC_DIR) -I$(TEST_INC_DIR)

# flags
# CFLAGS   =  -O3 -Wall -m64 -fopenmp -g
CFLAGS		:= -O3 -Wall
LFLAGS		:= -lm 



################################################################################
############################ COMPILATION VARIABLES #############################
################################################################################
CORE_SRC_FILES			:= $(wildcard $(CORE_SRC_DIR)/*.c)
CORE_OBJ_FILES			:= $(patsubst $(CORE_SRC_DIR)/%.c,$(CORE_OBJ_DIR)/%.o,$(CORE_SRC_FILES))
CORE_INC_FILES			:= $(wildcard $(CORE_INC_DIR)/*.h)

TEST_SRC_FILES			:= $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJ_FILES			:= $(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC_FILES))
TEST_INC_FILES			:= $(wildcard $(TEST_INC_DIR)/*.h)

ALL_SRC_FILES			:= $(CORE_SRC_FILES) $(TEST_SRC_FILES)
ALL_OBJ_FILES			:= $(CORE_OBJ_FILES) $(TEST_OBJ_FILES)
ALL_INC_FILES			:= $(CORE_INC_FILES) $(TEST_INC_FILES)



################################################################################
##################################### CORE #####################################
################################################################################
.PHONY: build
build: build-core

.PHONY: build-all
build-all: build-core build-test

.PHONY: core-directories
core-directories :
	@mkdir -p $(CORE_OBJ_DIR)

.PHONY: build-core
build-core : core-directories $(CORE_OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-core: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

$(CORE_OBJ_DIR)/%.o : $(CORE_SRC_DIR)/%.c $(CORE_INC_FILES)
	$(CC) $(CFLAGS) $(CORE_INC) -c -o $@ $<


################################################################################
##################################### TEST #####################################
################################################################################
.PHONY: test
test: build-test
	$(BIN_DIR)/$(TEST)

.PHONY: test-directories
test-directories :
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(TEST_OBJ_DIR)

.PHONY: build-test
build-test : build-core test-directories $(BIN_DIR)/$(TEST)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-test: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

$(BIN_DIR)/$(TEST) :  $(TEST_OBJ_FILES) $(CORE_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS)

$(TEST_OBJ_DIR)/%.o : $(TEST_SRC_DIR)/%.c $(TEST_INC_FILES)
	$(CC) $(CFLAGS) $(TEST_INC) -c -o $@ $<



################################################################################
#################################### CLEAN #####################################
################################################################################

.PHONY: clean
clean: clean-all

.PHONY: clean-all
clean-all:
	@rm -fr $(OBJ_DIR)
	@rm -fr $(BIN_DIR)


.PHONY: clean-core
clean-core:
	@rm -fr $(CORE_OBJ_DIR)

.PHONY: clean-test
clean-test:
	@rm -fr $(TEST_OBJ_DIR)
	@rm -fr $(BIN_DIR)/$(TEST).exe



################################################################################
##################################### ALL ######################################
################################################################################

.PHONY: all
all: build-all



################################################################################
################################# END OF FILE ##################################
################################################################################