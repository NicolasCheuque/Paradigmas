#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

// Niveles de la Taxonomía de Bloom
enum NivelBloom {
  RECORDAR = 1,   // Remembering - Nivel más básico (recordar información)
  COMPRENDER = 2, // Understanding - Comprender significados
  APLICAR = 3,    // Applying - Usar conocimiento en situaciones nuevas
  ANALIZAR = 4,   // Analyzing - Descomponer información en partes
  EVALUAR = 5,    // Evaluating - Juzgar valor de información
  CREAR = 6       // Creating - Nivel más alto (crear algo nuevo)
};

// Clase base Pregunta - Define la estructura común para todos los tipos de
// preguntas
class Pregunta {
protected:
  int id;             // Identificador único
  std::string texto;  // Texto de la pregunta
  int nivelBloom;     // Nivel según taxonomía de Bloom
  int tiempoEstimado; // Tiempo estimado en minutos
  int anio;           // Año al que pertenece la pregunta

public:
  // Constructor - Inicializa los atributos básicos de una pregunta
  Pregunta(int id, const std::string &texto, int nivelBloom, int tiempoEstimado,
           int anio = 0)
      : id(id), texto(texto), nivelBloom(nivelBloom),
        tiempoEstimado(tiempoEstimado), anio(anio) {}

  // Destructor virtual - Permite polimorfismo correcto al eliminar objetos
  virtual ~Pregunta() = default;

  // Getters - Métodos para obtener los valores de los atributos
  int getId() const { return id; }
  std::string getTexto() const { return texto; }
  int getNivelBloom() const { return nivelBloom; }
  int getTiempoEstimado() const { return tiempoEstimado; }
  int getAnio() const { return anio; }

  // Setters - Métodos para modificar los valores de los atributos
  void setTexto(const std::string &nuevoTexto) { texto = nuevoTexto; }
  void setNivelBloom(int nivel) { nivelBloom = nivel; }
  void setTiempoEstimado(int tiempo) { tiempoEstimado = tiempo; }
  void setAnio(int nuevoAnio) { anio = nuevoAnio; }

  // Método virtual para obtener el tipo de pregunta - Será sobrescrito por
  // clases derivadas
  virtual std::string getTipo() const { return "Base"; }

  // Método para mostrar la información de la pregunta
  virtual void mostrar() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Pregunta: " << texto << "\n";
    std::cout << "Nivel de Bloom: " << getNombreNivelBloom(nivelBloom) << "\n";
    std::cout << "Tiempo Estimado: " << tiempoEstimado << " minutos\n";
    if (anio > 0) {
      std::cout << "Año: " << anio << "\n";
    }
  }

  // Método estático para obtener el nombre del nivel de Bloom
  static std::string getNombreNivelBloom(int nivel) {
    switch (nivel) {
    case RECORDAR:
      return "Recordar";
    case COMPRENDER:
      return "Comprender";
    case APLICAR:
      return "Aplicar";
    case ANALIZAR:
      return "Analizar";
    case EVALUAR:
      return "Evaluar";
    case CREAR:
      return "Crear";
    default:
      return "Desconocido";
    }
  }
};

// Clase para preguntas de opción múltiple - Hereda de Pregunta
class PreguntaOpcionMultiple : public Pregunta {
private:
  std::vector<std::string> opciones; // Lista de opciones disponibles
  int opcionCorrecta;                // Índice de la opción correcta (0-based)

public:
  // Constructor
  PreguntaOpcionMultiple(int id, const std::string &texto, int nivelBloom,
                         int tiempoEstimado,
                         const std::vector<std::string> &opciones,
                         int opcionCorrecta, int anio = 0)
      : Pregunta(id, texto, nivelBloom, tiempoEstimado, anio),
        opciones(opciones), opcionCorrecta(opcionCorrecta) {}

  // Getters
  std::vector<std::string> getOpciones() const { return opciones; }
  int getOpcionCorrecta() const { return opcionCorrecta; }

  // Setters
  void setOpciones(const std::vector<std::string> &nuevasOpciones) {
    opciones = nuevasOpciones;
  }
  void setOpcionCorrecta(int opcion) { opcionCorrecta = opcion; }

  // Sobrescritura del método getTipo
  std::string getTipo() const override { return "Opción Múltiple"; }

