@echo off
mkdir build

tools-builder\arduino-builder -compile -logger=machine -hardware hardware -tools tools-builder -tools hardware\tools -libraries libraries -fqbn=arduino:avr:leonardo -ide-version=10819 -build-path build -warnings=all -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.arduinoOTA.path=hardware\tools -prefs=runtime.tools.arduinoOTA-1.3.0.path=hardware\tools -prefs=runtime.tools.avrdude.path=hardware\tools -prefs=runtime.tools.avrdude-6.3.0-arduino17.path=hardware\tools -prefs=runtime.tools.avr-gcc.path=hardware\tools -prefs=runtime.tools.avr-gcc-7.3.0-atmel3.6.1-arduino7.path=hardware\tools -verbose user_script.cpp
pause

RD /S /Q build
mkdir build