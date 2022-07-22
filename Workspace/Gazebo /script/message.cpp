/*
    Author: Aditi Shanmugam 
    Date: 20-04-2022 | 10:24 PM
    About: C++ plugin file for Project1 
    Inputs: None 
    Outputs: Greeting Message - "Welcome to Aditi's World!\n"
*/

#include <gazebo/gazebo.hh>

namespace gazebo 
{
    class WorldPluginMyRobot : public WorldPlugin 
    {
        public: WorldPluginMyRobot() : WorldPlugin()
        {
            printf("Welcome to Aditi's World!\n");
        }
        public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
        {

        }
    };
GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)
}