  // Sobrescritura del método mostrar
  void mostrar() const override {
    Pregunta::mostrar();
    std::cout << "Tipo: Opción Múltiple\n";
    std::cout << "Opciones:\n";
    for (size_t i = 0; i < opciones.size(); ++i) {
      std::cout << "  " << (i + 1) << ". " << opciones[i] << "\n";
    }
    std::cout << "Opción Correcta: " << (opcionCorrecta + 1) << "\n";
  }
};

// Clase para preguntas de verdadero/falso - Hereda de Pregunta
class PreguntaVerdaderoFalso : public Pregunta {
private:
  bool respuestaCorrecta; // true = Verdadero, false = Falso

public:
  // Constructor
  PreguntaVerdaderoFalso(int id, const std::string &texto, int nivelBloom,
                         int tiempoEstimado, bool respuestaCorrecta,
                         int anio = 0)
      : Pregunta(id, texto, nivelBloom, tiempoEstimado, anio),
        respuestaCorrecta(respuestaCorrecta) {}

  // Getters y setters
  bool getRespuestaCorrecta() const { return respuestaCorrecta; }
  void setRespuestaCorrecta(bool respuesta) { respuestaCorrecta = respuesta; }

  // Sobrescritura del método getTipo
  std::string getTipo() const override { return "Verdadero/Falso"; }

  // Sobrescritura del método mostrar
  void mostrar() const override {
    Pregunta::mostrar();
    std::cout << "Tipo: Verdadero/Falso\n";
    std::cout << "Respuesta Correcta: "
              << (respuestaCorrecta ? "Verdadero" : "Falso") << "\n";
  }
};

// Clase para preguntas de emparejamiento - Hereda de Pregunta
class PreguntaEmparejamiento : public Pregunta {
private:
  std::vector<std::string>
      elementosIzquierda; // Elementos a emparejar (lado izquierdo)
  std::vector<std::string>
      elementosDerecha; // Elementos a emparejar (lado derecho)
  std::vector<int> emparejamientosCorrectos; // Índices que indican el
                                             // emparejamiento correcto

public:
  // Constructor
  PreguntaEmparejamiento(int id, const std::string &texto, int nivelBloom,
                         int tiempoEstimado,
                         const std::vector<std::string> &elementosIzquierda,
                         const std::vector<std::string> &elementosDerecha,
                         const std::vector<int> &emparejamientosCorrectos,
                         int anio = 0)
      : Pregunta(id, texto, nivelBloom, tiempoEstimado, anio),
        elementosIzquierda(elementosIzquierda),
        elementosDerecha(elementosDerecha),
        emparejamientosCorrectos(emparejamientosCorrectos) {}

  // Getters
  std::vector<std::string> getElementosIzquierda() const {
    return elementosIzquierda;
  }
  std::vector<std::string> getElementosDerecha() const {
    return elementosDerecha;
  }
  std::vector<int> getEmparejamientosCorrectos() const {
    return emparejamientosCorrectos;
  }

  // Setters
  void setElementosIzquierda(const std::vector<std::string> &elementos) {
    elementosIzquierda = elementos;
  }
  void setElementosDerecha(const std::vector<std::string> &elementos) {
    elementosDerecha = elementos;
  }
  void setEmparejamientosCorrectos(const std::vector<int> &emparejamientos) {
    emparejamientosCorrectos = emparejamientos;
  }

  // Sobrescritura del método getTipo
  std::string getTipo() const override { return "Emparejamiento"; }

  // Sobrescritura del método mostrar
  void mostrar() const override {
    Pregunta::mostrar();
    std::cout << "Tipo: Emparejamiento\n";
    std::cout << "Elementos Izquierda:\n";
    for (size_t i = 0; i < elementosIzquierda.size(); ++i) {
      std::cout << "  " << (i + 1) << ". " << elementosIzquierda[i] << "\n";
    }
    std::cout << "Elementos Derecha:\n";
    for (size_t i = 0; i < elementosDerecha.size(); ++i) {
      std::cout << "  " << (char)('A' + i) << ". " << elementosDerecha[i]
                << "\n";
    }
    std::cout << "Emparejamientos Correctos:\n";
    for (size_t i = 0; i < emparejamientosCorrectos.size(); ++i) {
      std::cout << "  " << (i + 1) << " -> "
                << (char)('A' + emparejamientosCorrectos[i]) << "\n";
    }
  }
};

// Gestor de Preguntas - Maneja la colección de preguntas y operaciones CRUD
class GestorPreguntas {
private:
  std::vector<std::unique_ptr<Pregunta>>
      preguntas;       // Almacena todas las preguntas
  int siguienteId = 1; // ID para la siguiente pregunta

