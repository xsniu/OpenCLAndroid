//--------------------------------------------------------------------------------------
// File: hello_world.cpp
// Desc:
//
// Author:      QUALCOMM
//
//               Copyright (c) 2017 QUALCOMM Technologies, Inc.
//                         All Rights Reserved.
//                      QUALCOMM Proprietary/GTDR
//--------------------------------------------------------------------------------------

// Std includes
#include <cstdlib>
#include <fstream>
#include <iostream>

// Project includes
#include "oclutil/cl_wrapper.h"

// Library includes
#include <CL/cl.h>


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "debug.h"

static const char *HELP_MESSAGE = "\n"
"Usage: hello_world <input> <output>\n"
"\n"
"This example copies the input file to the output file.\n"
"Use it to test your build tools.\n";

static const char *PROGRAM_SOURCE[] = {
"__kernel void copy(__global char *src,\n",
"                   __global char *dst\n",
"                   )\n",
"{\n",
"    uint wid_x = get_global_id(0);\n",
"    dst[wid_x] = src[wid_x];\n",
"}\n"
};

using namespace cv;

static const cl_uint PROGRAM_SOURCE_LEN = sizeof(PROGRAM_SOURCE) / sizeof(const char *);

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        Debug_error("Please specify source and destination files.\n") ;
        Debug_error("%s\n",HELP_MESSAGE);
        std::exit(EXIT_SUCCESS);
    }
    const std::string src_filename(argv[1]);
    const std::string out_filename(argv[2]);

    Mat imgSrc = imread(src_filename, IMREAD_UNCHANGED);
    if(imgSrc.empty()){
        Debug_error("Can not read File %s\n", src_filename.c_str());
        exit(-1);
    }

    cl_wrapper       wrapper;
    cl_program       program         = wrapper.make_program(PROGRAM_SOURCE, PROGRAM_SOURCE_LEN);
    cl_kernel        kernel          = wrapper.make_kernel("copy", program);
    cl_context       context         = wrapper.get_context();
    cl_command_queue command_queue   = wrapper.get_command_queue();
    cl_int           err             = CL_SUCCESS;

    const int srcWidth    = imgSrc.cols;
    const int srcHeight   = imgSrc.rows;
    const int srcChannels = imgSrc.channels();
    printf("%d\n",srcChannels);


    const size_t buf_size  = srcWidth*srcHeight*srcChannels;
    std::vector<char> buf(buf_size);
    memcpy(buf.data(), imgSrc.data, buf_size);

    cl_mem src_buffer = clCreateBuffer(
            context,
            CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
            buf_size,
            buf.data(),
            &err
    );
    if (err != CL_SUCCESS) {
        Debug_error(" with clCreateBuffer for source file.");
        std::exit(err);
    }

    cl_mem out_buffer = clCreateBuffer(
            context,
            CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,
            buf_size,
            NULL,
            &err );
    if (err != CL_SUCCESS) {
        Debug_error("with clCreateBuffer for output file.");
        std::exit(err);
    }

    /*
     * Step 1: Set up kernel arguments and run the kernel.
     */

    err = clSetKernelArg(kernel, 0, sizeof(src_buffer), &src_buffer);
    if (err != CL_SUCCESS) {
        Debug_error("with clSetKernelArg for argument 0.");
        std::exit(err);
    }

    err = clSetKernelArg(kernel, 1, sizeof(out_buffer), &out_buffer);
    if (err != CL_SUCCESS) {
        Debug_error(" with clSetKernelArg for argument 1.");
        std::exit(err);
    }

    err = clEnqueueNDRangeKernel(
            command_queue,
            kernel,
            1,
            NULL,
            &buf_size,
            NULL,
            0,
            NULL,
            NULL
    );
    if (err != CL_SUCCESS) {
        Debug_error("with clEnqueueNDRangeKernel.");
        std::exit(err);
    }

    /*
     * Step 2: Copy the data out of the ion buffer for each plane.
     */

    char *mapped_ptr = static_cast<char *>(clEnqueueMapBuffer(
            command_queue,
            out_buffer,
            CL_TRUE,
            CL_MAP_READ,
            0,
            buf_size,
            0,
            NULL,
            NULL,
            &err ));
    if (err != CL_SUCCESS) {
        Debug_error("mapping output buffer.");
        std::exit(err);
    }

    Mat imgDst = Mat(srcHeight, srcWidth, CV_8UC3);
    memcpy(static_cast<void*>(imgDst.data), mapped_ptr, buf_size);
    imwrite(out_filename, imgDst);

    err = clEnqueueUnmapMemObject(command_queue, out_buffer, mapped_ptr, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        Debug_error("unmapping output buffer.");
        std::exit(err);
    }

    clFinish(command_queue);

    // Clean up cl resources that aren't automatically handled by cl_wrapper
    clReleaseMemObject(src_buffer);
    clReleaseMemObject(out_buffer);

    return 0;
}