OUT_DIR:=bin
SOURCES_DIR:=src
OBJ_SOURCE:=$(SOURCES_DIR)/evenList.cpp \
	    $(SOURCES_DIR)/random.cpp  \
            $(SOURCES_DIR)/Simtel_simulation.cpp  \
            $(SOURCES_DIR)/simulation.cpp  \
            



halloo:$(OBJ_SOURCE) 
	g++ -o $(OUT_DIR)/$@  $^ -I.