  // Mapas para validación de preguntas repetidas
  std::map<int, std::set<std::string>> preguntasPorAnio; // Preguntas por año
  std::map<std::string, int> textoAPreguntaId;           // Mapeo de texto a ID

  // Verifica si una pregunta es similar a otra existente
  bool esPreguntaSimilar(const std::string &texto, int anio) {
    // Verificar si la pregunta existe exactamente en el mismo año
    if (anio > 0 && preguntasPorAnio.count(anio) > 0) {
      if (preguntasPorAnio[anio].count(texto) > 0) {
        return true;
      }
    }

    // Verificar si la pregunta existe en el año anterior
    if (anio > 1 && preguntasPorAnio.count(anio - 1) > 0) {
      if (preguntasPorAnio[anio - 1].count(texto) > 0) {
        return true;
      }
    }

    // Verificar similitud con otras preguntas (implementación simplificada)
    if (textoAPreguntaId.count(texto) > 0) {
      return true;
    }

    return false;
  }

public:
  // Método para agregar una pregunta con validación
  int agregarPregunta(std::unique_ptr<Pregunta> pregunta) {
    std::string texto = pregunta->getTexto();
    int anio = pregunta->getAnio();

    // Validar si la pregunta es similar a otra existente
    if (esPreguntaSimilar(texto, anio)) {
      return -1; // Indica que la pregunta es similar a otra existente
    }

    // Asignar un nuevo ID y agregar la pregunta
    int id = siguienteId++;
    pregunta->setAnio(anio);

    // Registrar la pregunta en los mapas de validación
    if (anio > 0) {
      preguntasPorAnio[anio].insert(texto);
    }
    textoAPreguntaId[texto] = id;

    preguntas.push_back(std::move(pregunta));
    return id;
  }

  // Método para actualizar una pregunta existente
  bool actualizarPregunta(int id,
                          std::unique_ptr<Pregunta> preguntaActualizada) {
    auto it = std::find_if(
        preguntas.begin(), preguntas.end(),
        [id](const std::unique_ptr<Pregunta> &p) { return p->getId() == id; });

    if (it != preguntas.end()) {
      // Eliminar la pregunta anterior de los mapas de validación
      std::string textoAnterior = (*it)->getTexto();
      int anioAnterior = (*it)->getAnio();

      if (anioAnterior > 0) {
        preguntasPorAnio[anioAnterior].erase(textoAnterior);
      }
      textoAPreguntaId.erase(textoAnterior);

      // Validar si la nueva versión es similar a otra existente (que no sea la
      // misma)
      std::string nuevoTexto = preguntaActualizada->getTexto();
      int nuevoAnio = preguntaActualizada->getAnio();

      if (nuevoTexto != textoAnterior &&
          esPreguntaSimilar(nuevoTexto, nuevoAnio)) {
        // Volver a registrar la pregunta anterior para mantener consistencia
        if (anioAnterior > 0) {
          preguntasPorAnio[anioAnterior].insert(textoAnterior);
        }
        textoAPreguntaId[textoAnterior] = id;
        return false; // La actualización falló por similitud
      }

      // Registrar la nueva versión en los mapas de validación
      if (nuevoAnio > 0) {
        preguntasPorAnio[nuevoAnio].insert(nuevoTexto);
      }
      textoAPreguntaId[nuevoTexto] = id;

      // Actualizar la pregunta
      *it = std::move(preguntaActualizada);
      return true;
    }
    return false;
  }

  // Método para eliminar una pregunta
  bool eliminarPregunta(int id) {
    auto it = std::find_if(
        preguntas.begin(), preguntas.end(),
        [id](const std::unique_ptr<Pregunta> &p) { return p->getId() == id; });

    if (it != preguntas.end()) {
      // Eliminar la pregunta de los mapas de validación
      std::string texto = (*it)->getTexto();
      int anio = (*it)->getAnio();

      if (anio > 0) {
        preguntasPorAnio[anio].erase(texto);
      }
      textoAPreguntaId.erase(texto);

      // Eliminar la pregunta
      preguntas.erase(it);
      return true;
    }
    return false;
  }

  // Método para obtener una pregunta por su ID
  Pregunta *getPregunta(int id) {
    auto it = std::find_if(
        preguntas.begin(), preguntas.end(),
        [id](const std::unique_ptr<Pregunta> &p) { return p->getId() == id; });

    if (it != preguntas.end()) {
      return it->get();
    }
    return nullptr;
  }

