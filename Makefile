DIST_PATH=DistributedServer

CENTRAL_PATH=CentralServer

DIST_NAME=distributed_server.bin

CENTRAL_NAME=central_server.bin

run: all
	./$(DIST_NAME) & ./$(CENTRAL_NAME)

all: CENTRAL_SERVER DISTRIBUTED_SERVER

clean:
	cd $(CENTRAL_PATH) && make clean
	cd $(DIST_PATH) && make clean

CENTRAL_SERVER:
	cd $(CENTRAL_PATH) && make all
	mv $(CENTRAL_PATH)/$(CENTRAL_NAME) ./
	
DISTRIBUTED_SERVER:
	cd $(DIST_PATH) && make all
	mv $(DIST_PATH)/$(DIST_NAME) ./

