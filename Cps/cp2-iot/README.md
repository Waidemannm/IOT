# 🌱 SmartGrass IoT

Sistema IoT para monitoramento ambiental utilizando ESP32, sensores simulados e comunicação via MQTT.

---

## 🧠 Descrição do Projeto

Este projeto consiste no desenvolvimento de uma solução IoT utilizando o microcontrolador ESP32 para monitoramento de condições ambientais em tempo real.

A proposta demonstra uma arquitetura escalável baseada no modelo **publish/subscribe**, utilizando o protocolo MQTT para comunicação entre dispositivos.

---

## ⚙️ Tecnologias Utilizadas

- ESP32 (simulado no Wokwi)
- Protocolo MQTT
- Broker HiveMQ
- Node-RED (consumo e processamento dos dados)
- Arduino IDE / C++
- JSON (estrutura de dados)

---

## 🔌 Sensores Utilizados

O sistema utiliza dois sensores principais:

### 📏 Sensor Ultrassônico (HC-SR04)
- Mede distância
- Simula nível ou crescimento (ex: grama)

### 💧 Potenciômetro (Simulando Umidade)
- Simula leitura de umidade do solo
- Valor varia de 0% a 100%

---

## 📡 Arquitetura do Sistema


---

## 🔄 Funcionamento

1. O ESP32 realiza a leitura dos sensores
2. Os dados são estruturados em formato JSON
3. As informações são enviadas via MQTT para o broker HiveMQ
4. O Node-RED consome esses dados
5. Os dados podem ser:
   - exibidos em dashboard
   - processados para gerar alertas
   - armazenados em banco de dados

---

## 📦 Estrutura dos Dados (MQTT)

### Tópicos utilizados:


### Exemplo de payload:

```json
{
  "sensor": "ultrassom",
  "valor": 12.5
}

{
  "sensor": "umidade",
  "valor": 45
}
