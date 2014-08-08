//
//  Created by Takashi Aoki (c) takashiaoki.com
//
//  Released under the MIT license
//  http://opensource.org/licenses/mit-license.php
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "lo/lo.h"

typedef enum ofxLoArgType
{
	OFXLO_TYPE_NONE,
	OFXLO_TYPE_INT,
	//OFXLO_TYPE_INT32,
	//OFXLO_TYPE_INT64,
	OFXLO_TYPE_FLOAT,
	OFXLO_TYPE_STRING,
	OFXLO_TYPE_BLOB,
	//OFXLO_TYPE_BUNDLE,
} ofxLoArgType;

/*

ofxLoArg

*/

class ofxLoArg
{
public:
	ofxLoArg(){ _type = OFXLO_TYPE_NONE; };
	virtual ~ofxLoArg(){};

	virtual const ofxLoArgType& getType() { return _type; }
	virtual std::string getTypeName() { return "none"; }

protected:
	ofxLoArgType _type;
};

class ofxLoArgInt : public ofxLoArg
{
public:
	ofxLoArgInt(int value)
	{
		_value = value; _type = OFXLO_TYPE_INT;
	};
	~ofxLoArgInt(){};

	const ofxLoArgType& getType() { return _type; }
	std::string getTypeName() { return "i"; }
	int get(){ return _value; };

private:
	int _value;
};

class ofxLoArgFloat : public ofxLoArg
{
public:
	ofxLoArgFloat(float value)
	{
		_value = value; _type = OFXLO_TYPE_FLOAT;
	};
	~ofxLoArgFloat(){};

	const ofxLoArgType& getType() { return _type; }
	std::string getTypeName() { return "f"; }
	float get(){ return _value; };

private:
	float _value;
};

class ofxLoArgString : public ofxLoArg
{
public:
	ofxLoArgString(std::string value)
	{
		_value = value; _type = OFXLO_TYPE_STRING;
	};
	~ofxLoArgString(){};

	const ofxLoArgType& getType() { return _type; }
	std::string getTypeName() { return "s"; }
	std::string get(){ return _value; };

private:
	std::string _value;
};

/*

ofxLoArg: Blob Object

*/

class ofxLoBlob
{
public:
	ofxLoBlob(){};
	~ofxLoBlob(){};

	lo_blob blob;
	unsigned char* pixels;
};

class ofxLoArgBlob : public ofxLoArg
{
public:
	ofxLoArgBlob(int size, const void* value)
	{
		_value = lo_blob_new(size, value);	
		_type  = OFXLO_TYPE_BLOB;
	};
	ofxLoArgBlob(lo_blob value)
	{
		_value = value;
		_type  = OFXLO_TYPE_BLOB;
	};
	~ofxLoArgBlob(){};

	const ofxLoArgType& getType() { return _type; }
	std::string getTypeName() { return "b"; }
	
	lo_blob get(){ return _value; };

	unsigned char* getPixels()
	{ 
		return (unsigned char *)lo_blob_dataptr(_value); 
	};


private:
	lo_blob _value;
};

/*

ofxLoMessage: message object

*/

class ofxLoMessage
{
public:
	ofxLoMessage(){};
	~ofxLoMessage()
	{
		//std::cout << "clear" << std::endl;
		clear();
	};

	ofxLoMessage( ofxLoMessage& other ){ copy ( other ); }
	ofxLoMessage& operator= ( ofxLoMessage& other ) { return copy( other ); }
	ofxLoMessage& copy( ofxLoMessage& other )
	{
		clear();

		_address = other.getAddress();

		//remote_host = other.remote_host;
		//remote_port = other.remote_port;

		// copy arguments
		for(std::vector<ofxLoArg*>::iterator it = other._args.begin(); it != other._args.end(); it++)
		{
			ofxLoArg* arg = *(it);
			if(arg->getType() == OFXLO_TYPE_INT)        _args.push_back(new ofxLoArgInt(((ofxLoArgInt*)arg)->get()));
			else if(arg->getType() == OFXLO_TYPE_FLOAT) _args.push_back(new ofxLoArgFloat(((ofxLoArgFloat*)arg)->get()));
			else if(arg->getType() == OFXLO_TYPE_STRING)_args.push_back(new ofxLoArgString(((ofxLoArgString*)arg)->get()));
			else if(arg->getType() == OFXLO_TYPE_BLOB)_args.push_back(new ofxLoArgBlob(((ofxLoArgBlob*)arg)->get()));
		}

		return *this;
	}
	void clear()
	{
		for(std::vector<ofxLoArg*>::iterator it = _args.begin(); it != _args.end();it++)
		{
			delete *(it);
		}
		_args.clear();
	}
	int getNumArgs() const
	{
		return (int)_args.size();
	};
	ofxLoArg* getArg(int index) const
	{
		return _args[index];
	};
	int getArgAsInt( int index ) const
	{
		ofxLoArg* arg = _args[index];
		if(arg->getType() != OFXLO_TYPE_INT)
		{
			std::cout << "error!" << std::endl;
			return 0;
		}
		else return ((ofxLoArgInt*)arg)->get();
	};
	float getArgAsFloat( int index ) const
	{
		ofxLoArg* arg = _args[index];
		if(arg->getType() != OFXLO_TYPE_FLOAT)
		{
			std::cout << "error!" << std::endl;
			return 0;
		}
		else return ((ofxLoArgFloat*)arg)->get();
	};
	std::string getArgAsString( int index ) const
	{
		ofxLoArg* arg = _args[index];
		if(arg->getType() != OFXLO_TYPE_STRING)
		{
			std::cout << "error!" << std::endl;
			return 0;
		}
		else return ((ofxLoArgString*)arg)->get();
	};


	// TEST
	lo_blob getArgAsBlob( int index ) const
	{
		ofxLoArg* arg = _args[index];
		if(arg->getType() != OFXLO_TYPE_BLOB)
		{
			std::cout << "error!" << std::endl;
			return 0;
		}
		else return ((ofxLoArgBlob*)arg)->get();
	};

	unsigned char* getArgAsPixels(int index) const
	{
		ofxLoArg* arg = _args[index];
		if(arg->getType() != OFXLO_TYPE_BLOB)
		{
			std::cout << "error!" << std::endl;
			return 0;
		}
		else return ((ofxLoArgBlob*)arg)->getPixels();
	};

	const std::string& getAddress() const { return _address; };
	void setAddress(std::string address){ _address = address; };

	void addIntArg( int argument )
	{
		_args.push_back( new ofxLoArgInt(argument) );
	};
	void addFloatArg( float argument )
	{
		_args.push_back( new ofxLoArgFloat(argument) );
	};
	void addStringArg( std::string argument )
	{
		_args.push_back( new ofxLoArgString(argument) );
	};
	
	void addBlobArg( int size, const void* data )
	{
		_args.push_back( new ofxLoArgBlob(size, data) );
	};
	void addBlobArg(lo_blob argument)
	{
		_args.push_back( new ofxLoArgBlob(argument) );
	};

protected:
	bool hasArg(int index)
	{
		return (index > _args.size())? false : true;
	};

	std::vector<ofxLoArg*> _args;
	std::string _address;
};