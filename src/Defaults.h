//
//  Config.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 5/6/15.
//
//

#pragma once

#ifdef _DEBUG
#define OF_DEBUG
#endif // _DEBUG


#ifndef ConductrEnter_Config_h
#define ConductrEnter_Config_h 


#define ENABLE_KINECT true
#define ENABLE_MULTIPLE_FBOS false
#define ENABLE_MULTILAYER_EXPORT false
#define ENABLE_KNEES_DETECTION true
#define ENABLE_PRINTING true
#define ENABLE_REMOTE_KINECT false
#define ENABLE_MULTI_USER false



static const float          WINDOW_SCALE_FACTOR         = 1.0f;
static const float          FBO_SCALE_FACTOR            = 1.0f;

static const int            WINDOW_WIDTH                = 1920;
static const int            WINDOW_HEIGHT               = 1080;

static const int			DESIGN_WIDTH = WINDOW_WIDTH;
static const int			DESIGN_HEIGHT = WINDOW_HEIGHT;

static const int			DESIGN_LEFT_WIDTH = 920;
static const int			DESIGN_LEFT_HEIGHT = 472;

static const int            DEFAULT_WINDOW_WIDTH        = int(float(WINDOW_WIDTH) * WINDOW_SCALE_FACTOR);
static const int            DEFAULT_WINDOW_HEIGHT       = int(float(WINDOW_HEIGHT) * WINDOW_SCALE_FACTOR);

#if ENABLE_MULTIPLE_FBOS
static const int            FBO_WIDTH                   = int(float(WINDOW_WIDTH) * FBO_SCALE_FACTOR);
static const int            FBO_HEIGHT                  = int(float(WINDOW_HEIGHT) * FBO_SCALE_FACTOR);
#else
static const int            FBO_WIDTH                   = int(float(DESIGN_WIDTH) * FBO_SCALE_FACTOR);
static const int            FBO_HEIGHT                  = int(float(DESIGN_HEIGHT) * FBO_SCALE_FACTOR);
#endif

static const ofWindowMode   DEFAULT_WINDOW_MODE         = OF_WINDOW;

static const int            DEFAULT_SAMPLERATE          = 44100;
static const int            DEFAULT_BUFFERSIZE          = 512;
static const bool			PERFORMANCE_MODE			= true;

static const int NUM_ERASED_COLORS = 3; //for debuging purposes

#endif
