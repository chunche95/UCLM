# Notificador de ofertas de videojuegos
En este ejercicio vas a crear un sistema de notificación de ofertas de videojuegos usando el protocolo MQTT en Python, con el módulo Paho. El sistema constará de dos partes: un editor que enviará información sobre ofertas de videojuegos y un suscriptor que recibirá dichas notificaciones según los intereses del usuario.

El editor deberá enviar mensajes con el nombre del videojuego y el porcentaje de descuento, uno por segundo, a un broker MQTT según la jerarquía de temas:

```
videojuegos/ofertas/<tipo>/<desarrollador>
```

El suscriptor deberá suscribirse a temas según sus intereses, los cuales serán especificados vía línea de comando. Por ejemplo, si el usuario está interesado en videojuegos de acción de los desarrolladores Ubisoft y Rockstar:

```
suscriptor.py -d ubisoft rockstar -t acción
```

Y si están interesados ​​en algún tipo de videojuego de la desarrolladora Valve:

```
suscriptor.py -d válvula
```

Para todos los mensajes de interés se publicará un texto en el terminal, imprimiendo un texto especial en caso de que el descuento sea superior al 70%.