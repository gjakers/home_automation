/***********************************************************
 * hue.cpp
 * Testing hueplusplus API for light control
 ***********************************************************/
#include <iostream>
#include <iomanip>
#include <hueplusplus>

const std::string bridge_ip  = "192.168.0.16";
const std::string username   = "gakers";
const std::string bridge_mac = "00:17:88:A3:B1:3F";

handler = std::make_shared<LinHttpHandler>();

/**Getting username?*********************************************************/
HueFinder finder(handler);
std::vector<HueFinder::HueIdentification> bridges = finder.FindBridges();
if (bridges.empty())
{
	bridges.push_back({ bridge_ip, bridge_mac });
}
Hue tmp_bridge = finder.GetBridge(bridges[0]);
std::string user = tmp_bridge.getUsername();

cout << "Username: " << user << "\n";
/****************************************************************************/

handler = std::make_shared<LinHttpHandler>();
Hue bridge(bridge_ip, user, handler);

std::string c, cmd;
int light;
while(1) {
  std::cout 
    << "Enter a command\n"
    << "Format: <light> <cmd>\n"
    << "\tcommands:\n"
    << "\t (on)  - turn light on\n"
    << "\t (off) - turn light off\n"
    << "\t (mag) (val) - set brightness\n"
    << "\t (col) (R) (G) (B) - set color to RGB\n"
    << "\t (inf) - Get light information\n";
  std::cin >> c;
  std::istringstream iss(c);
  std::vector<std::string> res(std::istream_iterator<std::string>{iss},
                               std::istream_iterator<std::string>());
  light = std::stoi(res[0]);
  cmd   = res[1];
  if(cmd == "on")
    bridge.getLight(light).On();
  if(cmd == "off")
    bridge.getLight(light).Off();
  if(cmd == "mag") 
    bridge.getLight(light).setBrightness(std::stoi(res[2]));
  if(cmd == "col")
    bridge.getLight(light).setColorRGB(std::stoi(res[3]),
                                       std::stoi(res[4]),
                                       std::stoi(res[5]));
  if(cmd == "inf")
    std::cout << std::boolalpha
      << "\nName: "                    << bridge.getLight(light).getName()
      << "\nType: "                     << bridge.getLight(light).getType()
      << "\nColor type: "              << bridge.getLight(light).getColorType()
      << "\nHas brightness control? "  << bridge.getLight(light).hasBrightnessControl()
      << "\nHas temperature control? " << bridge.getLight(light).hasTemperatureControl()
      << "\nHas color control? "       << bridge.getLight(light).hasColorControl() << '\n';
}





