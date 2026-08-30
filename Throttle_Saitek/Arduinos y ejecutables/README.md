# RP2040-Zero: trim, encoder y conmutadores HID

Este proyecto hace que una Waveshare RP2040-Zero aparezca en el ordenador como
un dispositivo USB HID con un eje Z real para el potenciómetro, un eje Slider
virtual controlado por encoder y catorce botones.

## Conexiones

| Componente | RP2040-Zero |
|---|---|
| Potenciómetro, extremo 1 | 3V3 |
| Potenciómetro, cursor central | GPIO26 |
| Potenciómetro, extremo 2 | GND |
| Botón 1 | GPIO2 y GND |
| Botón 2 | GPIO3 y GND |
| Botón 3 | GPIO4 y GND |
| Botón 4 | GPIO5 y GND |
| Botón 5 | GPIO9 y GND |
| Encoder A / CLK | GPIO6 |
| Encoder B / DT | GPIO7 |
| Encoder común | GND |
| Pulsación encoder SW | GPIO8 y GND |
| Conmutador 1 ON | GPIO10 y común a GND |
| Conmutador 1 OFF | GPIO11 y común a GND |
| Selector encoder: botón HID 9, motor/luces | GPIO12 y común a GND |
| Selector encoder: botón HID 10, radios | GPIO13 y común a GND |
| Momentáneo 1 ARRIBA | GPIO14 y común a GND |
| Momentáneo 1 ABAJO | GPIO15 y común a GND |
| Momentáneo 2 ARRIBA | GPIO27 y común a GND |
| Momentáneo 2 ABAJO | GPIO28 y común a GND |

Los pulsadores no necesitan resistencias externas: el programa activa las
resistencias pull-up internas. Los dos conmutadores momentáneos se consideran
del tipo `(ON)-OFF-(ON)`, con retorno por muelle al centro. Si el eje Z funciona
al revés, intercambia los dos extremos del potenciómetro (3V3 y GND).

El encoder aparece como `Slider`. Arranca en el centro (512) porque un encoder
incremental no conoce una posición absoluta después de desconectar la corriente.
Cada clic cambia 16 unidades. Estos valores pueden ajustarse mediante
`ENCODER_AXIS_START` y `ENCODER_AXIS_STEP`.

## Encoder en DCS y MSFS

El encoder mantiene simultáneamente dos salidas:

- En DCS aparece como eje HID `Slider`.
- En MSFS envía órdenes de radio, motor y luces por el puerto serie USB al programa
  `MSFS_Radio_Bridge.exe`.

El puente debe estar abierto y conectado al puerto COM de la RP2040-Zero y a
SimConnect. El comportamiento del pulsador del encoder se decide al soltarlo:

El selector de GPIO12/GPIO13 siempre debe cerrar una sola entrada contra GND:

- Botón HID 10 / GPIO13 activo: funcionamiento de radios e instrumentos.
- Botón HID 9 / GPIO12 activo: funcionamiento de llave, calefacción y luces.

| Duración | Radio/instrumento normal | Modo selección |
|---|---|---|
| Menos de 1 segundo | Alterna unidades/decimales en COM/NAV o cambia la cifra ADF | Confirma el control seleccionado y sale de selección |
| Entre 1 y 2 segundos | Intercambia activa/standby | Sin efecto |
| 2 segundos o más | Entra en selección | Sin efecto |

Dentro del modo selección, el equipo se cambia girando el encoder:

`COM1`, `COM2`, `NAV1`, `OBS1`, `NAV2`, `OBS2`, `ADF1`, `ADF HDG`,
`ALTÍMETRO`, `DIRECCIONAL` y `TRANSPONDEDOR`.

COM1, COM2, NAV1, NAV2 y ADF1 indican la selección alternando automáticamente
un paso de la frecuencia standby y restaurándolo cada 350 ms. OBS1, OBS2,
ADF HDG, ALTÍMETRO y DIRECCIONAL hacen el mismo movimiento de un paso con su
mando correspondiente. El TRANSPONDEDOR alterna únicamente su cuarta cifra.
Al cambiar de equipo o salir mediante un clic corto, el valor original se
restaura.

En uso normal, COM/NAV modifican siempre la frecuencia standby. En ADF, el
primer clic corto selecciona la cifra 2, el siguiente la cifra 3 y el siguiente
vuelve a la cifra 1. Cada giro modifica únicamente 100, 10 o 1 kHz según esa
selección interna. Las acciones se realizan al soltar el pulsador, por lo que
mantenerlo apretado no genera repetición. OBS cambia un grado, ADF HDG gira la
carta del ADF, ALTÍMETRO modifica el ajuste barométrico y DIRECCIONAL ajusta el
heading gyro.

### Transpondedor

