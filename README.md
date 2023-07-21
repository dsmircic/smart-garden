# smart-garden
IoT solution for monitoring clear water production out of a reverse osmosis desalinizer.

The solution uses two microcontrollers. One is set up as a sensor and transmitter which measures water flow at both the clear and waste ends of the desalinizer and transmits data to the receiver via the LoRa protocol. The receiving microcontroller serves as a _sink_ with access to a WiFi network and posts data to ThingsBoard Cloud service.

The posted data is then aggregated into different categories using a built-in rule engine on the platform. The platform serves as an endpoint for the user to view and monitor water production in real time.

A web service gathers data from the platform and displays it so the user can have a simpler interface for viewing data.
