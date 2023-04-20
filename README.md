# featherhuzzah

This is code for featherHuzzah ES-P12s.
We used this module for TCP connection to server.
Code is modified from one of the Arduino examples for FeatherHuzzah.

**In Finnish**
Arduino lähettää omalta serialmonitorilta dataa (mySerial). FeatherHuzzah kuuntelee yhtä pinniä (RX3) ja kirjoittaa kaiken saatavilla olevan
datan omalle serialmonitorille. Data lähetetään edelleen palvelimelle TCP-yhteydellä.
