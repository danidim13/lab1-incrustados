# lab1-incrustados

1. Configurar el CAD.
  - Buscar en la hoja de datos del Micro.
  - Leer valores de micrófono.
  - Leer valores del sensore de luz.

2. Cómo usar el sensor de luz.
  - Buscar en la hoja de datos del sensor del shield.

3. Integrar todo.

## Especificaciones y requerimientos

 - Controlar hasta 3 lamparas (5, 10 y 15 W). --> Debe haber una previsión en el código (como un #define o una constante) para indicar cuantas salidas son necesarias.
 - El sistema tiene tres estados: Reset (recién encendido), Encendido y Apagado.
 - Se debe definir un valor de umbral de la iluminación, para distinguir entre <b>día</b> y <b>noche</b>.
 - En el estado Reset:
   * Las lámparas parpadean 3 veces.
   * Si iluminación == día --> Apagado.
   * Si iluminación == noche --> Encendido.
 - Hay 2 posibles transiciones de Apagado --> Encendido: que se de la <b>condición de encendido</b> o que se presione el <b>botón</b>. 
 - Condición de encendido:
   * Lámpara apagada.
   * Iluminación == noche.
   * Nivel de sonido ~10% mayor que promedio de los últimos 5 segundos, por 1 segundo. 
 - Hay 2 posibles transiciones de Encendido --> Apagado: que transcurran <b>30 minutos del encendido</b> o que se presione el <b>botón</b>.

Se podría hacer como un diagrama de transición de estados o sino un diagrama de flujo para el reporte.

## Hardware

Para armar todo el sistema se tiene que configurar correctamente:

 - [x] Botón
 - [ ] Sistema de reloj
 - [ ] Timer
 - [ ] Convertidor A/D
 - [ ] LED(s) o pines de salida (aclarar con el profe?)

