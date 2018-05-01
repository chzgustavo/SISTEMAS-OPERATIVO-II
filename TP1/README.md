# SISTEMAS OPERATIVOS II
## Sockets en sistemas tipo UNIX
### Trabajo Practico N° 1: SOCKET TCP-UDP

				

***Descripción:*** El objetivo del presente trabajo práctico es diseñar e implementar un software que haga uso de la API de sockets del Sistema Operativo,implementando lo visto en el teórico y haciendo uso todos los conocimientos adquiridos en Ingeniería de Software y Sistemas Operativos I.


***Pasos que se deben realizar para poder compilar y ejecutar los programas:***

1. En el directorio donde este alojado servidor y cliente ejecute: ***make***
2. Puede ejecutar el servidor y cliente realizando: ***./servidor*** y ***./cliente***
3. En el cliente debe ingresar el prompt : ***connect user@ip:puerto***
	* user: se establecio 5 usuarios estos son: gustavo, armando, miguel, juan, max
	* ip: ip del servidor
	* puerto: 6020
4. En el cliente debe ingresar la contraseña:
	* usuario gustavo contraseña es: ***gustavo***
	* usuario armando contraseña es: ***armando***
	* usuario miguel contraseña es: ***miguel***
	* usuario juan contraseña es: ***juan***
	* usuario max contraseña es: ***max***
5. Si la autenticacion de usuario y contraseña es correcta el cliente puede comunicarse con el servidor de lo contrario debe ingresa nuevamente
6. Cliente puede ejecutar comando, si desea finalizar la seccion puede escribir ***exit***
7. Puede ejecutar ***make clean*** si desea borrar los archivos ejecutables
