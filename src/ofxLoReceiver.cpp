//
//  Created by Takashi Aoki (c) takashiaoki.com
//

#include "ofxLoReceiver.h"

int lo_recieve(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
{
    ofxLoReceiver* target = (ofxLoReceiver*)user_data;

    ofxLoMessage* message =  new ofxLoMessage();
    std::string ad = path;
    message->setAddress(ad);

    for (int i = 0; i < argc; i++)
    {
        if(types[i] == 'i')
        {
            message->addIntArg(argv[i]->i);
        }
        else if(types[i] == 'f')
        {
            message->addFloatArg(argv[i]->f);
        }
        else if(types[i] == 's')
        {
            message->addStringArg(&argv[i]->s);
        }
        else if(types[i] == 'b')
        {
            message->addBlobArg((lo_blob)argv[i]);
        }
    }

    target->processMessage(message);
    
    return 0;
};