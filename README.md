```markdown
# cub3d
Mi primer RayCaster con miniLibX

**Capítulo II**  
**Objetivos**  
Los objetivos de este proyecto son similares a los de todos los proyectos del primer año: rigor, uso de C, aplicación de algoritmos básicos, investigación de información, etc.  

Como proyecto de diseño gráfico, **cub3D** te permitirá mejorar tus habilidades en las siguientes áreas: manejo de ventanas, colores, eventos, formas rellenas, etc.  

En conclusión, **cub3D** es un campo de juego notable para explorar las aplicaciones prácticas y lúdicas de las matemáticas sin necesidad de entender todos sus detalles específicos.  

Con la ayuda de los numerosos documentos disponibles en internet, utilizarás las matemáticas como herramienta para crear algoritmos elegantes y eficientes.

**Capítulo III**  
**Instrucciones Comunes**  

- Tu proyecto debe estar escrito en **C**.  
- Debe cumplir con la **Norma**. Si tienes archivos o funciones de bonificación, también serán verificados según la norma, y recibirás un 0 si se encuentra algún error en ella.  
- Tus funciones no deben terminar inesperadamente (fallo de segmentación, error de bus, doble liberación de memoria, etc.), excepto en casos de comportamientos indefinidos. Si esto ocurre, tu proyecto será considerado no funcional y recibirá un 0 durante la evaluación.  
- Toda la memoria asignada en el heap debe ser liberada correctamente cuando sea necesario. No se tolerarán fugas de memoria.  
- Si el enunciado lo requiere, debes entregar un **Makefile** que compile tus archivos fuente al resultado solicitado, utilizando las banderas `-Wall`, `-Wextra` y `-Werror`, con el compilador `cc`. Además, tu **Makefile** no debe realizar relinks.  
- Tu **Makefile** debe contener al menos las reglas: `$(NAME)`, `all`, `clean`, `fclean` y `re`.  
- Para incluir bonificaciones en tu proyecto, debes agregar una regla **bonus** a tu **Makefile**, que incluirá todos los encabezados, librerías o funciones adicionales que están prohibidas en la parte principal del proyecto. Las bonificaciones deben estar en un archivo separado con el sufijo `_bonus.{c/h}` si no se especifica lo contrario en el enunciado. La evaluación de la parte obligatoria y de bonificación se realiza por separado.  
- Si tu proyecto permite el uso de tu **libft**, debes copiar sus fuentes y su **Makefile** asociado en una carpeta llamada **libft**. El **Makefile** de tu proyecto debe compilar la librería utilizando su propio **Makefile**, y luego compilar el proyecto.  
- Se te anima a crear programas de prueba para tu proyecto, aunque este trabajo no será entregado ni evaluado. Estos programas te permitirán probar fácilmente tu trabajo y el de tus compañeros. Encontrarás estas pruebas especialmente útiles durante tu defensa, donde puedes usarlas junto con las de tus compañeros a los que estés evaluando.  
- Entrega tu trabajo en el repositorio **git** asignado. Solo se evaluará el trabajo que se encuentre en el repositorio después de las evaluaciones por parte de tus compañeros, si ocurre un error en cualquier sección de tu trabajo durante la calificación de Deepthought, la evaluación se detendrá.

**Capítulo IV**  
**Parte Obligatoria - cub3D**  

- **Nombre del programa:** cub3D  
- **Archivos a entregar:** Todos tus archivos.  
- **Makefile:** Debe incluir las reglas `all`, `clean`, `fclean`, `re`, `bonus`.  
- **Argumentos:** Un mapa en formato `*.cub`.  
- **Funciones externas permitidas:**  
  - `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, `gettimeofday`.  
  - Todas las funciones de la librería matemática (`-lm`, `man 3 math`).  
  - Todas las funciones de la MiniLibX.  
- **Libft autorizada:** Sí.  
- **Descripción:**  
  Debes crear una representación gráfica en 3D "realista" del interior de un laberinto desde una perspectiva en primera persona. Esta representación debe realizarse utilizando los principios de **Ray-Casting** mencionados anteriormente.  

**Restricciones:**  
- Debes usar la **miniLibX**. Puedes optar por usar la versión disponible en el sistema operativo o compilarla desde sus fuentes. Si eliges trabajar con las fuentes, debes aplicar las mismas reglas para tu libft que las mencionadas en la sección de Instrucciones Comunes.  
- La gestión de la ventana debe ser fluida: cambiar a otra ventana, minimizar, etc., debe funcionar correctamente.  
- Muestra diferentes texturas de paredes (puedes elegirlas) que varíen dependiendo de la orientación de la pared (Norte, Sur, Este, Oeste).

- **Tu programa debe ser capaz de configurar colores diferentes para el suelo y el techo.**  
- **El programa muestra la imagen en una ventana y debe respetar las siguientes reglas:**  
  - Las teclas de flecha izquierda y derecha del teclado deben permitir mirar hacia la izquierda y la derecha en el laberinto.  
  - Las teclas **W**, **A**, **S** y **D** deben permitir mover el punto de vista a través del laberinto.  
  - Presionar **ESC** debe cerrar la ventana y salir del programa limpiamente.  
  - Hacer clic en la cruz roja del marco de la ventana debe cerrar la ventana y salir del programa limpiamente.  
  - Se recomienda encarecidamente el uso de imágenes de la **MiniLibX**.  

