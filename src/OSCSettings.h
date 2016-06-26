//
//  OSCSettings.h
//  MovimentsGranados
//
//  Created by Miquel Angel Soler on 4/1/16.
//
//

#pragma once
//#include <stdlib.h>

#ifndef MovimentsGranados_OSCSettings_h
#define MovimentsGranados_OSCSettings_h

// Kinect
static const string         OSC_KINECT_SENDER_HOST          = "192.168.7.122";
static const string			OSC_KINECT_RECEIVER_HOST		= "192.168.1.122";
static const int            OSC_KINECT_SENDER_PORT          = 30304;
static const int			OSC_KINECT_SENDER_PORT_VIDEO	= 7890;
static const string         OSC_KINECT_ADDR_BASE            = "/motion";
static const string         OSC_KINECT_ADDR_STATE           = "/detectionStatus";
static const string         OSC_KINECT_STATE_DETECTING      = "Detecting";
static const string         OSC_KINECT_STATE_CAPTURING      = "Capturing";
static const string         OSC_KINECT_STATE_POSITIONED     = "Positioned";
static const string         OSC_KINECT_ADDR_LHAND           = "/leftHand";
static const string         OSC_KINECT_ADDR_RHAND           = "/rightHand";
static const string         OSC_KINECT_ADDR_LKNEE			= "/leftKnee";
static const string         OSC_KINECT_ADDR_RKNEE			= "/rightKnee";
static const string         OSC_KINECT_ADDR_POSITION        = "/position";
static const string         OSC_KINECT_ADDR_VELOCITY        = "/velocity";
static const string         OSC_KINECT_ADDR_KEY				= "/key";
static const string         OSC_KINECT_ADDR_MOUSE_MOVE		= "/mouseMove";
static const string         OSC_KINECT_ADDR_MOUSE_PRESS		= "/mousePress";


#endif
