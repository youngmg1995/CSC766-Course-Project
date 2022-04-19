################################################################################
############################# GENERAL DIRECTORIES ##############################
################################################################################

# ---------------------------------------------------------------------------- #

# top level directories
ROOT_DIR			:= .

SRC_DIR           	:= $(ROOT_DIR)/src
INC_DIR			  	:= $(ROOT_DIR)/include
OBJ_DIR				:= $(ROOT_DIR)/obj
BIN_DIR			  	:= $(ROOT_DIR)/bin

# ---------------------------------------------------------------------------- #

# directories for sperating object files created by different compilers
GCC_DIR				:= g++
EMCC_DIR			:= em++

# ---------------------------------------------------------------------------- #

# subdirectories for seperating core, test, and experiment files
CORE_DIR			:= core
TEST_DIR			:= test
EXP_DIR				:= exp

# ---------------------------------------------------------------------------- #

# executables /bin
NATIVE_C_BIN		:= $(BIN_DIR)/native-c
NATIVE_C_TEST		:= $(NATIVE_C_BIN)/test
NATIVE_C_EXP		:= $(NATIVE_C_BIN)/exp

NATIVE_JS_BIN		:= $(BIN_DIR)/native-js
NATIVE_JS_TEST		:= $(NATIVE_JS_BIN)/test.js
NATIVE_JS_EXP		:= $(NATIVE_JS_BIN)/exp.js

NATIVE_WASM_BIN		:= $(BIN_DIR)/native-wasm
NATIVE_WASM_TEST	:= $(NATIVE_WASM_BIN)/test.js
NATIVE_WASM_EXP		:= $(NATIVE_WASM_BIN)/exp.js

WEB_JS_BIN			:= $(BIN_DIR)/web-js
WEB_JS_TEST			:= $(WEB_JS_BIN)/test.html
WEB_JS_EXP			:= $(WEB_JS_BIN)/exp.html

WEB_WASM_BIN		:= $(BIN_DIR)/web-wasm
WEB_WASM_TEST		:= $(WEB_WASM_BIN)/test.html
WEB_WASM_EXP		:= $(WEB_WASM_BIN)/exp.html

# ---------------------------------------------------------------------------- #

################################################################################
############################ COMPILATION PARAMETERS ############################
################################################################################

# ------------------------------------------------------------------------------
# compliler
CC				:= g++
EMCC			:= em++

# ------------------------------------------------------------------------------

# include directories
LIB_INC			:= `pkg-config nlohmann_json --cflags`
CORE_INC		:= -I$(INC_DIR)/$(CORE_DIR) $(LIB_INC)
TEST_INC		:= -I$(INC_DIR)/$(TEST_DIR) $(CORE_INC)
EXP_INC			:= -I$(INC_DIR)/$(EXP_DIR) $(CORE_INC)

# ------------------------------------------------------------------------------

# flags
GCC_CFLAGS		:= -O3 -Wall -Werror -std=c++20 -pthread
GCC_LFLAGS		:= -O3 -lm -std=c++20 -pthread -lpthread

EMCC_CFLAGS		:= -O3 -Wall -std=c++20 -pthread
EMCC_LFLAGS 	:= -O3 -lm -std=c++20 -pthread -lpthread -s ASSERTIONS=1 -s PROXY_TO_PTHREAD -s PTHREAD_POOL_SIZE=17 -s INITIAL_MEMORY=4294901760 --preload-file .data/
NO_WASM_LFLAG 	:= -s WASM=0

# EMCC_CFLAGS		:= -O3 -Wall  -pthread -s PROXY_TO_PTHREAD -s PTHREAD_POOL_SIZE=8
# # EMCC_LFLAGS 	:= -lm -pthread -lpthread -s ASSERTIONS=1 -s INITIAL_MEMORY=134217728 -s PTHREAD_POOL_SIZE=8 #-s INITIAL_MEMORY=2147418121 -s ALLOW_MEMORY_GROWTH=1  
# EMCC_LFLAGS 	:= -lm -pthread -lpthread -s ASSERTIONS=1 -s PROXY_TO_PTHREAD -s PTHREAD_POOL_SIZE=8 -s INITIAL_MEMORY=1073676288 #-s INITIAL_MEMORY=2147418112  -s INITIAL_MEMORY=134217728  -s ALLOW_MEMORY_GROWTH=1 1073676288
# NO_WASM_LFLAG 	:= -s WASM=0

