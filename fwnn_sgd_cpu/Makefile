objects=main.o mnistio.o \
		log_reg_layer.o hidden_layer.o sgd_learn.o \
		neural_network.o forward_layer.o full_connect_layer.o \
		conv_layer.o maxpool_layer.o

cnn_sgd:$(objects)
	g++ -o cnn_sgd -framework opencl $(objects)

main.o: mnistio.h sgd_learn.h log_reg_layer.h neural_network.h main.cpp
#myclutils.o:myclutils.h
mnistio.o:mnistio.h
forward_layer.o:forward_layer.h
full_connect_layer.o:full_connect_layer.h forward_layer.h
log_reg_layer.o:full_connect_layer.h log_reg_layer.h
hidden_layer.o:full_connect_layer.h hidden_layer.h
conv_layer.o:conv_layer.h
maxpool_layer.o:maxpool_layer.h
neural_network.o:neural_network.h forward_layer.h log_reg_layer.h hidden_layer.h maxpool_layer.h conv_layer.h
sgd_learn.o:sgd_learn.h neural_network.h

.PHONY : clean
clean :
	-rm cnn_sgd $(objects)
