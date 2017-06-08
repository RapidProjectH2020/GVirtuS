/*
 * gVirtuS -- A GPGPU transparent virtualization component.
 *
 * Copyright (C) 2009-2010  The University of Napoli Parthenope at Naples.
 *
 * This file is part of gVirtuS.
 *
 * gVirtuS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gVirtuS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gVirtuS; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Written by: Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>,
 *             Department of Applied Science
 */

#include <iostream>
#include <cstdio>
#include <string>

#include "CudnnHandler.h"

using namespace std;
using namespace log4cplus;

CUDNN_ROUTINE_HANDLER(Create){
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("Create"));
    
    cudnnHandle_t handle;
    cudnnStatus_t cs = cudnnCreate(&handle);
    Buffer * out = new Buffer();
    try{
        out->Add<cudnnHandle_t>(handle);
    } catch (string e){
        LOG4CPLUS_DEBUG(logger,e);
        return new Result(CUDNN_STATUS_EXECUTION_FAILED);
    }
    return new Result(cs,out);
}

CUDNN_ROUTINE_HANDLER(GetVersion){
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("GetVersion"));
    
    size_t version = cudnnGetVersion();
    return new Result(version);
}

CUDNN_ROUTINE_HANDLER(GetErrorString){
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("GetErrorString"));
    cudnnStatus_t cs = in->Get<cudnnStatus_t>();
    const char * s = cudnnGetErrorString(cs);
    Buffer * out = new Buffer();
    try{
        out->Add((char *)s);
    } catch (string e){
        LOG4CPLUS_DEBUG(logger,e);
        return new Result(CUDNN_STATUS_EXECUTION_FAILED);
    }
    return new Result(CUDNN_STATUS_SUCCESS,out);
}