# -s INITIAL_MEMORY=4294901760 
# -s ALLOW_MEMORY_GROWTH=1 -s MAXIMUM_MEMORY=4GB
#  -s NO_DISABLE_EXCEPTION_CATCHING
# -sENVIRONMENT=web
# -fsanitize=undefined

# ------------------------------------------------------------------------------

################################################################################
############################ COMPILATION VARIABLES #############################
################################################################################

# ------------------------------------------------------------------------------

CORE_SRC_FILES			:= $(wildcard $(SRC_DIR)/$(CORE_DIR)/*.cpp)
CORE_INC_FILES			:= $(wildcard $(INC_DIR)/$(CORE_DIR)/*.h)
CORE_GCC_OBJ_FILES		:= $(patsubst $(SRC_DIR)/$(CORE_DIR)/%.cpp,$(OBJ_DIR)/$(GCC_DIR)/$(CORE_DIR)/%.o,$(CORE_SRC_FILES))
CORE_EMCC_OBJ_FILES		:= $(patsubst $(SRC_DIR)/$(CORE_DIR)/%.cpp,$(OBJ_DIR)/$(EMCC_DIR)/$(CORE_DIR)/%.o,$(CORE_SRC_FILES))

# ------------------------------------------------------------------------------

TEST_SRC_FILES			:= $(wildcard $(SRC_DIR)/$(TEST_DIR)/*.cpp)
TEST_INC_FILES			:= $(wildcard $(INC_DIR)/$(TEST_DIR)/*.h)
TEST_GCC_OBJ_FILES		:= $(patsubst $(SRC_DIR)/$(TEST_DIR)/%.cpp,$(OBJ_DIR)/$(GCC_DIR)/$(TEST_DIR)/%.o,$(TEST_SRC_FILES))
TEST_EMCC_OBJ_FILES		:= $(patsubst $(SRC_DIR)/$(TEST_DIR)/%.cpp,$(OBJ_DIR)/$(EMCC_DIR)/$(TEST_DIR)/%.o,$(TEST_SRC_FILES))

# ------------------------------------------------------------------------------

EXP_SRC_FILES			:= $(wildcard $(SRC_DIR)/$(EXP_DIR)/*.cpp)
EXP_INC_FILES			:= $(wildcard $(INC_DIR)/$(EXP_DIR)/*.h)
EXP_GCC_OBJ_FILES		:= $(patsubst $(SRC_DIR)/$(EXP_DIR)/%.cpp,$(OBJ_DIR)/$(GCC_DIR)/$(EXP_DIR)/%.o,$(EXP_SRC_FILES))
EXP_EMCC_OBJ_FILES		:= $(patsubst $(SRC_DIR)/$(EXP_DIR)/%.cpp,$(OBJ_DIR)/$(EMCC_DIR)/$(EXP_DIR)/%.o,$(EXP_SRC_FILES))

# ------------------------------------------------------------------------------

################################################################################
############################### TOP LEVEL RULES ################################
################################################################################

.PHONY: thing
thing:
	@echo $(CORE_INC)

# ------------------------------------------------------------------------------
# top level build rules

.PHONY: build
build: build-all

.PHONY: build-all
build-all: build-native-c build-native-js build-native-wasm build-web-js build-web-wasm

.PHONY: all
all: build-all

# ------------------------------------------------------------------------------
# top level run

.PHONY: run
run: run-native-c

# ------------------------------------------------------------------------------
# top level clean

.PHONY: clean
clean: clean-all

.PHONY: clean-all
clean-all:
	@rm -fr $(OBJ_DIR)
	@rm -fr $(BIN_DIR)

# ------------------------------------------------------------------------------

################################################################################
##################################### GCC ######################################
################################################################################

.PHONY: build-gcc
build-gcc : build-gcc-core build-gcc-test build-gcc-exp

.PHONY: clean-gcc
clean-gcc:
	@rm -rf $(OBJ_DIR)/$(GCC_DIR)

# ----------------------------------  core ----------------------------------- #

.PHONY: build-gcc-core
build-gcc-core : gcc-core-directories $(CORE_GCC_OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-gcc-core: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

.PHONY: gcc-core-directories
gcc-core-directories :
	@mkdir -p $(OBJ_DIR)/$(GCC_DIR)/$(CORE_DIR)

$(OBJ_DIR)/$(GCC_DIR)/$(CORE_DIR)/%.o : $(SRC_DIR)/$(CORE_DIR)/%.cpp $(CORE_INC_FILES)
	$(CC) $(GCC_CFLAGS) $(CORE_INC) -c -o $@ $<

.PHONY: clean-gcc-core
clean-gcc-core:
	@rm -fr $(CORE_GCC_OBJ_DIR)

# ----------------------------------- test ----------------------------------- #

.PHONY: build-gcc-test
build-gcc-test : build-gcc-core gcc-test-directories $(TEST_GCC_OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-gcc-test: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

.PHONY: gcc-test-directories
gcc-test-directories :
	@mkdir -p $(OBJ_DIR)/$(GCC_DIR)/$(TEST_DIR)

$(OBJ_DIR)/$(GCC_DIR)/$(TEST_DIR)/%.o : $(SRC_DIR)/$(TEST_DIR)/%.cpp $(TEST_INC_FILES) $(CORE_INC_FILES)
	$(CC) $(GCC_CFLAGS) $(TEST_INC) -c -o $@ $<

.PHONY: clean-gcc-test
clean-gcc-test:
	@rm -fr $(TEST_GCC_OBJ_DIR)


# ----------------------------------- exp ------------------------------------ #

.PHONY: build-gcc-exp
build-gcc-exp : build-gcc-core gcc-exp-directories $(EXP_GCC_OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-gcc-exp: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

.PHONY: gcc-exp-directories
gcc-exp-directories :
	@mkdir -p $(OBJ_DIR)/$(GCC_DIR)/$(EXP_DIR)

$(OBJ_DIR)/$(GCC_DIR)/$(EXP_DIR)/%.o : $(SRC_DIR)/$(EXP_DIR)/%.cpp $(EXP_INC_FILES) $(CORE_INC_FILES)
	$(CC) $(GCC_CFLAGS) $(EXP_INC) -c -o $@ $<

.PHONY: clean-gcc-exp
clean-gcc-exp:
	@rm -fr $(EXP_GCC_OBJ_DIR)

# ------------------------------------------------------------------------------

################################################################################
##################################### EMCC #####################################
################################################################################

.PHONY: build-emcc
build-emcc : build-emcc-core build-emcc-test build-emcc-exp

.PHONY: clean-emcc
clean-emcc:
	@rm -rf $(OBJ_DIR)/$(EMCC_DIR)

# ----------------------------------  core ----------------------------------- #

.PHONY: build-emcc-core
build-emcc-core : emcc-core-directories $(CORE_EMCC_OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-emcc-core: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

.PHONY: emcc-core-directories
emcc-core-directories :
	@mkdir -p $(OBJ_DIR)/$(EMCC_DIR)/$(CORE_DIR)

$(OBJ_DIR)/$(EMCC_DIR)/$(CORE_DIR)/%.o : $(SRC_DIR)/$(CORE_DIR)/%.cpp $(CORE_INC_FILES)
	$(EMCC) $(EMCC_CFLAGS) $(CORE_INC) -c -o $@ $<

.PHONY: clean-emcc-core
clean-emcc-core:
	@rm -fr $(CORE_EMCC_OBJ_DIR)

# ----------------------------------- test ----------------------------------- #

.PHONY: build-emcc-test
build-emcc-test : build-emcc-core emcc-test-directories $(TEST_EMCC_OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-emcc-test: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

.PHONY: emcc-test-directories
emcc-test-directories :
	@mkdir -p $(OBJ_DIR)/$(EMCC_DIR)/$(TEST_DIR)

$(OBJ_DIR)/$(EMCC_DIR)/$(TEST_DIR)/%.o : $(SRC_DIR)/$(TEST_DIR)/%.cpp $(TEST_INC_FILES) $(CORE_INC_FILES)
	$(EMCC) $(EMCC_CFLAGS) $(TEST_INC) -c -o $@ $<

.PHONY: clean-emcc-test
clean-emcc-test:
	@rm -fr $(TEST_EMCC_OBJ_DIR)


# ----------------------------------- exp ------------------------------------ #

.PHONY: build-emcc-exp
build-emcc-exp : build-emcc-core emcc-exp-directories $(EXP_EMCC_OBJ_FILES)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> build-emcc-exp: ./$(word 2,$^)"
	@echo " ****************************************************************************** "

.PHONY: emcc-exp-directories
emcc-exp-directories :
	@mkdir -p $(OBJ_DIR)/$(EMCC_DIR)/$(EXP_DIR)

$(OBJ_DIR)/$(EMCC_DIR)/$(EXP_DIR)/%.o : $(SRC_DIR)/$(EXP_DIR)/%.cpp $(EXP_INC_FILES) $(CORE_INC_FILES)
	$(EMCC) $(EMCC_CFLAGS) $(EXP_INC) -c -o $@ $<

.PHONY: clean-emcc-exp
clean-emcc-exp:
	@rm -fr $(EXP_EMCC_OBJ_DIR)

# ------------------------------------------------------------------------------

################################################################################
################################ ACTUAL TARGETS ################################
################################################################################

# --------------------------------- native-c --------------------------------- #

.PHONY: run-native-c
run-native-c : run-native-c-test

.PHONY: run-native-c-test
run-native-c-test : build-native-c-test
	$(NATIVE_C_TEST)

.PHONY: run-native-c-exp
run-native-c-exp : build-native-c-exp
	$(NATIVE_C_EXP)


.PHONY: build-native-c
build-native-c : build-native-c-core build-native-c-test build-native-c-exp

.PHONY: build-native-c-core
build-native-c-core : build-gcc-core

.PHONY: build-native-c-test
build-native-c-test : build-gcc-test native-c-directories $(NATIVE_C_TEST)

.PHONY: build-native-c-exp
build-native-c-exp : build-gcc-exp native-c-directories $(NATIVE_C_EXP)

.PHONY: native-c-directories
native-c-directories:
	@mkdir -p $(NATIVE_C_BIN)

$(NATIVE_C_TEST) : $(TEST_GCC_OBJ_FILES) $(CORE_GCC_OBJ_FILES) 
	@$(CC) $(GCC_CFLAGS) -o $@ $^  $(GCC_LFLAGS)

$(NATIVE_C_EXP) : $(EXP_GCC_OBJ_FILES) $(CORE_GCC_OBJ_FILES)
	@$(CC) $(GCC_CFLAGS) -o $@ $^  $(GCC_LFLAGS)


.PHONY: clean-native-c
clean-native-c: clean-gcc
	@rm -rf $(NATIVE_C_BIN)

# -------------------------------- native-js --------------------------------- #

.PHONY: run-native-js
run-native-js : run-native-js-test

.PHONY: run-native-js-test
run-native-js-test : build-native-js-test
	node $(NATIVE_JS_TEST)

.PHONY: run-native-js-exp
run-native-js-exp : build-native-js-exp
	node --max-old-space-size=4096 $(NATIVE_JS_EXP)


.PHONY: build-native-js
build-native-js : build-native-js-core build-native-js-test build-native-js-exp

.PHONY: build-native-js-core
build-native-js-core : build-emcc-core

.PHONY: build-native-js-test
build-native-js-test : build-emcc-test native-js-directories $(NATIVE_JS_TEST)

.PHONY: build-native-js-exp
build-native-js-exp : build-emcc-exp native-js-directories $(NATIVE_JS_EXP)

.PHONY: native-js-directories
native-js-directories:
	@mkdir -p $(NATIVE_JS_BIN)

$(NATIVE_JS_TEST) : $(TEST_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES) 
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS) $(NO_WASM_LFLAG)

$(NATIVE_JS_EXP) : $(EXP_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES)
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS) $(NO_WASM_LFLAG)


.PHONY: clean-native-js
clean-native-js: clean-emcc
	@rm -rf $(NATIVE_JS_BIN)

# ------------------------------- native-wasm -------------------------------- #

.PHONY: run-native-wasm
run-native-wasm : run-native-wasm-test

.PHONY: run-native-wasm-test
run-native-wasm-test : build-native-wasm-test
	node $(NATIVE_WASM_TEST)

.PHONY: run-native-wasm-exp
run-native-wasm-exp : build-native-wasm-exp
	node --max-old-space-size=4096 $(NATIVE_WASM_EXP)


.PHONY: build-native-wasm
build-native-wasm : build-native-wasm-core build-native-wasm-test build-native-wasm-exp

.PHONY: build-native-wasm-core
build-native-wasm-core : build-emcc-core

.PHONY: build-native-wasm-test
build-native-wasm-test : build-emcc-test native-wasm-directories $(NATIVE_WASM_TEST)

.PHONY: build-native-wasm-exp
build-native-wasm-exp : build-emcc-exp native-wasm-directories $(NATIVE_WASM_EXP)

.PHONY: native-wasm-directories
native-wasm-directories:
	@mkdir -p $(NATIVE_WASM_BIN)

$(NATIVE_WASM_TEST) : $(TEST_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES) 
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS)

$(NATIVE_WASM_EXP) : $(EXP_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES)
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS)


.PHONY: clean-native-wasm
clean-native-wasm: clean-emcc
	@rm -rf $(NATIVE_WASM_BIN)

# ---------------------------------- web-js ---------------------------------- #

# .PHONY: run-web-js
# run-web-js : run-web-js-test

# .PHONY: run-web-js-test
# run-web-js-test : build-web-js-test
# 	node $(WEB_JS_TEST)

# .PHONY: run-web-js-exp
# run-web-js-exp : build-web-js-exp
# 	node --max-old-space-size=4096 $(WEBJS_EXP)


.PHONY: build-web-js
build-web-js : build-web-js-core build-web-js-test build-web-js-exp

.PHONY: build-web-js-core
build-web-js-core : build-emcc-core

.PHONY: build-web-js-test
build-web-js-test : build-emcc-test web-js-directories $(WEB_JS_TEST)

.PHONY: build-web-js-exp
build-web-js-exp : build-emcc-exp web-js-directories $(WEB_JS_EXP)

.PHONY: web-js-directories
web-js-directories:
	@mkdir -p $(WEB_JS_BIN)

$(WEB_JS_TEST) : $(TEST_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES) 
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS) $(NO_WASM_LFLAG)

$(WEB_JS_EXP) : $(EXP_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES)
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS) $(NO_WASM_LFLAG)


.PHONY: clean-web-js
clean-web-js: clean-emcc
	@rm -rf $(WEB_JS_BIN)

# --------------------------------- web-wasm --------------------------------- #

# .PHONY: run-web-wasm
# run-web-wasm : run-web-wasm-test

# .PHONY: run-web-wasm-test
# run-web-wasm-test : build-web-wasm-test
# 	node $(WEB_WASM_TEST)

# .PHONY: run-web-wasm-exp
# run-web-wasm-exp : build-web-wasm-exp
# 	node --max-old-space-size=4096 $(WEB_WASM_EXP)


.PHONY: build-web-wasm
build-web-wasm : build-web-wasm-core build-web-wasm-test build-web-wasm-exp

.PHONY: build-web-wasm-core
build-web-wasm-core : build-emcc-core

.PHONY: build-web-wasm-test
build-web-wasm-test : build-emcc-test web-wasm-directories $(WEB_WASM_TEST)

.PHONY: build-web-wasm-exp
build-web-wasm-exp : build-emcc-exp web-wasm-directories $(WEB_WASM_EXP)

.PHONY: web-wasm-directories
web-wasm-directories:
	@mkdir -p $(WEB_WASM_BIN)

$(WEB_WASM_TEST) : $(TEST_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES) 
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS)

$(WEB_WASM_EXP) : $(EXP_EMCC_OBJ_FILES) $(CORE_EMCC_OBJ_FILES)
	@$(EMCC) $(EMCC_CFLAGS) -o $@ $^  $(EMCC_LFLAGS)


.PHONY: clean-web-wasm
clean-web-wasm: clean-emcc
	@rm -rf $(WEB_WASM_BIN)

# ---------------------------------------------------------------------------- #

################################################################################
################################# END OF FILE ##################################
################################################################################