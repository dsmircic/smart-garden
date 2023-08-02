# smart-garden
IoT solution for monitoring water production out of a reverse osmosis desalinizer.

The solution uses two microcontrollers. One is set up as a sensor and transmitter which measures water flow at the clear output of the desalinizer and transmits data to the receiver via the LoRa protocol. The receiving microcontroller serves as a _sink_ with access to a WiFi network and posts data to ThingsBoard Cloud service.

The posted data is then aggregated into different categories using a built-in rule engine on the platform. The platform serves as an endpoint for the user to view and monitor water production in real time.

Akenza.io aggregates measurements and displays them so the user can have a simpler interface for viewing data.
