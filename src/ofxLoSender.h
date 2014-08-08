//
//  ofxLoSender
//
//  Created by Takashi Aoki (c) takashiaoki.com
//  openFrameworks addon for liblo OSC Library, inspired by ofxOsc.
//  
//  liblo version 0.25
//  liblo: http://liblo.sourceforge.net/ 
//
//  Released under the MIT license
//  http://opensource.org/licenses/mit-license.php
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "lo/lo.h"
#include "ofxLoMessage.h"

class ofxLoSender
{
public:
	ofxLoSender(){};
	~ofxLoSender(){};
    
	void setup(std::string hostname, std::string port)
	{
		_sender = lo_address_new(hostname.c_str(), port.c_str());
    	lo_server_thread_start(_sender);
	};

	void sendMessage(ofxLoMessage& message)
	{
		lo_message m = lo_message_new();

		for(int i=0; i< message.getNumArgs(); ++i)
		{
			ofxLoArg* arg = message.getArg(i);

			if(arg->getType() == OFXLO_TYPE_INT)
			{
				lo_message_add_int32(m, ((ofxLoArgInt*)arg)->get());
			}
			else if(arg->getType() == OFXLO_TYPE_FLOAT)
			{
				lo_message_add_float(m, ((ofxLoArgFloat*)arg)->get());
			}
			else if(arg->getType() == OFXLO_TYPE_STRING)
			{
				lo_message_add_string(m, ((ofxLoArgString*)arg)->get().c_str());
			}
			else if(arg->getType() == OFXLO_TYPE_BLOB)
			{
				lo_message_add_blob(m, ((ofxLoArgBlob*)arg)->get());
			}
		}

		lo_send_message(_sender, message.getAddress().c_str(), m);
		lo_message_free(m);

		//message.clear();
	};

private:
	lo_address _sender;
};