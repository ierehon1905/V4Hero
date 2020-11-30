# V4Hero
An official client for PatafourV4.
Coded in C++ with SFML lib using Code::Blocks IDE with GCC compiler

## How to run

You have to install SFML using frameworks, place them in /Library/Frameworks.

If it does not work check that
In Xcode project settings in Build Phases there is a run script ot copy all SFML rewuirement during build. 
In Builld Settings in Signing in Other Code Signing Flags pass "--deep" (without quotes)
In Signin and Capabilities in Hardened Runtime check Disable Library Validation
