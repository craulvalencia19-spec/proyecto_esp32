// 1. DEFINIR LOS PINES FÍSICOS
#define RELE_0  26
#define RELE_1  27  // Tu pin elegido
#define RELE_2  25
#define RELE_3  33

// Guardamos los pines en una lista (Array) para controlarlos juntos
const int pinesReles[4] = {RELE_0, RELE_1, RELE_2, RELE_3};

void setup() {
  // Inicializar la comunicación con la computadora
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n========================================");
  Serial.println("  CASA INTELIGENTE - DESDE CERO ACTIVA");
  Serial.println("========================================");

  // Configurar los 4 pines como SALIDAS y apagados al arrancar
  for (int i = 0; i < 4; i++) {
    pinMode(pinesReles[i], OUTPUT);
    digitalWrite(pinesReles[i], HIGH); // En relés, HIGH suele ser APAGADO
  }
  Serial.println("Sistema listo. Esperando comandos en español...");
}

void loop() {
  // ¿Hay algún comando llegando por el cable USB?
  if (Serial.available() > 0) {
    
    // Leer el texto que escribiste hasta que presiones ENTER
    String comando = Serial.readStringUntil('\n');
    comando.trim(); // Limpiar espacios invisibles

    Serial.print("Comando recibido: ");
    Serial.println(comando);

    // ===================================================
    // SECCIÓN DE CONTROL GLOBAL (TODOS AL INSTANTE)
    // ===================================================
    if (comando == "prender_todos") {
      for (int i = 0; i < 4; i++) {
        digitalWrite(pinesReles[i], LOW); // LOW los activa a todos juntos
      }
      Serial.println("⚡ ¡TODOS los relés encendidos al instante!");
    } 
    else if (comando == "apagar_todos") {
      for (int i = 0; i < 4; i++) {
        digitalWrite(pinesReles[i], HIGH); // HIGH los apaga a todos juntos
      }
      Serial.println("🛑 ¡Todos los relés apagados al instante!");
    } 

    // ===================================================
    // SECCIÓN DE CONTROL INDIVIDUAL (TUS COMANDOS EXACTOS)
    // ===================================================
    else if (comando == "prender_rele_1") {
      digitalWrite(RELE_1, LOW);
      Serial.println("✅ Relé 1 (Pin 27) ENCENDIDO");
    }
    else if (comando == "apagar_rele_1") {
      digitalWrite(RELE_1, HIGH);
      Serial.println("✅ Relé 1 (Pin 27) APAGADO");
    }
    else if (comando == "prender_rele_2") {
      digitalWrite(RELE_2, LOW);
      Serial.println("✅ Relé 2 (Pin 25) ENCENDIDO");
    }
    else if (comando == "apagar_rele_2") {
      digitalWrite(RELE_2, HIGH);
      Serial.println("✅ Relé 2 (Pin 25) APAGADO");
    }
    
    // Si escribes otra cosa que no existe:
    else {
      Serial.println("❌ Comando inválido. Usa: 'prender_todos' o 'prender_rele_1'");
    }
  }
}