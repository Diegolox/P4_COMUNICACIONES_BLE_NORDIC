# P4 · Comunicaciones Bluetooth

Práctica de comunicación inalámbrica con **Bluetooth Low Energy (BLE)** en Arduino Nano 33 BLE y **Bluetooth Classic** en ESP32. Se trabaja el descubrimiento de dispositivos, el acceso a datos mediante GATT y el intercambio de mensajes mediante un puerto serie Bluetooth.

Los proyectos utilizan PlatformIO y el framework Arduino. La carpeta `hal` reúne el manejo del hardware y la comunicación Bluetooth; `network` contiene la definición y gestión del GATT, y `protocol` implementa el comportamiento del eco en el ESP32.

## 1. Advertising BLE

Proyecto: [P4_01_ADVERSITING_NOMBRE](P4_01_ADVERSITING_NOMBRE).

El *advertising* permite que un dispositivo BLE anuncie su presencia sin establecer previamente una conexión. En este ejercicio, el Nano se identifica como `Nano-DIEGO` y anuncia un servicio con el UUID personalizado `44494547-4F00-0000-0000-000000000000`, cuyos primeros bytes representan «DIEGO» en ASCII.

`initBLEAdvertising()` configura e inicia el anuncio. Después, `updateBLE()` llama a `BLE.poll()` para atender los eventos de comunicación. El dispositivo puede descubrirse desde una aplicación como nRF Connect.

> **DIAGRAMA PENDIENTE:** anuncio del Nano y detección desde el móvil.

<!-- Sustituir el marcador anterior por: ![Advertising BLE](docs/advertising.png) -->

## 2. GATT: LED RGB y acelerómetro

Proyecto: [P4_02_GATT](P4_02_GATT).

GATT organiza los datos que expone el periférico BLE. Un **servicio** agrupa funciones relacionadas y una **característica** contiene un valor con sus operaciones permitidas: lectura, escritura o notificación. Cada servicio y característica se identifica mediante un UUID. Los **descriptores** añaden información sobre las características, como su significado o sus unidades.

El Nano actúa como periférico y servidor GATT. El servicio del LED permite leer y escribir su color: `0` apaga el LED, `1` enciende el rojo, `2` el verde y `3` el azul.

El servicio de la IMU ofrece la aceleración en formato `x;y;z`, expresada en **g**. El cliente puede leer el valor o suscribirse a notificaciones para recibir nuevas medidas. Otra característica permite detener las lecturas escribiendo `0` y reanudarlas escribiendo `1`.

`initGATT()` registra los servicios, características y descriptores. `updateGATT()` procesa las órdenes recibidas y actualiza las medidas cuando hay datos nuevos y la lectura está activa.

> **DIAGRAMA PENDIENTE:** árbol GATT con los servicios LED e IMU y sus características.

<!-- Sustituir el marcador anterior por: ![Estructura GATT](docs/gatt.png) -->

## 3. Bluetooth Classic: eco de mensajes

Proyecto: [P4_03_BLUETOOTH_CLASSIC](P4_03_BLUETOOTH_CLASSIC).

El ESP32 utiliza `BluetoothSerial` y el perfil **SPP**, que permite intercambiar datos como por un puerto serie. Se anuncia con el nombre `ESP32-Chat` y puede utilizarse desde un terminal del PC conectado a su puerto Bluetooth.

`leerBluetooth()` acumula los caracteres entre llamadas y devuelve el mensaje cuando recibe un retorno de carro o salto de línea. Mientras está incompleto devuelve una cadena vacía, sin quedarse esperando. `escribirBluetooth()` envía el texto con un salto de línea.

La función `eco_mensaje()` devuelve cada mensaje no vacío con el prefijo `ECO-`: al enviar `Hola`, se recibe `ECO-Hola`.

> **DIAGRAMA PENDIENTE:** envío desde el PC, recepción en el ESP32 y respuesta de eco.

<!-- Sustituir el marcador anterior por: ![Eco Bluetooth Classic](docs/eco-bluetooth.png) -->

## Uso

Abrir la carpeta del ejercicio en PlatformIO y cargarlo en su placa correspondiente. Para BLE, explorar el Nano desde nRF Connect y acceder a sus características. Para Bluetooth Classic, emparejar el ESP32 con el PC, abrir el puerto serie Bluetooth y enviar mensajes terminados en CR o LF.
