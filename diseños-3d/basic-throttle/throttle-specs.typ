#set document(title: "Club de Vuelo - Especificaciones throttle", author: "cdv-diseño")

#set page(
  margin: (top: 4cm, bottom: 2cm),
  header: [
    #grid(
      columns: (1fr, 1fr, 1fr),
      align: (left + bottom, center + bottom, right + bottom),

      box(align(center)[
        #image("etsiae-logo-cropped.pdf", height: 1.2cm) \
        #v(-1.5em, weak: true) // Optional spacing
        #text(size: 8pt)[Club de Vuelo UPM]
      ]),

      align(horizon)[
        #text(weight: "bold", size: 16pt)[Especificaciones throttle]
      ],

      align(horizon)[
        #datetime.today().display("[day]-[month]-[year]")
      ],
    )
    #v(0.2em)
    #line(length: 100%, stroke: 0.3pt) // Separator line below header
  ],
  footer: [
    #set align(center)
    // Dynamic page numbering
    #context [Page #counter(page).display("1 of 1", both: true)]
  ],
)
= Especificaciones para el throttle:
A continuación se presenta la funcionalidad deseada para el throttle

== Funcionalidad requerida:

- Un eje principal para el throttle (sensor magnético)
- Eje alternativo para prop rpm (sensor magnético)
- Interruptor para el tren (ON-ON)
- Interruptor para los flaps (MON-OFF-MON)
- Botón en el throttle (pulgar)
- Botón para centrar la vista
- Ruedas de trimado

=== Inputs necesarios:
+ Bus I2C (1x o alternativamente 1x MUX)
+ 6x Input digital
+ 2x Input analógico

=== Microcontrolador:
Se utilizará un Arduino Pro Micro, disponible ya de antemano en el club.

== Funcionalidad del hardware requerida

- El throttle deberá poder anclarse a la silla o a la mesa.
- La fricción en los ejes debe de ser ajustable.
- El botón de centrar la vista debe ser accesible.
