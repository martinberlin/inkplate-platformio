# Inkplate-platformio
Compiling Inkplate6 with Platformio instead of Arduino IDE

### Select your test

Just edit platformio.ini and uncomment only one of the src_dir folders to select what example to run:

    [platformio]
    default_envs = esp32
    # Select what example to compile uncommenting only one of this lines:
    #src_dir = examples/1. Basic Inkplate Functionality/1-Inkplate_basic_monochrome
    src_dir = examples/1. Basic Inkplate Functionality/2-Inkplate_basic_grayscale

That will select the 2-Inkplate_basic_grayscale cpp file of the folder examples/1. Basic Inkplate Functionality and compile it. Not ideal but lets you have many different tests under the same codebase.

Only examples of the 1. and 2. sections are done. Just rename to cpp and add new examples if you feel like