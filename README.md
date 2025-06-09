# Disclaimer
I started this project out of curiosity. In the meantime, I have delved deeper into rendering pipelines and the basics of ray tracing.
These files were created in the course of a ray tracing series from the YouTube channel ‘The Cherno’. Copying code is nothing special - I just want to show that I'm interested in many things and can familiarise myself with them quickly.

# Walnut App Template

This is a simple app template for [Walnut](https://github.com/TheCherno/Walnut) - unlike the example within the Walnut repository, this keeps Walnut as an external submodule and is much more sensible for actually building applications. See the [Walnut](https://github.com/TheCherno/Walnut) repository for more details.

## Getting Started
Once you've cloned, you can customize the `premake5.lua` and `WalnutApp/premake5.lua` files to your liking (eg. change the name from "WalnutApp" to something else).  Once you're happy, run `scripts/Setup.bat` to generate Visual Studio 2022 solution/project files. Your app is located in the `WalnutApp/` directory, which some basic example code to get you going in `WalnutApp/src/WalnutApp.cpp`. I recommend modifying that WalnutApp project to create your own application, as everything should be setup and ready to go.