- **Tu programa debe tomar como primer argumento un archivo de descripción de escena con la extensión `.cub`.**  
  - El mapa debe estar compuesto por solo 6 caracteres posibles:  
    - `0` para un espacio vacío.  
    - `1` para una pared.  
    - `N`, `S`, `E` o `W` para la posición inicial del jugador y la orientación al iniciar.  

**Ejemplo de un mapa válido:**  
```
111111  
100101  
101001  
1100N1  
111111  
```

- **Reglas adicionales para el mapa:**  
  - El mapa debe estar cerrado/rodeado por paredes; si no es así, el programa debe devolver un error.  
  - Excepto por el contenido del mapa, cada tipo de elemento puede estar separado por una o más líneas vacías.  
  - Excepto por el contenido del mapa, que siempre debe ser lo último, cada tipo de elemento puede aparecer en cualquier orden en el archivo.  
  - Excepto por el mapa, cada tipo de información de un elemento puede estar separado por uno o más espacios.  
  - El mapa debe ser interpretado tal como aparece en el archivo. Los espacios son una parte válida del mapa y debes gestionarlos adecuadamente. Tu programa debe ser capaz de interpretar cualquier tipo de mapa que respete estas reglas.

  - **Cada elemento (excepto el mapa) comienza con un identificador de tipo** (compuesto por uno o dos caracteres), seguido por toda la información específica de cada objeto en un orden estricto, como se detalla a continuación:  

  - **Textura del norte:**  
    `NO ./path_to_the_north_texture`  
    - Identificador: `NO`  
    - Ruta a la textura del norte  

  - **Textura del sur:**  
    `SO ./path_to_the_south_texture`  
    - Identificador: `SO`  
    - Ruta a la textura del sur  

  - **Textura del oeste:**  
    `WE ./path_to_the_west_texture`  
    - Identificador: `WE`  
    - Ruta a la textura del oeste  

  - **Textura del este:**  
    `EA ./path_to_the_east_texture`  
    - Identificador: `EA`  
    - Ruta a la textura del este  

  - **Color del suelo:**  
    `F 220,100,0`  
    - Identificador: `F`  
    - Colores **R, G, B** en el rango [0, 255]: `220, 100, 0`  

  - **Color del techo:**  
  `C 225,30,0`  
  - Identificador: `C`  
  - Colores **R, G, B** en el rango [0, 255]: `225, 30, 0`  

- **Ejemplo de la parte obligatoria con una escena minimalista en formato `.cub`:**  
```
NO ./path_to_the_north_texture  
SO ./path_to_the_south_texture  
WE ./path_to_the_west_texture  
EA ./path_to_the_east_texture  
F 220,100,0  
C 225,30,0  

1111111111111111111111111  
1000000000110000000000001  
1011000001110000000000001  
1001000000000000000000001  
111111111011000001110000000000001  
100000000011000001110111111111111  
11110111111111011100000010001  
11110111111111011101010010001  
11000000110101011100000010001  
10000000000000001100000010001  
10000000000000001101010010001  
11000001110101011111011110N0111  
11110111 1110101 101111010001  
11111111 1111111 111111111111  
```

- **Si se encuentra cualquier tipo de error de configuración en el archivo, el programa debe cerrarse correctamente y devolver:**  
  `"Error\n"` seguido de un mensaje de error explícito de tu elección.

**Capítulo V**  
**Parte de Bonificación**  

Las bonificaciones serán evaluadas solo si la parte obligatoria es **PERFECTA**.  
Por **PERFECTA** nos referimos naturalmente a que debe estar completa, que no debe fallar, incluso en casos de errores graves como usos incorrectos, etc.  
Esto significa que, si tu parte obligatoria no obtiene **TODOS** los puntos durante la evaluación, tus bonificaciones serán completamente **IGNORADAS**.  

**Lista de bonificaciones:**  
- Colisiones con las paredes.  
- Sistema de minimapa.  
- Puertas que pueden abrirse y cerrarse.  
- Sprite animado.  
- Rotar el punto de vista con el ratón.  

¡Podrás crear mejores juegos más adelante, no pierdas demasiado tiempo!  

Se te permite usar otras funciones o agregar símbolos en el mapa para completar la parte de bonificación, siempre y cuando su uso esté justificado durante tu evaluación. También se te permite modificar el formato del archivo de escena esperado para adaptarlo a tus necesidades. ¡Sé inteligente!

**Capítulo VII**  
**Entrega y evaluación por pares**  

Entrega tu tarea en tu repositorio de Git como de costumbre. Solo se evaluará el trabajo dentro de tu repositorio durante la defensa. No dudes en verificar dos veces los nombres de tus archivos para asegurarte de que estén correctos.
