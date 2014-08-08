//
//  ofxLoReceiver
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
#include <map>
#include <deque>

#include "lo/lo.h"
#include "ofxLoMessage.h"

// callback function of Liblo
int lo_recieve(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data);

class ofxLoReceiver
{
public:
	ofxLoReceiver(){};
	~ofxLoReceiver(){};
    
	void setup(std::string port)
	{
		_reciever = lo_server_thread_new(port.c_str(), NULL);
	};

    // returns true if there are any messages waiting for collection
    bool hasWaitingMessages()
    {
        int queue_length = (int)_messages.size();
        return queue_length > 0;
    };

    /// take the next message on the queue of received messages, copy its details into message, and
    /// remove it from the queue. return false if there are no more messages to be got, otherwise
    /// return true
    bool getNextMessage(ofxLoMessage* message)
    {
        // copy the message from the queue to message
        ofxLoMessage* src_message = _messages.front();
        message->copy( *src_message );

        delete src_message;
        _messages.pop_front(); // and remove it from the queue

        return true;
    };
    
    // osc address, type of arguments, number of parametors
    void addAdress(std::string path, ofxLoArgType type, int argsize=1)
	{
        std::string a_type = "";
        
		if(type == OFXLO_TYPE_INT)
		{
            a_type = "i";	
		}
        else if(type == OFXLO_TYPE_FLOAT)
        {
            a_type = "f";
        }
        else if(type == OFXLO_TYPE_STRING)
        {
            a_type = "s";
        }
        else if(type == OFXLO_TYPE_BLOB)
        {
            a_type = "b";
        }
        else if(type == OFXLO_TYPE_NONE)
		{
            a_type = "";
		}

        std::string types = "";
        int n = 0; while (n < argsize){ types += a_type; n++; }
        lo_server_thread_add_method(_reciever, path.c_str(), types.c_str(), lo_recieve, this);
	};
	void start()
	{
		lo_server_thread_start(_reciever);	
	};
    void processMessage(ofxLoMessage* message)
    {
        _messages.push_back(message);
    };

private:
    lo_address _reciever;
    std::deque<ofxLoMessage*> _messages;
};