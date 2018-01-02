# DogGoneIt
Code for an ESP8266 automated dog feeder that runs on MQTT. 

Very simple Dog feeder - see https://hackaday.io/project/28942-voice-activated-dog-feeder for more details. 

Essentially it is a ploy-pipe dog biscuit silo with a trap door operated by a continious rotation servo. The servo is driven by an ESP 8266 that received MQTT messages to trigger the servo. I have subsequently hooked it up to my google home mini to make it voice activated.

Hardware is a wemos D1 (r2) hooked up to a servo in the following configuration:
 * WEMOS  - Servo 
 * 5V     - 5V
 * Gnd    - Gnd
 * D3     - Signal
