Las **promesas en JavaScript** son una forma de manejar operaciones asincrónicas de manera más sencilla que con los tradicionales callbacks. A continuación te explicaré los conceptos clave: desde una petición básica, pasando por anidamiento de promesas, hasta el uso de `async` y `await`.

### 1. **Básico: Promesa con `.then()`**
Una promesa es un objeto que representa un valor que estará disponible ahora, en el futuro, o nunca. Tiene tres estados:
- **Pendiente (pending)**: La operación aún no ha terminado.
- **Resuelta (fulfilled)**: La operación ha terminado exitosamente.
- **Rechazada (rejected)**: La operación ha fallado.

Aquí tienes un ejemplo básico de una promesa:

```javascript
let promesa = new Promise((resolve, reject) => {
  let exito = true;
  if (exito) {
    resolve("¡Operación exitosa!");
  } else {
    reject("¡Operación fallida!");
  }
});

promesa
  .then((resultado) => {
    console.log(resultado);  // Si la promesa se resuelve.
  })
  .catch((error) => {
    console.log(error);  // Si la promesa es rechazada.
  });
```

- **`resolve`**: se llama cuando la operación ha sido exitosa.
- **`reject`**: se llama cuando algo falla.

### 2. **Anidamiento de Promesas**
Es común que una operación asincrónica dependa de otra. Con promesas, podemos "anidar" las operaciones usando varios `.then()`.

```javascript
let promesa1 = new Promise((resolve, reject) => {
  resolve("Primera promesa cumplida");
});

promesa1
  .then((resultado1) => {
    console.log(resultado1); // "Primera promesa cumplida"
    return new Promise((resolve, reject) => {
      resolve("Segunda promesa cumplida");
    });
  })
  .then((resultado2) => {
    console.log(resultado2); // "Segunda promesa cumplida"
  })
  .catch((error) => {
    console.log("Error:", error);
  });
```

En este ejemplo, el segundo `.then()` no se ejecuta hasta que la primera promesa se haya resuelto, creando una secuencia de operaciones asincrónicas.

### 3. **`async` y `await`**
`async` y `await` son una forma más moderna y legible de trabajar con promesas, introducidas en ES2017. Estas palabras clave permiten escribir código asíncrono que se parece más al código síncrono, lo que lo hace más fácil de entender y mantener.

- **`async`**: convierte una función en una función asíncrona que siempre devuelve una promesa.
- **`await`**: pausa la ejecución de la función `async` hasta que la promesa se resuelva.

Aquí tienes un ejemplo con `async` y `await`:

```javascript
// Función que devuelve una promesa
function obtenerDatos() {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve("Datos obtenidos correctamente");
    }, 2000);
  });
}

// Usando async y await
async function procesarDatos() {
  try {
    console.log("Esperando los datos...");
    let resultado = await obtenerDatos(); // Espera a que se resuelva la promesa
    console.log(resultado);  // "Datos obtenidos correctamente"
  } catch (error) {
    console.log("Error:", error);
  }
}

procesarDatos();
```

- **`await obtenerDatos()`**: espera que la promesa devuelta por `obtenerDatos()` se resuelva.
- El código después de `await` no se ejecuta hasta que la promesa haya sido resuelta o rechazada.

### 4. **Manejo de Errores con `try` y `catch`**
Cuando se usan `async` y `await`, los errores se manejan con un bloque `try/catch` en lugar de un `.catch()`:

```javascript
async function obtenerDatosSeguro() {
  try {
    let resultado = await obtenerDatos();
    console.log(resultado);
  } catch (error) {
    console.log("Error al obtener los datos:", error);
  }
}

obtenerDatosSeguro();
```

Este enfoque facilita la captura de errores y mantiene el código más limpio.

---

### Resumen:
1. Las **promesas** manejan código asincrónico y tienen tres estados: pendiente, resuelta y rechazada.
2. **Anidar promesas** es común para realizar múltiples operaciones secuenciales.
3. **`async` y `await`** son una forma más moderna y fácil de leer para trabajar con promesas, permitiendo código asincrónico que parece síncrono.
4. Los errores se pueden manejar con `.catch()` o un bloque `try/catch` al usar `async/await`.

Estas herramientas son esenciales para manejar la asincronía en aplicaciones web, como realizar solicitudes HTTP, operaciones en bases de datos, o manejar eventos del usuario.

---

## MERN Stack.
El **MERN Stack** es un conjunto de tecnologías de desarrollo web que permite construir aplicaciones full-stack de manera eficiente utilizando JavaScript en todas las capas de la aplicación (front-end, back-end, y base de datos). Está compuesto por cuatro tecnologías principales:

1. **MongoDB**: Una base de datos NoSQL orientada a documentos que almacena los datos en formato JSON. Se utiliza para manejar grandes volúmenes de datos no estructurados o semi-estructurados, permitiendo flexibilidad en la organización de la información.

2. **Express.js**: Un framework minimalista de Node.js para el lado del servidor que facilita la creación de APIs y el manejo de solicitudes HTTP de manera sencilla y estructurada.

3. **React.js**: Una biblioteca de JavaScript desarrollada por Facebook que se usa para crear interfaces de usuario interactivas y dinámicas en el front-end. React permite construir componentes reutilizables y gestionar el estado de la aplicación de manera eficiente.

4. **Node.js**: Un entorno de ejecución para JavaScript que permite usar este lenguaje en el lado del servidor, permitiendo la creación de aplicaciones escalables y de alto rendimiento.

### ¿Cómo funciona el desarrollo con MERN?
El flujo típico de desarrollo en MERN es el siguiente:

- **Front-end (React)**: React se encarga de la interfaz de usuario, interactuando con el usuario y realizando llamadas a las APIs para obtener o enviar datos. Por ejemplo, cuando un usuario envía un formulario, React envía los datos a través de una solicitud HTTP.
  
- **Back-end (Node.js + Express.js)**: El servidor Express recibe las solicitudes del front-end, realiza la lógica de negocio y se comunica con la base de datos para almacenar o recuperar información. Node.js permite manejar múltiples conexiones de manera eficiente gracias a su modelo de I/O no bloqueante.

- **Base de datos (MongoDB)**: MongoDB almacena los datos que el back-end gestiona. Como es una base de datos NoSQL, los datos se almacenan en colecciones y documentos, en lugar de en tablas y filas como en una base de datos relacional tradicional.

### Ejemplo de flujo MERN Stack:
1. Un usuario visita una aplicación construida con React, que carga una página donde puede ver y agregar comentarios.
2. React realiza una solicitud HTTP al servidor Express para obtener los comentarios existentes desde la base de datos MongoDB.
3. El servidor Express consulta MongoDB y devuelve los datos a React.
4. El usuario agrega un nuevo comentario en el front-end, que React envía al servidor Express.
5. Express valida y guarda el nuevo comentario en MongoDB.

### Ventajas del MERN Stack:
- **Un solo lenguaje**: Usar JavaScript en todo el stack simplifica el desarrollo, ya que los desarrolladores no necesitan aprender varios lenguajes para diferentes capas de la aplicación.
- **Componentización en React**: Permite crear interfaces interactivas y reutilizables de manera modular.
- **Ecosistema open-source**: Todas las tecnologías del stack son de código abierto, lo que facilita su adopción y mejora constante por la comunidad.

El MERN Stack es una opción popular para construir aplicaciones web modernas, desde proyectos pequeños hasta aplicaciones de gran escala debido a su flexibilidad y escalabilidad.