  // Método para buscar preguntas por nivel de Bloom
  std::vector<Pregunta *> buscarPorNivelBloom(int nivel) {
    std::vector<Pregunta *> resultado;
    for (const auto &p : preguntas) {
      if (p->getNivelBloom() == nivel) {
        resultado.push_back(p.get());
      }
    }
    return resultado;
  }

  // Método para buscar preguntas por año
  std::vector<Pregunta *> buscarPorAnio(int anio) {
    std::vector<Pregunta *> resultado;
    for (const auto &p : preguntas) {
      if (p->getAnio() == anio) {
        resultado.push_back(p.get());
      }
    }
    return resultado;
  }

  // Método para calcular el tiempo total estimado
  int calcularTiempoTotal() {
    int tiempoTotal = 0;
    for (const auto &p : preguntas) {
      tiempoTotal += p->getTiempoEstimado();
    }
    return tiempoTotal;
  }

  // Método para obtener todas las preguntas
  std::vector<Pregunta *> getTodasLasPreguntas() {
    std::vector<Pregunta *> resultado;
    for (const auto &p : preguntas) {
      resultado.push_back(p.get());
    }
    return resultado;
  }
};

// Interfaz de Usuario - Maneja la interacción con el usuario
class InterfazUsuario {
private:
  GestorPreguntas gestor; // Gestor de preguntas para operaciones CRUD

  // Método para limpiar la pantalla
  void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    (void)system("clear"); // Ignorar valor de retorno
#endif
  }

  // Método para esperar a que el usuario presione Enter
  void esperarEnter() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Método para obtener entrada numérica validada
  int obtenerEntradaInt(const std::string &mensaje, int min, int max) {
    int entrada;
    while (true) {
      std::cout << mensaje;
      if (std::cin >> entrada) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (entrada >= min && entrada <= max) {
          return entrada;
        }
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::cout << "Entrada inválida. Por favor ingrese un número entre " << min
                << " y " << max << ".\n";
    }
  }

  // Método para obtener entrada de texto
  std::string obtenerEntradaString(const std::string &mensaje) {
    std::string entrada;
    std::cout << mensaje;
    std::getline(std::cin, entrada);
    return entrada;
  }

