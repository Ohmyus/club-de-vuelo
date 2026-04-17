#set document(title: "Club de Vuelo - Especificaciones stick", author: "cdv-diseño")

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
= Especificaciones para la base:
Los requisitos para la base son los siguientes:

== Funcionalidad requerida:

- Dos ejes principales para el movimiento de la palanca (Encoders magnéticos)
- Interfaz modular para aceptar tipos de grips (conector GX-20-10p)

=== Inputs necesarios:
+ Bus I2C (2x o alternativamente 1x MUX)
+ 10x Input igital

=== Microcontrolador:
Se utilizará un Arduino Pro Micro, disponible ya de antemano en el club.

== Funcionalidad del hardware requerida

- La base debe de ser lo suficientemente rígida para permitir operación exigente.
- La conexión al grip debe de ser sólida y evitar cualquier tipo de juego.
- [Opcional] La fuerza de centrado de los muelles debe de ser ajustable.
