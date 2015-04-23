#include <OpenCL/opencl.h>
cl_context CreateGPUContext();
cl_context CreateCPUContext();
cl_command_queue CreateCommandQueue(cl_context context,cl_device_id *device,int device_num);
cl_program CreateProgram(cl_context context, cl_device_id device,const char* fileName);
const char *getErrorString(cl_int error);