public:
  // Método para mostrar el menú principal
  void mostrarMenu() {
    limpiarPantalla();
    std::cout << "===== Sistema de Gestión de Preguntas basado en la Taxonomía "
                 "de Bloom =====\n";
    std::cout << "1. Crear una nueva pregunta\n";
    std::cout << "2. Actualizar una pregunta existente\n";
    std::cout << "3. Eliminar una pregunta\n";
    std::cout << "4. Buscar preguntas por nivel de Bloom\n";
    std::cout << "5. Buscar preguntas por año\n";
    std::cout << "6. Mostrar todas las preguntas\n";
    std::cout << "7. Mostrar tiempo estimado de finalización del test\n";
    std::cout << "0. Salir\n";
    std::cout << "Ingrese su opción: ";
  }

  // Método para manejar la entrada del usuario
  void manejarEntradaUsuario() {
    bool ejecutando = true;
    while (ejecutando) {
      mostrarMenu();
      int opcion = obtenerEntradaInt("", 0, 7);

      switch (opcion) {
      case 0:
        ejecutando = false;
        break;
      case 1:
        crearPregunta();
        break;
      case 2:
        actualizarPregunta();
        break;
      case 3:
        eliminarPregunta();
        break;
      case 4:
        buscarPreguntas();
        break;
      case 5:
        buscarPreguntasPorAnio();
        break;
      case 6:
        mostrarTodasLasPreguntas();
        break;
      case 7:
        mostrarTiempoTotal();
        break;
      }
    }
  }

  // Método para crear una nueva pregunta
  void crearPregunta() {
    limpiarPantalla();
    std::cout << "===== Crear una Nueva Pregunta =====\n";
    std::cout << "Seleccione el tipo de pregunta:\n";
    std::cout << "1. Opción Múltiple\n";
    std::cout << "2. Verdadero/Falso\n";
    std::cout << "3. Emparejamiento\n";

    int tipo = obtenerEntradaInt("Ingrese el tipo (1-3): ", 1, 3);
    std::string texto =
        obtenerEntradaString("Ingrese el texto de la pregunta: ");

    // Solicitar el año de la pregunta (para validación)
    int anio = obtenerEntradaInt(
        "Ingrese el año de la pregunta (0 si no aplica): ", 0, 2100);

    std::cout << "Niveles de la Taxonomía de Bloom:\n";
    std::cout << "1. Recordar - Nivel más básico (recordar información)\n";
    std::cout << "2. Comprender - Comprender significados\n";
    std::cout << "3. Aplicar - Usar conocimiento en situaciones nuevas\n";
    std::cout << "4. Analizar - Descomponer información en partes\n";
    std::cout << "5. Evaluar - Juzgar valor de información\n";
    std::cout << "6. Crear - Nivel más alto (crear algo nuevo)\n";

    int nivelBloom =
        obtenerEntradaInt("Ingrese el nivel de Bloom (1-6): ", 1, 6);
    int tiempoEstimado = obtenerEntradaInt(
        "Ingrese el tiempo estimado para responder (en minutos): ", 1, 60);

    std::unique_ptr<Pregunta> pregunta;

    switch (tipo) {
    case 1: { // Opción Múltiple
      int numOpciones =
          obtenerEntradaInt("Ingrese el número de opciones (2-6): ", 2, 6);
      std::vector<std::string> opciones;

      for (int i = 0; i < numOpciones; ++i) {
        std::string opcion = obtenerEntradaString("Ingrese la opción " +
                                                  std::to_string(i + 1) + ": ");
        opciones.push_back(opcion);
      }

      int opcionCorrecta =
          obtenerEntradaInt("Ingrese la opción correcta (1-" +
                                std::to_string(numOpciones) + "): ",
                            1, numOpciones) -
          1;

      pregunta = std::make_unique<PreguntaOpcionMultiple>(
          0, texto, nivelBloom, tiempoEstimado, opciones, opcionCorrecta, anio);
      break;
    }
    case 2: { // Verdadero/Falso
      int respuesta = obtenerEntradaInt(
          "Ingrese la respuesta correcta (1 para Verdadero, 0 para Falso): ", 0,
          1);
      pregunta = std::make_unique<PreguntaVerdaderoFalso>(
          0, texto, nivelBloom, tiempoEstimado, respuesta == 1, anio);
      break;
    }
    case 3: { // Emparejamiento
      int numPares = obtenerEntradaInt(
          "Ingrese el número de pares para emparejar (2-6): ", 2, 6);
      std::vector<std::string> elementosIzquierda;
      std::vector<std::string> elementosDerecha;
      std::vector<int> emparejamientosCorrectos;

      for (int i = 0; i < numPares; ++i) {
        std::string elementoIzquierda = obtenerEntradaString(
            "Ingrese el elemento izquierdo " + std::to_string(i + 1) + ": ");
        elementosIzquierda.push_back(elementoIzquierda);
      }

      for (int i = 0; i < numPares; ++i) {
        std::string elementoDerecha = obtenerEntradaString(
            "Ingrese el elemento derecho " + std::to_string(i + 1) + ": ");
        elementosDerecha.push_back(elementoDerecha);
      }

      for (int i = 0; i < numPares; ++i) {
        int emparejamiento =
            obtenerEntradaInt("Ingrese el elemento derecho que coincide con el "
                              "elemento izquierdo " +
                                  std::to_string(i + 1) + " (1-" +
                                  std::to_string(numPares) + "): ",
                              1, numPares) -
            1;
        emparejamientosCorrectos.push_back(emparejamiento);
      }

      pregunta = std::make_unique<PreguntaEmparejamiento>(
          0, texto, nivelBloom, tiempoEstimado, elementosIzquierda,
          elementosDerecha, emparejamientosCorrectos, anio);
      break;
    }
    }

    int id = gestor.agregarPregunta(std::move(pregunta));
    if (id > 0) {
      std::cout << "Pregunta agregada exitosamente con ID: " << id << "\n";
    } else {
      std::cout << "Error: La pregunta es similar a otra existente en el mismo "
                   "año o año anterior.\n";
    }

    esperarEnter();
  }

  // Método para actualizar una pregunta existente
  void actualizarPregunta() {
    limpiarPantalla();
    std::cout << "===== Actualizar una Pregunta =====\n";

    auto todasLasPreguntas = gestor.getTodasLasPreguntas();
    if (todasLasPreguntas.empty()) {
      std::cout << "No hay preguntas disponibles para actualizar.\n";
      esperarEnter();
      return;
    }

    std::cout << "Preguntas disponibles:\n";
    for (const auto &p : todasLasPreguntas) {
      std::cout << "ID: " << p->getId() << " - " << p->getTexto().substr(0, 50)
                << (p->getTexto().length() > 50 ? "..." : "") << " ("
                << p->getTipo() << ")"
                << (p->getAnio() > 0 ? " - Año: " + std::to_string(p->getAnio())
                                     : "")
                << "\n";
    }

    int id = obtenerEntradaInt("Ingrese el ID de la pregunta a actualizar: ", 0,
                               std::numeric_limits<int>::max());
    Pregunta *pregunta = gestor.getPregunta(id);

    if (!pregunta) {
      std::cout << "Pregunta no encontrada.\n";
      esperarEnter();
      return;
    }

    std::cout << "Detalles actuales de la pregunta:\n";
    pregunta->mostrar();

    std::string texto =
        obtenerEntradaString("Ingrese el nuevo texto de la pregunta (deje "
                             "vacío para mantener el actual): ");
    if (!texto.empty()) {
      pregunta->setTexto(texto);
    }

    // Solicitar el año de la pregunta (para validación)
    int anioActual = pregunta->getAnio();
    int anio = obtenerEntradaInt(
        "Ingrese el nuevo año de la pregunta (0 para mantener " +
            (anioActual > 0 ? std::to_string(anioActual) : "sin año") + "): ",
        0, 2100);
    if (anio > 0) {
      pregunta->setAnio(anio);
    } else if (anio == 0 && anioActual > 0) {
      // Mantener el año actual
    } else {
      pregunta->setAnio(0);
    }

    std::cout << "Niveles de la Taxonomía de Bloom:\n";
    std::cout << "1. Recordar\n";
    std::cout << "2. Comprender\n";
    std::cout << "3. Aplicar\n";
    std::cout << "4. Analizar\n";
    std::cout << "5. Evaluar\n";
    std::cout << "6. Crear\n";

    int nivelBloom = obtenerEntradaInt(
        "Ingrese el nuevo nivel de Bloom (1-6, 0 para mantener el actual): ", 0,
        6);
    if (nivelBloom != 0) {
      pregunta->setNivelBloom(nivelBloom);
    }

    int tiempoEstimado =
        obtenerEntradaInt("Ingrese el nuevo tiempo estimado (en minutos, 0 "
                          "para mantener el actual): ",
                          0, 60);
    if (tiempoEstimado != 0) {
      pregunta->setTiempoEstimado(tiempoEstimado);
    }

    // Actualizaciones específicas según el tipo
    if (pregunta->getTipo() == "Opción Múltiple") {
      PreguntaOpcionMultiple *pom =
          dynamic_cast<PreguntaOpcionMultiple *>(pregunta);
      if (pom) {
        int actualizarOpciones = obtenerEntradaInt(
            "¿Actualizar opciones? (1 para Sí, 0 para No): ", 0, 1);
        if (actualizarOpciones) {
          auto opcionesActuales = pom->getOpciones();
          int numOpciones =
              obtenerEntradaInt("Ingrese el número de opciones (2-6): ", 2, 6);
          std::vector<std::string> opciones;

          for (int i = 0; i < numOpciones; ++i) {
            std::string opcionPredeterminada =
                i < opcionesActuales.size() ? opcionesActuales[i] : "";
            std::string opcion = obtenerEntradaString(
                "Ingrese la opción " + std::to_string(i + 1) + " [" +
                opcionPredeterminada + "]: ");
            opciones.push_back(opcion.empty() ? opcionPredeterminada : opcion);
          }

          pom->setOpciones(opciones);

          int opcionCorrecta =
              obtenerEntradaInt("Ingrese la opción correcta (1-" +
                                    std::to_string(numOpciones) + "): ",
                                1, numOpciones) -
              1;
          pom->setOpcionCorrecta(opcionCorrecta);
        }
      }
    } else if (pregunta->getTipo() == "Verdadero/Falso") {
      PreguntaVerdaderoFalso *pvf =
          dynamic_cast<PreguntaVerdaderoFalso *>(pregunta);
      if (pvf) {
        int actualizarRespuesta = obtenerEntradaInt(
            "¿Actualizar respuesta correcta? (1 para Sí, 0 para No): ", 0, 1);
        if (actualizarRespuesta) {
          int respuesta = obtenerEntradaInt("Ingrese la respuesta correcta (1 "
                                            "para Verdadero, 0 para Falso): ",
                                            0, 1);
          pvf->setRespuestaCorrecta(respuesta == 1);
        }
      }
    } else if (pregunta->getTipo() == "Emparejamiento") {
      PreguntaEmparejamiento *pe =
          dynamic_cast<PreguntaEmparejamiento *>(pregunta);
      if (pe) {
        int actualizarElementos = obtenerEntradaInt(
            "¿Actualizar elementos de emparejamiento? (1 para Sí, 0 para No): ",
            0, 1);
        if (actualizarElementos) {
          auto elementosIzquierdaActuales = pe->getElementosIzquierda();
          auto elementosDerechaActuales = pe->getElementosDerecha();

          int numPares = obtenerEntradaInt(
              "Ingrese el número de pares para emparejar (2-6): ", 2, 6);
          std::vector<std::string> elementosIzquierda;
          std::vector<std::string> elementosDerecha;
          std::vector<int> emparejamientosCorrectos;

          for (int i = 0; i < numPares; ++i) {
            std::string predeterminadoIzquierda =
                i < elementosIzquierdaActuales.size()
                    ? elementosIzquierdaActuales[i]
                    : "";
            std::string elementoIzquierda = obtenerEntradaString(
                "Ingrese el elemento izquierdo " + std::to_string(i + 1) +
                " [" + predeterminadoIzquierda + "]: ");
            elementosIzquierda.push_back(elementoIzquierda.empty()
                                             ? predeterminadoIzquierda
                                             : elementoIzquierda);
          }

          for (int i = 0; i < numPares; ++i) {
            std::string predeterminadoDerecha =
                i < elementosDerechaActuales.size()
                    ? elementosDerechaActuales[i]
                    : "";
            std::string elementoDerecha = obtenerEntradaString(
                "Ingrese el elemento derecho " + std::to_string(i + 1) + " [" +
                predeterminadoDerecha + "]: ");
            elementosDerecha.push_back(elementoDerecha.empty()
                                           ? predeterminadoDerecha
                                           : elementoDerecha);
          }

          for (int i = 0; i < numPares; ++i) {
            int emparejamiento =
                obtenerEntradaInt("Ingrese el elemento derecho que coincide "
                                  "con el elemento izquierdo " +
                                      std::to_string(i + 1) + " (1-" +
                                      std::to_string(numPares) + "): ",
                                  1, numPares) -
                1;
            emparejamientosCorrectos.push_back(emparejamiento);
          }

          pe->setElementosIzquierda(elementosIzquierda);
          pe->setElementosDerecha(elementosDerecha);
          pe->setEmparejamientosCorrectos(emparejamientosCorrectos);
        }
      }
    }

    // Crear una copia de la pregunta actualizada para pasarla al gestor
    std::unique_ptr<Pregunta> preguntaActualizada;
    if (pregunta->getTipo() == "Opción Múltiple") {
      PreguntaOpcionMultiple *pom =
          dynamic_cast<PreguntaOpcionMultiple *>(pregunta);
      preguntaActualizada = std::make_unique<PreguntaOpcionMultiple>(
          id, pom->getTexto(), pom->getNivelBloom(), pom->getTiempoEstimado(),
          pom->getOpciones(), pom->getOpcionCorrecta(), pom->getAnio());
    } else if (pregunta->getTipo() == "Verdadero/Falso") {
      PreguntaVerdaderoFalso *pvf =
          dynamic_cast<PreguntaVerdaderoFalso *>(pregunta);
      preguntaActualizada = std::make_unique<PreguntaVerdaderoFalso>(
          id, pvf->getTexto(), pvf->getNivelBloom(), pvf->getTiempoEstimado(),
          pvf->getRespuestaCorrecta(), pvf->getAnio());
    } else if (pregunta->getTipo() == "Emparejamiento") {
      PreguntaEmparejamiento *pe =
          dynamic_cast<PreguntaEmparejamiento *>(pregunta);
      preguntaActualizada = std::make_unique<PreguntaEmparejamiento>(
          id, pe->getTexto(), pe->getNivelBloom(), pe->getTiempoEstimado(),
          pe->getElementosIzquierda(), pe->getElementosDerecha(),
          pe->getEmparejamientosCorrectos(), pe->getAnio());
    }

    if (gestor.actualizarPregunta(id, std::move(preguntaActualizada))) {
      std::cout << "Pregunta actualizada exitosamente.\n";
    } else {
      std::cout << "Error: No se pudo actualizar la pregunta. Puede ser "
                   "similar a otra existente.\n";
    }

    esperarEnter();
  }

  // Método para eliminar una pregunta
  void eliminarPregunta() {
    limpiarPantalla();
    std::cout << "===== Eliminar una Pregunta =====\n";

    auto todasLasPreguntas = gestor.getTodasLasPreguntas();
    if (todasLasPreguntas.empty()) {
      std::cout << "No hay preguntas disponibles para eliminar.\n";
      esperarEnter();
      return;
    }

    std::cout << "Preguntas disponibles:\n";
    for (const auto &p : todasLasPreguntas) {
      std::cout << "ID: " << p->getId() << " - " << p->getTexto().substr(0, 50)
                << (p->getTexto().length() > 50 ? "..." : "") << " ("
                << p->getTipo() << ")"
                << (p->getAnio() > 0 ? " - Año: " + std::to_string(p->getAnio())
                                     : "")
                << "\n";
    }

    int id = obtenerEntradaInt("Ingrese el ID de la pregunta a eliminar: ", 0,
                               std::numeric_limits<int>::max());

    if (gestor.eliminarPregunta(id)) {
      std::cout << "Pregunta eliminada exitosamente.\n";
    } else {
      std::cout << "Pregunta no encontrada.\n";
    }

    esperarEnter();
  }

  // Método para buscar preguntas por nivel de Bloom
  void buscarPreguntas() {
    limpiarPantalla();
    std::cout << "===== Buscar Preguntas por Nivel de Bloom =====\n";

    std::cout << "Niveles de la Taxonomía de Bloom:\n";
    std::cout << "1. Recordar\n";
    std::cout << "2. Comprender\n";
    std::cout << "3. Aplicar\n";
    std::cout << "4. Analizar\n";
    std::cout << "5. Evaluar\n";
    std::cout << "6. Crear\n";

    int nivelBloom = obtenerEntradaInt(
        "Ingrese el nivel de Bloom para buscar (1-6): ", 1, 6);

    auto preguntas = gestor.buscarPorNivelBloom(nivelBloom);

    if (preguntas.empty()) {
      std::cout << "No se encontraron preguntas para el nivel de Bloom: "
                << Pregunta::getNombreNivelBloom(nivelBloom) << "\n";
    } else {
      std::cout << "Se encontraron " << preguntas.size()
                << " preguntas para el nivel de Bloom: "
                << Pregunta::getNombreNivelBloom(nivelBloom) << "\n\n";

      for (const auto &p : preguntas) {
        p->mostrar();
        std::cout << "------------------------\n";
      }
    }

    esperarEnter();
  }

  // Método para buscar preguntas por año
  void buscarPreguntasPorAnio() {
    limpiarPantalla();
    std::cout << "===== Buscar Preguntas por Año =====\n";

    int anio = obtenerEntradaInt("Ingrese el año para buscar: ", 0, 2100);

    auto preguntas = gestor.buscarPorAnio(anio);

    if (preguntas.empty()) {
      std::cout << "No se encontraron preguntas para el año: " << anio << "\n";
    } else {
      std::cout << "Se encontraron " << preguntas.size()
                << " preguntas para el año: " << anio << "\n\n";

      for (const auto &p : preguntas) {
        p->mostrar();
        std::cout << "------------------------\n";
      }
    }

    esperarEnter();
  }

  // Método para mostrar todas las preguntas
  void mostrarTodasLasPreguntas() {
    limpiarPantalla();
    std::cout << "===== Todas las Preguntas =====\n";

    auto preguntas = gestor.getTodasLasPreguntas();

    if (preguntas.empty()) {
      std::cout << "No hay preguntas disponibles.\n";
    } else {
      std::cout << "Total de preguntas: " << preguntas.size() << "\n\n";

      for (const auto &p : preguntas) {
        p->mostrar();
        std::cout << "------------------------\n";
      }
    }

    esperarEnter();
  }

  // Método para mostrar el tiempo total estimado
  void mostrarTiempoTotal() {
    limpiarPantalla();
    std::cout << "===== Tiempo Estimado de Finalización del Test =====\n";

    int tiempoTotal = gestor.calcularTiempoTotal();

    std::cout << "Tiempo total estimado: " << tiempoTotal << " minutos";
    if (tiempoTotal >= 60) {
      int horas = tiempoTotal / 60;
      int minutos = tiempoTotal % 60;
      std::cout << " (" << horas << " hora" << (horas != 1 ? "s" : "")
                << (minutos > 0 ? " y " + std::to_string(minutos) + " minuto" +
                                      (minutos != 1 ? "s" : "")
                                : "")
                << ")";
    }
    std::cout << "\n";

    esperarEnter();
  }
};

int main() {
  InterfazUsuario ui;
  ui.manejarEntradaUsuario();

  std::cout << "¡Gracias por usar el Sistema de Gestión de Preguntas basado en "
               "la Taxonomía de Bloom!\n";
  return 0;
}