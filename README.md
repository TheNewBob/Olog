# Olog

A simple logging library for the orbiter spaceflight simulator for C++ 11.

## Why would I use it?

Orbiter has a perfectly servicable logging function. Put the emphasis on the singular "a", as in "one".  
Logging in an orbiter add-on usually entails using a lot of sprintf, since that one logging function has no string interpolation of its own.  
Also, Propper logging usually entails multiple log levels. This means that logging in Orbiter add-ons is either non-existant, insufficient or that the developer in question implemented something along the lines of Olog by himself.
Olog aims at eliminating that hassle for developers and provide concise, simple and performant logging.

## Nice words, but what do they mean exactly?

* simple synthax
* Your standard log levels: Error, Warn, Info, Debug and Trace
* sprintf-style string interpolation built right into the logging calls
* Lazy interpolation, i.e. string interpolation of logging messages is only performed if the message is actually logged.
* logged asserts that are evaluated or not depending on the set log level.

### Wait, why would I need logged asserts?

Admittedly, you probably don't. However, if you happen to work on a big project and have external testers, the ability to activate and deactivate your asserts independant of build, and have them logged, can come in very handy.

## Okay, how do I use it?

Add Olog/include to your include folders, and either add the .cpp file directly to your project, or use the provided libs for debug and release build.
Here's a short example of how to use it.   
Usually you'd just set your defaults in your initModule callback, and do the logging wherever you need it, obviously:

```
#define ORBITER_MODULE
#include "orbitersdk.h"
#include "Olog.h"

DLLCLBK void InitModule (HINSTANCE hModule)
{
	Olog::loglevel = OLOG_DEBUG;        //set your default log level
	Olog::assertlevel = OLOG_DEBUG;     //set the log level at and below which asserts should be evaluated
	Olog::projectName = "Olog Demo";    //set the name of your project. Olog will prepend this name to its messages so you can identify relevant entries.

	char *testmessage = "this is the %i%s test";
	Olog::trace(testmessage, 1, "st");  //this won't actually get logged, since the level is set to debug.
	Olog::debug(testmessage, 2, "nd");
	Olog::info(testmessage, 3, "rd");
	Olog::warn(testmessage, 4, "th");
	Olog::error(testmessage, 5, "th");	//This will just log an error, but not throw anything.
	
    //use a lambda to pass predicates to your asserts:    
	int a = 1;
	int b = 2;
	Olog::assertThat([&]() { return a > b; }, testmessage, 6, "th");  //this will log the passed message and terminate the simulation with a runtime exception, since it's false, and our current assert level is equal to our log level. If we'd raise the log level to info, this would not be evaluated.
}
```

The above example will produce the following output in orbiter.log:

```
000000.000: Olog Demo:[DEBUG] this is the 2nd test
000000.000: Olog Demo:[INFO] this is the 3rd test
000000.000: Olog Demo:[!WARNING!] this is the 4th test
000000.000: Olog Demo:[!!ERROR!!] this is the 5th test
000000.000: Olog Demo:[!!ERROR!!] Assertion failed: this is the 6th test
```

To allow setting the loglevel from your vessels cfg file, use this:

```
void MyClass::clbkSetClassCaps (FILEHANDLE cfg) 
{
	Olog::setLogLevelFromFile(cfg);
    // proceed to load your vessel data
}
```

If no log level is defined in the cfg, this won't do anything. But anyone can now add a line like this:  
```
OLOGLEVEL = Debug
```  
to the vessels cfg file to override the default log level and get more detailed log output, or set it higher and not be bothered by any performance loss that the potentially noisy logging at lower levels may incur.


 