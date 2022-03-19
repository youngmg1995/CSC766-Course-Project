################################################################################
############################# GENERAL DIRECTORIES ##############################
################################################################################
# globals binary /bin
# APP                 = run-binaryTree
TEST				= test-binaryTree

# dirs Root app
ROOT_DIR             = .

# dir root/managed_folders
SRC_DIR           	= src
INC_DIR			  	= include
OBJ_DIR				= obj
BIN_DIR			  	= bin



################################################################################
############################ COMPILATION PARAMETERS ############################
################################################################################
# compliler
CC		    = gcc

# flags
# CFLAGS   =  -O3 -Wall -m64 -fopenmp -g
INC_FLAG     = -I$(ROOT_DIR)/$(INC_DIR)
CFLAGS   =  -O3 -Wall $(INC_FLAG)
LFLAGS 	 = -lm 



################################################################################
############################ COMPILATION VARIABLES #############################
################################################################################
SRC_FILE				= $(wildcard $(ROOT_DIR)/$(SRC_DIR)/*.c)
OBJ_FILES				= $(patsubst $(ROOT_DIR)/$(SRC_DIR)/%.c,$(ROOT_DIR)/$(OBJ_DIR)/%.o,$(SRC_FILE))
INC_FILES				= $(wildcard $(ROOT_DIR)/$(INC_DIR)/*.h)
ALL_HEADER_FILES		= $(INC_FILES_ALGO)



################################################################################
############################# COMPILATION VARIABLES ############################
################################################################################

.PHONY: all
all: test

.PHONY: directories
directories :
	@mkdir -p $(ROOT_DIR)/$(BIN_DIR)
	@mkdir -p $(ROOT_DIR)/$(OBJ_DIR)


.PHONY: test
test : directories $(ROOT_DIR)/$(BIN_DIR)/$(TEST)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> binaryTree: ./$(word 2,$^)"
	@echo " ****************************************************************************** "


$(ROOT_DIR)/$(BIN_DIR)/$(TEST) :  $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS)

$(ROOT_DIR)/$(OBJ_DIR)/%.o : $(ROOT_DIR)/$(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c -o $@ $<



################################################################################
############################### Top Level Rules ################################
################################################################################

.PHONY: test
run: test-binaryTree

.PHONY: clean
clean: clean-all

.PHONY: clean-all
clean-all:
	@rm -fr $(ROOT_DIR)/$(OBJ_DIR)
	@rm -fr $(ROOT_DIR)/$(BIN_DIR)

.PHONY: run-test
run-test: test
	./$(ROOT_DIR)/$(BIN_DIR)/$(TEST)
#	./$(ROOT_DIR)/$(BIN_DIR)/$(APP) -f $(FILE_BIN) $(ARGS)
