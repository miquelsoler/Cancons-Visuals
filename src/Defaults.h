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



#define ENABLE_LIVE false
#define ENABLE_KINECT true
#define ENABLE_MULTIPLE_FBOS false
#define ENABLE_MULTILAYER_EXPORT false
#define ENABLE_KNEES_DETECTION true
#define ENABLE_PRINTING true
#define ENABLE_REMOTE_KINECT false



static const float          WINDOW_SCALE_FACTOR         = 1.0f;
static const float          FBO_SCALE_FACTOR            = 1.0f;

static const int            WINDOW_WIDTH                = 1920;
static const int            WINDOW_HEIGHT               = 685;

static const int			DESIGN_WIDTH = 1920;
static const int			DESIGN_HEIGHT = 685;

static const int			DESIGN_LEFT_WIDTH = 898;
static const int			DESIGN_LEFT_HEIGHT = 470;

static const int            DEFAULT_WINDOW_WIDTH        = int(float(WINDOW_WIDTH) * WINDOW_SCALE_FACTOR);
static const int            DEFAULT_WINDOW_HEIGHT       = int(float(WINDOW_HEIGHT) * WINDOW_SCALE_FACTOR);

#if ENABLE_MULTIPLE_FBOS
static const int            FBO_WIDTH                   = int(float(WINDOW_WIDTH) * FBO_SCALE_FACTOR);
static const int            FBO_HEIGHT                  = int(float(WINDOW_HEIGHT) * FBO_SCALE_FACTOR);
#else
static const int            FBO_WIDTH                   = int(float(WINDOW_WIDTH) * FBO_SCALE_FACTOR);
static const int            FBO_HEIGHT                  = int(float(WINDOW_HEIGHT) * FBO_SCALE_FACTOR);
#endif

static const ofWindowMode   DEFAULT_WINDOW_MODE         = OF_WINDOW;

static const int            DEFAULT_SAMPLERATE          = 44100;
static const int            DEFAULT_BUFFERSIZE          = 512;
static const bool			PERFORMANCE_MODE			= false;

#endif
