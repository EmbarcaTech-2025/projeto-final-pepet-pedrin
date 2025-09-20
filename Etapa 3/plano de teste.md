# Plano de Teste: Estimativa de Distância usando RSSI em ESP

## 1. Objetivo
- Estimar a relação entre RSSI medido pelo ESP e a distância real.  
- Obter um modelo de conversão **RSSI → distância** (modelo log-distance).  
- Avaliar precisão e erro em diferentes cenários (linha de visada, obstruções, orientação).  
- Recomendar técnicas de filtragem e calibração.

## 2. Equipamento Necessário
- ESP (ex.: ESP32) com BLE ou Wi-Fi ativo.  
- Smartphone com Bluetooth.  
- Trena/fita métrica de precisão.  
- Fitas para marcar distâncias no chão.  

## 3. Parâmetros Controlados
- **Distâncias de referência (d₀):** 10cm 20cm 40cm 80cm 160cm 320cm.    
- **Amostras por condição:** mínimo 30.

## 4. Matriz de Experimentos
1. **Distâncias:** 10cm 20cm 40cm 80cm 160cm 320cm.   
2. **Cenários:**  
   - Sem obstrução em espaço aberto.
   - Smartphone em posição estática a 0°

## 5. Procedimento
1. Fixar Tx e Rx na altura definida.  
2. Configurar transmissor em broadcast contínuo.  
3. Iniciar captura no ESP (RSSI + timestamp).  
4. Para cada distância:  
   - Reposicionar transmissor.  
   - Coletar **N = 30 amostras**.  
5. Repetir em todas as distâncias.

## 6. Extração do modelo
1. Calcular a média de RSSI para cada distãncia fixa.
2. Transformar os eixos utilizando logaritmos de base 10.
3. Cálculo do modelo por regressão linear utilizando MMQ.
4. Comparar ao modelo de dobro de distância -> perda de 6 dB.
