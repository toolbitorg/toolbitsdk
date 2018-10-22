JavaScript bindings
====

## Descripton

Build library of Toolbit Interface for JavaScript.


## Require

node.js

node-gyp

swig  
  http://www.swig.org/  


## Build


### Linux

    make
tbi.node will be created and copied to samples folder


### Windows

Install swig version 4.0.0 or later
    make
Execute "node-gyp configure build" on command prompt
Copy build/build/Release/tbi.node to samples


## Test

    cd ../samples
    node chopper_test.js


## Reference