Al confirmarlo desde la selección comienza controlando la cifra 1:

- Giro: cambia solamente la cifra seleccionada; MSFS limita cada cifra a 0...7.
- Clic corto: cifra 1 -> cifra 2 -> cifra 3 -> cifra 4 -> cifra 1.
- Pulsación larga de 1 a 3 segundos: alterna entre cifras y el selector `KNOB`.
- En `KNOB`, cada paso del encoder mueve el selector por
  `OFF -> STBY -> ON -> ALT -> TEST -> GROUND`.
- Pulsación extra larga de 3 segundos o más: abandona el transpondedor y entra
  en la selección general, tanto desde las cifras como desde `KNOB`.

Las acciones se deciden al soltar el pulsador y no tienen autorepetición.

### Llave, calefacción y luces

Al pasar el selector físico al botón HID 9/GPIO12 comienza siempre en `LLAVE`.
Los elementos se recorren en este orden:

`CEBADOR <- LLAVE -> CARB HEAT -> PITOT HEAT -> NAV LIGHTS -> STROBES ->
ROTATING BEACON -> TAXI LIGHT -> LANDING LIGHT`.

- Al entrar estás en control directo de `LLAVE`: el giro mueve la llave un punto
  a derecha o izquierda.
- Un clic corto sale de la llave y abre el selector, inicialmente sobre `LLAVE`.
- Tres clics cortos seguidos vuelven inmediatamente al control directo de
  `LLAVE` sin ejecutar los dos primeros clics.

En el modo de selección:

- El giro del encoder recorre la lista de controles en ambos sentidos.
- La lista no es circular: al llegar a CEBADOR o LANDING permanece en ese
  extremo. Para volver hay que girar en sentido contrario o usar triple clic.
- Un clic corto sobre cualquier interruptor cambia su estado entre ON y OFF.
- Al cambiar de selección con la rueda, el interruptor nuevo hace inmediatamente
  un pulso corto de 150 ms; repite al segundo y después cada dos segundos.
  Antes de cambiar de control, accionarlo o salir, el pulso se restaura.
- `LLAVE` no parpadea. Si el selector está sobre `LLAVE`, un clic corto vuelve a
  entrar en su control directo; para regresar al selector hay que pulsar otra vez.
- Girando a la izquierda desde LLAVE se selecciona `CEBADOR`. Un clic dispara el
  cebador del motor 1. El cebador tampoco parpadea.

El triple clic funciona también en radios: vuelve a `COM1`, modo de ajuste normal
y parte de unidades. Para distinguir el triple clic, la acción sencilla se
ejecuta unos 450 ms después del último clic.

**Importante:** el GPIO26 admite como máximo 3,3 V. No conectes el potenciómetro
a 5 V. Si la lectura oscila, puede añadirse un condensador cerámico de 100 nF
entre GPIO26 y GND, cerca de la placa.

## Preparación de Arduino IDE

1. En `Archivo > Preferencias > URLs adicionales para el Gestor de tarjetas`, añade:

   `https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json`

2. En el Gestor de tarjetas, busca `pico` e instala **Raspberry Pi Pico/RP2040**
   de Earle F. Philhower.
3. Selecciona `Herramientas > Placa > Raspberry Pi Pico/RP2040 > Waveshare
   RP2040 Zero`.
4. Selecciona `Herramientas > USB Stack > Adafruit TinyUSB`.
5. Abre `trimwheel.ino` y pulsa **Subir**.

En la primera carga, mantén pulsado **BOOT**, conecta el USB-C, suelta **BOOT**
y selecciona `UF2 Board` como puerto. Las cargas siguientes normalmente se
realizan sin pulsar BOOT.

## Prueba en Windows

Pulsa `Win + R`, escribe `joy.cpl` y pulsa Intro. Abre las propiedades del
controlador: el potenciómetro debe mover el eje Z, el encoder debe mover Slider
y las entradas digitales deben encender los botones 1 a 14.

## Ajuste del recorrido

El potenciómetro trabaja con resolución de 10 bits, de 0 a 1023. El filtro 1/8
reduce el ruido manteniendo una respuesta continua. Si el encoder gira al
revés, cambia `ENCODER_DIRECTION` de `1` a `-1`. Si solo avanza cada dos clics,
cambia `ENCODER_TRANSITIONS_PER_DETENT` de `4` a `2`.

## Referencias

- [Instalación de Arduino-Pico](https://arduino-pico.readthedocs.io/en/latest/install.html)
- [USB y Adafruit TinyUSB en Arduino-Pico](https://arduino-pico.readthedocs.io/en/latest/usb.html)
- [Página oficial de Waveshare RP2040-Zero](https://www.waveshare.com/wiki/RP2040-Zero)
