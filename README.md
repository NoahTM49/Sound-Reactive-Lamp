Sound-Reactive Lamp v1 Prototype
Built: May, 2026 
Documented: August, 2026
## Description

A sound-reactive desk lamp built around an Elegoo Nano V3.0, a MAX4466 electret mic module, and a 140-LED WS2812B strip driven with FastLED. The Arduino Nano samples the ambient sound level at roughly 70 Hz, using both an envelope follower and a fast-decaying peak detector to determine the number of lit LEDs that should glow a blue-to-purple gradient across the strip. The unlit LEDs are kept at a dim floor level to ensure the device still appears to be a lamp when placed in a quiet room. However, due to the few millimeters of clearance within the lamp tube itself, the Arduino Nano and mic were both routed outside of the lamp. I plan to have no hardware sticking outside of the lamp in its next version. 

## Demo

Video:

https://github.com/user-attachments/assets/0a8d51de-e844-4e49-a3c6-ed6fb9db21a7

Photos:
Assembled and lit		Tube Open			Circuit withdrawn
<img width="896" height="491" alt="Screenshot 2026-08-28 113226" src="https://github.com/user-attachments/assets/f6db85a7-08c5-4008-8dde-a592e9897096" />

## Behavior

Input:
A certain sound level picked up by the mic. The lamp is unable to distinguish between bass and treble and reacts to sound in general. Although I would like to figure out how to make this possible in the next version. 

Output:
The LEDs range from purple at the base to blue at the top, the lamp is always these colors. Though easily changeable in the code, it isn’t changeable elsewhere. 

Range:
Conversation within 5-10 feet is the lowest volume to be picked up by the lamp. If music is played too loudly however, it peaks out and shines as bright as possible.

## How It Works

Pickup:
MAX4466 electret module. It has a built-in preamp with adjustable gain on the back of the module. It outputs an analog voltage read at A0.

Baseline calibration:
500 samples averaged at startup to establish the DC bias level.

Detection:
It uses an exponential smoothing filter with a peak follower with 0.85 decay per cycle. Deadband below 15 is set to 0. 

Mapping:
Peak value scaled to a count of lit LEDs using map() with a ceiling of 80.

## Bill of materials

<img width="980" height="215" alt="Screenshot 2026-08-28 113830" src="https://github.com/user-attachments/assets/cb59b6b6-d49d-4f35-b771-5ea4f0bb09d5" />

## Firmware

Platform: Elegoo Nano V3.0 (ATmega328P), Arduino IDE, C++

Libraries: FastLED

## Code

[lamp.ino](lamp.ino)

## Fit

The prototype has a cramped fit, which has led to the biggest constraint, hardware sticking out. I used a small, clear PVC I found in my garage to wrap the LEDs around. It was too small to fit the hardware inside of, I learned this the hard way when I broke two of my solder joints on my Elegoo Nano trying to fit it inside of the pipe, twice. Even though it was too small, it was just large enough to leave no room in the acrylic piece for the hardware either.

Mic Mounting: 

The mic is mounted outside of the lamp, it is taped to the side of the lamp. I did this because it was unable to pick up the right audio when inside of the lamp. 

## What Version 2 Changes

As stated before, I look to have no hardware visible or sticking out of the lamp. I want to use a small and hollow stand for the lamp’s components to lie in. The mic will have a hole to be able to pick up noise but will have nothing else showing besides its electret microphone capsule. Among these changes, I would also like to have the color be changed using a remote or a button. Finally, if I can figure out a way to have the microphone distinguish the difference between bass and treble. 

## What I would do differently

I would slow down. With a 3 week deadline to work on the prototype before my summer classes began, I was determined to finish it before then. If I were to restart though, I would have taken the time to fix the jumper wires being used in a joint that would flex and I would have tried harder to put less strain on certain components. Neither would have taken more than a couple days to fix.  The lesson I took from this is that on a project like this, the electrical design feels like the most important engineering aspect when it really is the packaging and connections that determine whether it survives. 

## Appendix

Datasheets & Part Documentation:

MAX4466 - Weewooday electret microphone amplifier module with adjustable gain. Product page: https://www.amazon.com/Electret-Microphone-Amplifier-Adjustable-Breakout/dp/B08N4FNFTR/ref=sr_1_1_sspa?dib=eyJ2IjoiMSJ9.fh3BFvg2sEMm621wa0Ji-rt_pAPeks7H_Yd6NLSL2jClLITcIAcEIOOkQLeTRHjUAJGmSFVM88AxhlPHsV8te8i49gZE1HuL2wACRZVw-ej8wjgwT1a6jyaHSaxz5Og6v3zz1giA-ZfE1ZBpZ_nOjn9Zsz3YDxXq3o3STpJE3sWLMhBsnXtRK5qY7U_OWB5-izm4z1zLF-4ff5ycA_r3sMqOfuFi-oxpSvkmdZzttDc.0G1ooafj_bSZZGyFO6aRHFe5XNaSIS-kjXehK9oDM_U&dib_tag=se&keywords=max4466&qid=1787940111&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1
Datasheet: Analog Devices, MAX4465–MAX4469.

WS2812B - Intelligent control LED integrated light source. Datasheet: Worldsemi.

ATmega328P - 8-bit AVR microcontroller. Datasheet: Microchip.

References

Music Reactive Desk Light || DIY
https://youtu.be/5oRir4dck_w?si=xNusLMDWw6s88zuA

Arduino Tutorial 1 through 7
https://youtu.be/fJWR7dBuc18?si=Eeo2PfMx8ZmUIxts
https://youtu.be/9uHZB7-T_XA?si=pZz6v3PjOTd_G-du
https://youtu.be/CfdaJ4z4u4w?si=a507VJ39y4eYZ1lw
https://youtu.be/nPOKOi1jIK0?si=hq_dedGSeWLX10nf
https://youtu.be/rTuKKVcYeMg?si=tRHRdmNTaHbj_WEL
https://youtu.be/Lg39qKrdySU?si=pJa5EnaI_oGQF8bM
https://youtu.be/6CRhpUV92ww?si=QMQLMWCabZnhFFQG

How to Code Arduino: Beginner’s Tutorial
https://youtu.be/ZOllXMxLRqc?si=1CjI8bn-YERET0IE

FastLED library documentation - fastled.io

FastLED wiki: power management and setMaxPowerInVoltsAndMilliamps()

## Tools

Arduino IDE - firmware development

FastLED - LED driver library

Digital multimeter - supply voltage and current draw verification

Arduino-based serial plotter - I used this to observe the mic signal envelope to tune the threshold.

Loop Timing Breakdown:

<img width="640" height="163" alt="Screenshot 2026-08-28 113901" src="https://github.com/user-attachments/assets/e31aa324-10e0-4129-9b9d-fd11bce281a9" />
