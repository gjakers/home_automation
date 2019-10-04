#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <Hue.h>
#include <LinHttpHandler.h>

const string bridge_ip  = "192.168.0.16";
const string username   = "-7PH4kS18LbdcR3LBZHBDY4gZ5UUvhsSAkAHcQhH";
const string bridge_mac = "00:17:88:A3:B1:3F";

using namespace std;
void main(int argc, char** argv) 
{  
    for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\n"; 
	
	if (argc < 3) {
		printf("Command format: lights.exe <target> <cmd>\n");
		return;
	}
	
	char *target = argv[1];
	char *cmd    = argv[2];
	vector<string> extra;
	if (argc > 3) {
		for(int i=3; i<=argc; i++)
			extra.push_back(string(argv[i]);
	}
	
	vector<int> targets;
	
	/* target is 'all' */
	if (string::npos != target.find("all") {
		for (int i=1; i<6; i++)
			targets.push_back(i);
	} else {
		for (int i=0; < strlen(target); i++) {
			if(target[i] != ',')
				targets.push_back((int)target[i]);
		}	
	}
	
	/* Initialize Bridge */
	auto handler = std::make_shared<LinHttpHandler>();
	Hue bridge(bridge_ip, username, handler);
	
	for (int i=0; i<targets.size(); i++) {
		if (cmd == "on") {
			bridge.getLight(targets[i]).On();
		}
		if (cmd == "off") {
			bridge.getLight(targets[i]).Off();
		}
		if (cmd == "mag")
			bridge.getLight(targets[i]).setBrightness(stoi(extra[0]));
		if (cmd == "col")
			bridge.getLight(targets[i]).setColorRGB(stoi(extra[0]),
													stoi(extra[1]),
													stoi(extra[2]));
	}
}
	
